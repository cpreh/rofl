#include "../log.hpp"
#include "../log_location.hpp"
#include "../../../log_parameters.hpp"
#include <sge/log/declare_lib_base.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/log/location.hpp>

SGE_LOG_DECLARE_LIB_BASE(
	rofl::polygonizers::triangle::log,
	rofl::log_parameters(
		rofl::polygonizers::triangle::log_location()
	)
)
