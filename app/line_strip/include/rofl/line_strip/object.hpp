#ifndef ROFL_LINE_STRIP_OBJECT_HPP_INCLUDED
#define ROFL_LINE_STRIP_OBJECT_HPP_INCLUDED

#include <rofl/line_strip/object_fwd.hpp>
#include <rofl/line_strip/parameters_fwd.hpp>
#include <rofl/line_strip/style.hpp>
#include <fcppt/reference_wrapper.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/static.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/renderer/vf/color.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/part.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace rofl
{
namespace line_strip
{
template
<
	typename Value,
	typename Color
>
class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef Value unit;

	typedef
	fcppt::math::vector::static_
	<
		unit,
		2
	> point;

	typedef
	std::vector
	<
		point
	> point_sequence;
	typedef Color color;

	object(
		sge::renderer::device::core &,
		parameters<unit,color> const &);

	~object();

	object(
		object &&
	);

	object &
	operator=(
		object &&
	);

	void
	push_back(
		point const &);

	void
	pop_back();

	void
	clear();

	void
	draw(
		sge::renderer::context::core &) const;

	// only read access because we have to regenerate the vb afterwards
	point_sequence const &
	points() const;

	void
	back(
		point const &);
private:
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


	typedef fcppt::reference_wrapper<
		sge::renderer::device::core
	> device_reference;

	device_reference renderer_;

	rofl::line_strip::style style_;

	color color_;

	point_sequence points_;

	sge::renderer::vertex::declaration_unique_ptr vertex_declaration_;

	typedef
	fcppt::optional<
		sge::renderer::vertex::buffer_unique_ptr
	>
	optional_vertex_buffer_ptr;

	optional_vertex_buffer_ptr vertex_buffer_;

	void
	regenerate_vb();
};

}
}

#endif
