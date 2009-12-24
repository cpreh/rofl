#include "../log.hpp"
#include <rofl/log.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/text.hpp>

fcppt::log::object &
rofl::polygonizers::log()
{
	static fcppt::log::object o(
		fcppt::log::parameters::inherited(
			rofl::log(),
			FCPPT_TEXT("polygonizers")));
	return o;
}
