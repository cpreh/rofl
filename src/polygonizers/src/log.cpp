#include "../log.hpp"
#include "../log_location.hpp"
#include <rofl/aux/log_parameters.hpp>
#include <fcppt/log/define_object.hpp>
#include <fcppt/log/parameters/object.hpp>


FCPPT_LOG_DEFINE_OBJECT(
	rofl::polygonizers::log,
	rofl::aux::log_parameters(
		rofl::polygonizers::log_location()
	)
)
