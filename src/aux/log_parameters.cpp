#include <rofl/log_context.hpp>
#include <rofl/aux/log_parameters.hpp>
#include <fcppt/io/clog.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location_fwd.hpp>
#include <fcppt/log/parameters.hpp>


fcppt::log::parameters
rofl::aux::log_parameters(
	fcppt::log::location const &_location
)
{
	return
		fcppt::log::parameters(
			fcppt::io::clog(),
			fcppt::log::level::warning
		)
		.enabled(
			true
		)
		.context_location(
			rofl::log_context(),
			_location
		);
}
