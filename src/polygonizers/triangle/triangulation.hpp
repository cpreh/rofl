#ifndef ROFL_POLYGONIZERS_TRIANGLE_TRIANGULATION_HPP_INCLUDED
#define ROFL_POLYGONIZERS_TRIANGLE_TRIANGULATION_HPP_INCLUDED

#include "impl/impl.hpp"

namespace rofl
{
namespace polygonizers
{
namespace triangle
{
class triangulation
{
public:
	triangulation(
		char const *options,
		triangulateio &in,
		triangulateio &out);
	~triangulation();
private:
	triangulateio &out_;
};
}
}
}

#endif
