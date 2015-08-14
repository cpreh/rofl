#include <rofl/aux/log_parameters.hpp>
#include <rofl/aux/polygonizers/triangle/log.hpp>
#include <rofl/aux/polygonizers/triangle/log_location.hpp>
#include <fcppt/log/define_object.hpp>
#include <fcppt/log/location.hpp>


FCPPT_LOG_DEFINE_OBJECT(
	rofl::aux::polygonizers::triangle::log,
	rofl::aux::log_parameters(
		rofl::aux::polygonizers::triangle::log_location()
	)
)
