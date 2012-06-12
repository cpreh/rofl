#include "parameters.hpp"
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/color.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/scoped_vertex_buffer.hpp>
#include <sge/renderer/scoped_vertex_declaration.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/context/object.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/foreach.hpp>

template
<
	typename A,
	typename B
>
rofl::line_strip::object<A,B>::object(
	sge::renderer::device &_renderer,
	parameters<A,B> const &params)
:
	renderer_(
		&_renderer),
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
rofl::line_strip::object<A,B>::object(
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
rofl::line_strip::object<A,B> &
rofl::line_strip::object<A,B>::operator=(
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
rofl::line_strip::object<A,B>::push_back(
	rofl::line_strip::object<A,B>::point const &v)
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
rofl::line_strip::object<A,B>::pop_back()
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
rofl::line_strip::object<A,B>::clear()
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
rofl::line_strip::object<A,B>::draw(
	sge::renderer::context::object &_render_context) const
{
	if (points_.empty())
		return;

	sge::renderer::scoped_vertex_declaration const vb_declaration(
		_render_context,
		*vertex_declaration_
	);

	sge::renderer::scoped_vertex_buffer const vb_context(
		_render_context,
		*vb_
	);

	_render_context.render_nonindexed(
		sge::renderer::first_vertex(
			0u
		),
		sge::renderer::vertex_count(
			vb_->size()
		),
		sge::renderer::primitive_type::line_strip);
}

template
<
	typename A,
	typename B
>
void
rofl::line_strip::object<A,B>::regenerate_vb()
{
	typedef
	sge::renderer::vf::pos
	<
		unit,
		2
	> pos_type;

	typedef
	sge::renderer::vf::color
	<
		typename color::format
	> color_type;

	typedef
	sge::renderer::vf::part
	<
		boost::mpl::vector
		<
			pos_type,
			color_type
		>
	> format_part;

	typedef
	sge::renderer::vf::format
	<
		boost::mpl::vector
		<
			format_part
		>
	> format;

	typedef
	sge::renderer::vf::view
	<
		format_part
	> vertex_view;

	if (points_.empty())
		return;

	vertex_declaration_ =
		renderer_->create_vertex_declaration(
			sge::renderer::vf::dynamic::make_format<format>());
	vb_ =
		renderer_->create_vertex_buffer(
			*vertex_declaration_,
			sge::renderer::vf::dynamic::make_part_index<
				format,
				format_part
			>(),
			sge::renderer::vertex_count(
				points_.size() + (style_ == style::loop ? 1 : 0)),
			sge::renderer::resource_flags::none);

	sge::renderer::scoped_vertex_lock const vblock(
		*vb_,
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
typename rofl::line_strip::object<A,B>::point_sequence const &
rofl::line_strip::object<A,B>::points() const
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
rofl::line_strip::object<A,B>::back(
	point const &p)
{
	points_.back() = p;
	regenerate_vb();
}
