#include <rofl/log_context.hpp>
#include <fcppt/log/context.hpp>

fcppt::log::context &
rofl::log_context()
{
	static fcppt::log::context global_;
	return global_;
}