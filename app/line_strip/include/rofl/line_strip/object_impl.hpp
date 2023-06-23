#ifndef ROFL_LINE_STRIP_OBJECT_IMPL_HPP_INCLUDED
#define ROFL_LINE_STRIP_OBJECT_IMPL_HPP_INCLUDED

#include <rofl/line_strip/parameters.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/make_part_index.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/set_proxy.hpp>
#include <sge/renderer/vf/labels/color.hpp>
#include <sge/renderer/vf/labels/pos.hpp>
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
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/context/core.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/optional/assign.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template
<
	typename A,
	typename B
>
rofl::line_strip::object<A,B>::object(
	sge::renderer::device::core_ref const _renderer,
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
	vertex_declaration_(
		renderer_.get().create_vertex_declaration(
			sge::renderer::vertex::declaration_parameters(
				sge::renderer::vf::dynamic::make_format<format>()
			)
		)
	),
	vertex_buffer_()
{
	regenerate_vb();
}

namespace rofl::line_strip
{
template
<
	typename A,
	typename B
>
object<A,B>::~object()
= default;
}

template
<
	typename A,
	typename B
>
rofl::line_strip::object<A,B>::object(
	object &&
)
noexcept
= default;

template
<
	typename A,
	typename B
>
rofl::line_strip::object<A,B> &
rofl::line_strip::object<A,B>::operator=(
	object &&
)
noexcept
= default;

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
	{
		return;
	}

	sge::renderer::vertex::scoped_declaration const vb_declaration(
		fcppt::make_ref(
			_render_context
		),
		fcppt::make_cref(
			*vertex_declaration_
		)
	);

	sge::renderer::vertex::buffer_unique_ptr const &vertex_buffer(
		vertex_buffer_.get_unsafe()
	);

	sge::renderer::vertex::scoped_buffer const vb_context(
		fcppt::make_ref(
			_render_context
		),
		fcppt::make_cref(
			*vertex_buffer
		)
	);

	_render_context.render_nonindexed(
		sge::renderer::vertex::first(
			0U
		),
		sge::renderer::vertex::count(
			vertex_buffer->linear_size()
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
	using
	vertex_view
	=
	sge::renderer::vf::view
	<
		format_part
	>;

	if (points_.empty())
	{
		return;
	}

	sge::renderer::vertex::buffer_unique_ptr const &vertex_buffer(
		fcppt::optional::assign(
			vertex_buffer_,
			renderer_.get().create_vertex_buffer(
				sge::renderer::vertex::buffer_parameters(
					fcppt::make_cref(
						*vertex_declaration_
					),
					sge::renderer::vf::dynamic::make_part_index<
						format,
						format_part
					>(),
					sge::renderer::vertex::count(
						points_.size() + (style_ == style::loop ? 1 : 0)),
					sge::renderer::resource_flags_field::null()
				)
			)
		)
	);

	sge::renderer::vertex::scoped_lock const vblock(
		fcppt::make_ref(
			*vertex_buffer
		),
		sge::renderer::lock_mode::writeonly);

	vertex_view const vertices(
		vblock.value());

	typename vertex_view::iterator vb_it = vertices.begin();

	for(
		auto const &v : points_
	)
	{
		sge::renderer::vf::set_proxy(
			*vb_it,
			sge::renderer::vf::labels::pos{},
			v
		);

		sge::renderer::vf::set_proxy(
			*vb_it,
			sge::renderer::vf::labels::color{},
			color_
		);

		++vb_it;
	}

	switch (style_)
	{
		case style::no_loop: break;
		case style::loop:
			sge::renderer::vf::set_proxy(
				*vb_it,
				sge::renderer::vf::labels::pos{},
				points_.front()
			);

			sge::renderer::vf::set_proxy(
				*vb_it,
				sge::renderer::vf::labels::color{},
				color_
			);
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
