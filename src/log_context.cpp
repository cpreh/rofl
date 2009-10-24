#include <rofl/log_context.hpp>
#include <sge/log/context.hpp>

sge::log::context &
rofl::log_context()
{
	static sge::log::context global_;
	return global_;
}