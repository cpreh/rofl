#include <rofl/log.hpp>
#include <rofl/log_context.hpp>
#include <fcppt/log/parameters/root.hpp>
#include <fcppt/log/parameters/all.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/text.hpp>

fcppt::log::object &
rofl::log()
{
	static fcppt::log::object global_(
		fcppt::log::parameters::root(
			fcppt::io::cout
		)
		.prefix(
			FCPPT_TEXT("rofl")
		)
		.enabled(
			true
		)
		.level(
			fcppt::log::level::warning
		)
		.context(
			log_context()
		)
		.create()
	);
	
	return global_;
}
