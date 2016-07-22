#include <rofl/create_polygonizer.hpp>
#include <rofl/polygonizer.hpp>
#include <rofl/polygonizer_unique_ptr.hpp>
#include <rofl/aux/polygonizers/triangle/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_fwd.hpp>


rofl::polygonizer_unique_ptr
rofl::create_polygonizer(
	fcppt::log::context &_log_context
)
{
	return
		fcppt::unique_ptr_to_base<
			rofl::polygonizer
		>(
			fcppt::make_unique_ptr<
				rofl::aux::polygonizers::triangle::object
			>(
				_log_context
			)
		);
}
