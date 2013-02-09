#ifndef ROFL_AUX_POLYGONIZERS_TRIANGLE_TRIANGULATION_HPP_INCLUDED
#define ROFL_AUX_POLYGONIZERS_TRIANGLE_TRIANGULATION_HPP_INCLUDED

#include <triangle/impl.hpp>
#include <fcppt/noncopyable.hpp>


namespace rofl
{
namespace aux
{
namespace polygonizers
{
namespace triangle
{

class triangulation
{
	FCPPT_NONCOPYABLE(
		triangulation
	);
public:
	triangulation(
		char const *options,
		triangulateio &in,
		triangulateio &out
	);

	~triangulation();
private:
	triangulateio &out_;
};

}
}
}
}

#endif
