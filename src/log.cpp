#include <rofl/log.hpp>
#include <rofl/log_location.hpp>
#include <rofl/aux/log_parameters.hpp>
#include <fcppt/log/define_object.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/parameters/object.hpp>


FCPPT_LOG_DEFINE_OBJECT(
	rofl::log,
	rofl::aux::log_parameters(
		rofl::log_location()
	)
)
