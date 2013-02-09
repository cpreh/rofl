#include <rofl/aux/log_parameters.hpp>
#include <rofl/aux/polygonizers/log.hpp>
#include <rofl/aux/polygonizers/log_location.hpp>
#include <fcppt/log/define_object.hpp>
#include <fcppt/log/parameters/object.hpp>


FCPPT_LOG_DEFINE_OBJECT(
	rofl::aux::polygonizers::log,
	rofl::aux::log_parameters(
		rofl::aux::polygonizers::log_location()
	)
)
