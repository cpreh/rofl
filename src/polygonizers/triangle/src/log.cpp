#include "../log.hpp"
#include "../../log.hpp"

fcppt::log::object &
rofl::polygonizers::triangle::log()
{
	static fcppt::log::object o(
		fcppt::log::parameters::inherited(
			polygonizers::log(),
			FCPPT_TEXT("triangle")));
	return o;
}
