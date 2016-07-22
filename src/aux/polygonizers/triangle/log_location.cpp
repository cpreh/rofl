#include <rofl/aux/polygonizers/log_location.hpp>
#include <rofl/aux/polygonizers/triangle/log_location.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/name.hpp>


fcppt::log::location
rofl::aux::polygonizers::triangle::log_location()
{
	return
		rofl::aux::polygonizers::log_location()
		/
		fcppt::log::name{
			FCPPT_TEXT("triangle")
		};
}
