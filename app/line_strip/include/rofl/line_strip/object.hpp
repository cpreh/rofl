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
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
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

	typedef typename
	fcppt::math::vector::static_
	<
		unit,
		2
	>::type point;

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
	typedef fcppt::reference_wrapper<
		sge::renderer::device::core
	> device_reference;

	device_reference renderer_;

	rofl::line_strip::style style_;

	color color_;

	point_sequence points_;

	sge::renderer::vertex::declaration_unique_ptr vertex_declaration_;

	sge::renderer::vertex::buffer_unique_ptr vertex_buffer_;

	void
	regenerate_vb();
};

}
}

#endif
