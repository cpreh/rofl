#include <rofl/log_location.hpp>
#include "log_location.hpp"
#include <fcppt/text.hpp>
#include <fcppt/log/location.hpp>


fcppt::log::location const
rofl::polygonizers::log_location()
{
	return
		rofl::log_location()
		/
		FCPPT_TEXT("polygonizers");
}
