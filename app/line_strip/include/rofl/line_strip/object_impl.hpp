#ifndef ROFL_LINE_STRIP_OBJECT_IMPL_HPP_INCLUDED
#define ROFL_LINE_STRIP_OBJECT_IMPL_HPP_INCLUDED

#include <rofl/line_strip/parameters.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/color.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/declaration.hpp>
#include <sge/renderer/vertex/declaration_parameters.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vertex/scoped_lock.hpp>
#include <sge/renderer/vertex/scoped_buffer.hpp>
#include <sge/renderer/vertex/scoped_declaration.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/context/core.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template
<
	typename A,
	typename B
>
rofl::line_strip::object<A,B>::object(
	sge::renderer::device::core &_renderer,
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
	vertex_declaration_(),
	vertex_buffer_()
{
	regenerate_vb();
}

template
<
	typename A,
	typename B
>
rofl::line_strip::object<A,B>::~object()
{
}

template
<
	typename A,
	typename B
>
rofl::line_strip::object<A,B>::object(
	object &&_other
)
:
	renderer_(
		_other.renderer_
	),
	style_(
		_other.style_
	),
	color_(
		_other.color_
	),
	points_(
		std::move(
			_other.points_
		)
	),
	vertex_declaration_(
		std::move(
			_other.vertex_declaration_
		)
	),
	vertex_buffer_(
		std::move(
			_other.vertex_buffer_
		)
	)
{
}

template
<
	typename A,
	typename B
>
rofl::line_strip::object<A,B> &
rofl::line_strip::object<A,B>::operator=(
	object &&_other
)
{
	renderer_ = _other.renderer_;

	style_ = _other.style_;

	color_ = _other.color_;

	points_ =
		std::move(
			_other.points_
		);

	vertex_declaration_ =
		std::move(
			_other.vertex_declaration_
		);

	vertex_buffer_ =
		std::move(
			_other.vertex_buffer_
		);

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
	sge::renderer::context::core &_render_context) const
{
	if (points_.empty())
		return;

	sge::renderer::vertex::scoped_declaration const vb_declaration(
		_render_context,
		*vertex_declaration_
	);

	sge::renderer::vertex::scoped_buffer const vb_context(
		_render_context,
		*vertex_buffer_
	);

	_render_context.render_nonindexed(
		sge::renderer::vertex::first(
			0u
		),
		sge::renderer::vertex::count(
			vertex_buffer_->size()
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
		renderer_.get().create_vertex_declaration(
			sge::renderer::vertex::declaration_parameters(
				sge::renderer::vf::dynamic::make_format<format>()));
	vertex_buffer_ =
		renderer_.get().create_vertex_buffer(
			sge::renderer::vertex::buffer_parameters(
				*vertex_declaration_,
				sge::renderer::vf::dynamic::make_part_index<
					format,
					format_part
				>(),
				sge::renderer::vertex::count(
					points_.size() + (style_ == style::loop ? 1 : 0)),
				sge::renderer::resource_flags_field::null()));

	sge::renderer::vertex::scoped_lock const vblock(
		*vertex_buffer_,
		sge::renderer::lock_mode::writeonly);

	vertex_view const vertices(
		vblock.value());

	typename vertex_view::iterator vb_it = vertices.begin();

	for(
		auto const &v : points_
	)
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

#endif
