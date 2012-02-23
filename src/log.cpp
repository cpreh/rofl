#include "log_location.hpp"
#include "log_parameters.hpp"
#include <rofl/log.hpp>
#include <sge/log/declare_lib_base.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/log/location.hpp>

SGE_LOG_DECLARE_LIB_BASE(
	rofl::log,
	rofl::log_parameters(
		rofl::log_location()
	)
)
