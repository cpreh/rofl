#include <rofl/log.hpp>
#include <rofl/log_context.hpp>
#include <sge/log/parameters/root.hpp>
#include <sge/text.hpp>
#include <sge/cout.hpp>
#include <sge/log/level.hpp>

sge::log::object &
rofl::log()
{
	static sge::log::object global_(
		sge::log::parameters::root(
			sge::cout
		)
		.prefix(
			SGE_TEXT("rofl")
		)
		.enabled(
			true
		)
		.level(
			sge::log::level::warning
		)
		.context(
			log_context()
		)
		.create()
	);
	
	return global_;
}
