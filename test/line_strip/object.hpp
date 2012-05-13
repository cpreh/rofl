#ifndef ROFL_LINE_STRIP_OBJECT_HPP_INCLUDED
#define ROFL_LINE_STRIP_OBJECT_HPP_INCLUDED

#include "parameters_fwd.hpp"
#include "style.hpp"
#include <fcppt/math/vector/static.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/vertex_buffer_shared_ptr.hpp>
#include <sge/renderer/vertex_declaration_shared_ptr.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <vector>

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
public:
	typedef Value unit;
	typedef typename
	fcppt::math::vector::static_
	<
		unit,
	2>::type point;
	typedef
	std::vector
	<
		point
	> point_sequence;
	typedef Color color;

	object(
		sge::renderer::device &,
		parameters<unit,color> const &);

	object(
		object const &);

	object &
	operator=(
		object const &);

	void
	push_back(
		point const &);

	void
	pop_back();

	void
	clear();

	void
	draw(
		sge::renderer::context::object &) const;

	// only read access because we have to regenerate the vb afterwards
	point_sequence const &
	points() const;

	void
	back(
		point const &);
private:
	sge::renderer::device *renderer_;
	style::type style_;
	color color_;
	point_sequence points_;
	sge::renderer::vertex_declaration_shared_ptr vertex_declaration_;
	sge::renderer::vertex_buffer_shared_ptr vb_;

	void regenerate_vb();
};
}
}

#endif
