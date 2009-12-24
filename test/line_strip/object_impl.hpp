#include "object.hpp"
#include "parameters.hpp"
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/color.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/make_dynamic_format.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/device.hpp>
#include <sge/cerr.hpp>
#include <fcppt/math/null.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/foreach.hpp>

template
<
	typename A,
	typename B
>
sge::line_strip::object<A,B>::object(
	sge::renderer::device_ptr const _renderer,
	parameters<A,B> const &params)
:
	renderer_(
		_renderer),
	style_(
		params.style()),
	color_(
		params.color()),
	points_(
		params.points().begin(),
		params.points().end()),
	vb_()
{
	regenerate_vb();
}

template
<
	typename A,
	typename B
>
sge::line_strip::object<A,B>::object(
	object const &r)
:
	renderer_(
		r.renderer_),
	style_(
		r.style_),
	color_(
		r.color_),
	points_(
		r.points_)
{
	regenerate_vb();
}

template
<
	typename A,
	typename B
>
sge::line_strip::object<A,B> &
sge::line_strip::object<A,B>::operator=(
	object const &r)
{
	style_ = r.style_;
	renderer_ = r.renderer_;
	color_ = r.color_;
	points_ = r.points_;
	regenerate_vb();
	return *this;
}

template
<
	typename A,
	typename B
>
void 
sge::line_strip::object<A,B>::push_back(
	sge::line_strip::object<A,B>::point const &v)
{
	points_.push_back(
		v);
	regenerate_vb();
}

template
<
	typename A,
	typename B
>
void 
sge::line_strip::object<A,B>::pop_back()
{
	points_.pop_back();
	regenerate_vb();
}

template
<
	typename A,
	typename B
>
void 
sge::line_strip::object<A,B>::clear()
{
	points_.clear();
	regenerate_vb();
}

template
<
	typename A,
	typename B
>
void 
sge::line_strip::object<A,B>::draw() const
{
	if (!points_.empty())
		renderer_->render(
			vb_,
			fcppt::math::null<sge::renderer::size_type>(),
			vb_->size(),
			sge::renderer::nonindexed_primitive_type::line_strip);
}

template
<
	typename A,
	typename B
>
void 
sge::line_strip::object<A,B>::regenerate_vb()
{
	typedef 
	renderer::vf::pos
	<
		unit,
		2
	> pos_type;
	
	typedef 
	renderer::vf::color
	<
		typename color::format
	> color_type;
	
	typedef 
	renderer::vf::format
	<
		boost::mpl::vector
		<
			pos_type,
			color_type
		>
	> format;
	
	typedef 
	renderer::vf::view
	<
		format
	> vertex_view;
	
	if (points_.empty())
		return;
	vb_ = 
		renderer_->create_vertex_buffer(
			renderer::vf::make_dynamic_format<format>(),
			static_cast<renderer::size_type>(
				points_.size() + (style_ == style::loop ? 1 : 0)),
			renderer::resource_flags::none);

	renderer::scoped_vertex_lock const vblock(
		vb_,
		sge::renderer::lock_mode::writeonly);
	
	vertex_view const vertices(
		vblock.value());

	typename vertex_view::iterator vb_it = vertices.begin();
	
	BOOST_FOREACH(point const &v,points_)
	{
		(*vb_it).template set<pos_type>(
			v);
		(*vb_it++).template set<color_type>(
			color_);
	}

	switch (style_)
	{
		case style::no_loop: break;
		case style::loop: 
			(*vb_it).template set<pos_type>(
				points_.front());
			(*vb_it).template set<color_type>(
				color_);
		break;
	}
}

template
<
	typename A,
	typename B
>
typename sge::line_strip::object<A,B>::point_sequence const &
sge::line_strip::object<A,B>::points() const
{
	return 
		points_;
}

template
<
	typename A,
	typename B
>
void
sge::line_strip::object<A,B>::back(
	point const &p)
{
	points_.back() = p;
	regenerate_vb();
}
