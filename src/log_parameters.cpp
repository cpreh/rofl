#include "log_parameters.hpp"
#include <rofl/log_context.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/log/parameters/with_context.hpp>
#include <fcppt/log/location_fwd.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/io/clog.hpp>

fcppt::log::parameters::object const
rofl::log_parameters(
	fcppt::log::location const &_location
)
{
	return
		fcppt::log::parameters::with_context(
			rofl::log_context(),
			_location
		)
		.enabled(
			true
		)
		.level_defaults(
			fcppt::io::clog(),
			fcppt::log::level::warning
		);
}
