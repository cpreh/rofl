#include "../log.hpp"
#include "../../log.hpp"
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/text.hpp>

fcppt::log::object &
rofl::polygonizers::triangle::log()
{
	static fcppt::log::object o(
		fcppt::log::parameters::inherited(
			polygonizers::log(),
			FCPPT_TEXT("triangle")));
	return o;
}
