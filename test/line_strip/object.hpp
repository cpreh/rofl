#ifndef SGE_LINE_STRIP_OBJECT_HPP_INCLUDED
#define SGE_LINE_STRIP_OBJECT_HPP_INCLUDED

#include "parameters_fwd.hpp"
#include "style.hpp"
#include <sge/math/vector/static.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <vector>

namespace sge
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
	sge::math::vector::static_
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
		sge::renderer::device_ptr,
		parameters<unit,color> const &);
	object(
		object const &);
	object &operator=(
		object const &);

	void push_back(
		point const &);
	void clear();
	void draw() const;
private:
	sge::renderer::device_ptr renderer_;
	style::type style_;
	color color_;
	point_sequence points_;
	sge::renderer::vertex_buffer_ptr vb_;

	void regenerate_vb();
};
}
}

#endif
