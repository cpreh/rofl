#ifndef ROFL_AUX_POLYGONIZERS_TRIANGLE_TRIANGULATION_HPP_INCLUDED
#define ROFL_AUX_POLYGONIZERS_TRIANGLE_TRIANGULATION_HPP_INCLUDED

#include <triangle/impl.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>


namespace rofl::aux::polygonizers::triangle
{

class triangulation
{
	FCPPT_NONMOVABLE(
		triangulation
	);
public:
	triangulation(
		char const *options,
		fcppt::reference<
			triangulateio
		> in,
		fcppt::reference<
			triangulateio
		> out
	);

	~triangulation();
private:
	fcppt::reference<
		triangulateio
	> const out_;
};

}

#endif
