#include "line_strip/object.hpp"
#include "line_strip/parameters.hpp"
#include "line_strip/object_impl.hpp"
#include "line_strip/parameters_impl.hpp"
#include "line_strip_output.hpp"
#include <sge/systems/cursor_demuxer.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/keyboard_collector.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/with_image2d.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/colors.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/parameters/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/projection/orthogonal_viewport.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_scoped_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/state/ffp/transform/scoped.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport_is_null.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/media/all_extensions.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <exception>
#include <vector>
#include <iostream>
#include <ostream>

namespace
{

typedef
rofl::line_strip::object
<
	float,
	sge::image::color::rgba8
>
line_strip;

typedef
rofl::line_strip::parameters
<
	float,
	sge::image::color::rgba8
>
line_strip_params;

typedef
std::vector
<
	line_strip
>
hole_vector;

class cursor_handler
{
public:
	cursor_handler(
		sge::input::cursor::object &,
		line_strip &current,
		line_strip &border,
		hole_vector &holes
	);
private:
	line_strip &current_;
	line_strip &border_;
	hole_vector &holes_;
	bool has_border_;
	fcppt::signal::scoped_connection const
		button_connection_,
		move_connection_;

	void
	button_callback(
		sge::input::cursor::button_event const &
	);

	void
	move_callback(
		sge::input::cursor::move_event const &
	);
};

cursor_handler::cursor_handler(
	sge::input::cursor::object &_cursor,
	line_strip &_current,
	line_strip &_border,
	hole_vector &_holes
)
:
	current_(
		_current),
	border_(
		_border),
	holes_(
		_holes),
	has_border_(
		false),
	button_connection_(
		_cursor.button_callback(
			std::tr1::bind(
				&cursor_handler::button_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	move_connection_(
		_cursor.move_callback(
			std::tr1::bind(
				&cursor_handler::move_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{
	current_.push_back(
		line_strip::point::null()
	);
}

void
cursor_handler::button_callback(
	sge::input::cursor::button_event const &_event
)
{
	if(
		!_event.pressed()
	)
		return;

	switch(
		_event.button_code()
	)
	{
	case sge::input::cursor::button_code::left:
		current_.push_back(
			current_.points().back());
		return;
	case sge::input::cursor::button_code::right:
		{
			// 4 because the last point is just a dummy point
			if (current_.points().size() < static_cast<line_strip::point_sequence::size_type>(4))
				return;
			// last point is the cursor position
			line_strip::point const last =
				current_.points().back();

			current_.pop_back();

			if (!has_border_)
			{
				border_ = current_;
				has_border_ = true;
			}
			else
			{
				holes_.push_back(
					current_);
			}
			current_.clear();
			current_.push_back(
				last);

			return;
		}
	default:
		break;
	}
}

void
cursor_handler::move_callback(
	sge::input::cursor::move_event const &_event
)
{
	if(
		!_event.position()
	)
		return;

	current_.back(
		fcppt::math::vector::structure_cast<
			line_strip::point
		>(
			*_event.position()
		)
	);
}

}


awl::main::exit_code const
test_main(
	awl::main::function_context const &
)
try
{
	sge::window::dim const window_dim(
		1024,
		768
	);

	sge::systems::instance<
		boost::mpl::vector4<
			sge::systems::with_window,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_input<
				boost::mpl::vector2<
					sge::systems::cursor_demuxer,
					sge::systems::keyboard_collector
				>
			>,
			sge::systems::with_image2d
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window(
				sge::window::parameters(
					sge::window::title(
						FCPPT_TEXT("pathfinding test")
					),
					window_dim
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters::object(
					sge::renderer::pixel_format::object(
						sge::renderer::pixel_format::color::depth32,
						sge::renderer::pixel_format::depth_stencil::off,
						sge::renderer::pixel_format::optional_multi_samples(),
						sge::renderer::pixel_format::srgb::no
					),
					sge::renderer::parameters::vsync::on,
					sge::renderer::display_mode::optional_object()
				),
				sge::viewport::center_on_resize(
					window_dim
				)
			)
		)
		(
			sge::systems::input(
				sge::systems::cursor_option_field::null()
			)
		)
		(
			sge::systems::image2d(
				sge::image::capabilities_field::null(),
				sge::media::all_extensions
			)
		)
	);

	fcppt::signal::scoped_connection const escape_connection(
		sge::systems::quit_on_escape(
			sys
		)
	);

	line_strip border(
		sys.renderer_core(),
		line_strip_params()
			.style(
				rofl::line_strip::style::loop)
			.color(
				line_strip::color(
					(mizuiro::color::init::red() %= 1.)
					(mizuiro::color::init::green() %= 0.)
					(mizuiro::color::init::blue() %= 0.)
					(mizuiro::color::init::alpha() %= 1.)
				)
			)
	);

	hole_vector holes;

	line_strip current_strip(
		sys.renderer_core(),
		line_strip_params()
			.style(
				rofl::line_strip::style::loop)
			.color(
				line_strip::color(
					(mizuiro::color::init::red() %= 1.)
					(mizuiro::color::init::green() %= 1.)
					(mizuiro::color::init::blue() %= 1.)
					(mizuiro::color::init::alpha() %= 1.)
				)
			)
	);

	cursor_handler handler(
		sys.cursor_demuxer(),
		current_strip,
		border,
		holes
	);

	while(
		sys.window_system().poll()
	)
	{
		if(
			sge::renderer::target::viewport_is_null(
				sys.renderer_ffp().onscreen_target().viewport()
			)
		)
			continue;

		sge::renderer::context::scoped_ffp const scoped_block(
			sys.renderer_ffp(),
			sys.renderer_ffp().onscreen_target()
		);

		sge::renderer::state::ffp::transform::object_scoped_ptr const transform_state(
			sys.renderer_ffp().create_transform_state(
				sge::renderer::state::ffp::transform::parameters(
					*sge::renderer::projection::orthogonal_viewport(
						scoped_block.get().target().viewport()
					)
				)
			)
		);

		sge::renderer::state::ffp::transform::scoped const scoped_transform(
			scoped_block.get(),
			sge::renderer::state::ffp::transform::mode::projection,
			*transform_state
		);

		scoped_block.get().clear(
			sge::renderer::clear::parameters()
			.back_buffer(
				sge::image::colors::black()
			)
		);

		current_strip.draw(
			scoped_block.get());

		border.draw(
			scoped_block.get());

		for(
			hole_vector::const_iterator it(
				holes.begin()
			);
			it != holes.end();
			++it
		)
			it->draw(
				scoped_block.get());
	}

	fcppt::io::cout()
		<< border
		<< FCPPT_TEXT('\n');

	for(
		hole_vector::const_iterator it(
			holes.begin()
		);
		it != holes.end();
		++it
	)
		fcppt::io::cout()
			<< *it
			<< FCPPT_TEXT('\n');

	return
		sys.window_system().exit_code();
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return awl::main::exit_failure();
}
