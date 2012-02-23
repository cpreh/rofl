#include "../log.hpp"
#include "../log_location.hpp"
#include "../../log_parameters.hpp"
#include <sge/log/declare_lib_base.hpp>
#include <fcppt/log/parameters/object.hpp>

SGE_LOG_DECLARE_LIB_BASE(
	rofl::polygonizers::log,
	rofl::log_parameters(
		rofl::polygonizers::log_location()
	)
)
