#include "line_strip/object.hpp"
#include "line_strip/parameters.hpp"
#include "line_strip/object_impl.hpp"
#include "line_strip/parameters_impl.hpp"
#include "line_strip_output.hpp"
#include "default_texture_creator.hpp"
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/image_loader.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/colors.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/input/cursor/button_event.hpp>
#include <sge/input/cursor/move_event.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/instance.hpp>
#include <sge/all_extensions.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/matrix/orthogonal.hpp>
#include <fcppt/math/almost_zero.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <exception>
#include <vector>
#include <ostream>

namespace
{

typedef
sge::line_strip::object
<
	float,
	sge::image::color::rgba8
>
line_strip;

typedef
sge::line_strip::parameters
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
	current_.back(
		fcppt::math::vector::structure_cast<
			line_strip::point
		>(
			_event.position()
		)
	);
}

}


int main()
try
{
	sge::window::dim const window_dim(
		1024,
		768
	);

	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::systems::window(
				sge::window::simple_parameters(
					FCPPT_TEXT("pathfinding test"),
					window_dim
				)
			)
		)
		(
			sge::systems::renderer(
				sge::renderer::parameters(
					sge::renderer::visual_depth::depth32,
					sge::renderer::depth_stencil_buffer::off,
					sge::renderer::vsync::on,
					sge::renderer::no_multi_sampling
				),
				sge::viewport::center_on_resize(
					window_dim
				)
			)
		)
		(
			sge::systems::input(
				sge::systems::input_helper_field(
					sge::systems::input_helper::keyboard_collector
				)
				|
				sge::systems::input_helper::cursor_demuxer,
				sge::systems::cursor_option_field::null()
			)
		)
		(
			sge::systems::image_loader(
				sge::image::capabilities_field::null(),
				sge::all_extensions
			)
		)
	);

	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector().key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running
				)
			)
		)
	);

	sys.renderer().state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color::clear_color = sge::image::colors::black())
	);

	sys.renderer().transform(
		sge::renderer::matrix_mode::projection,
		fcppt::math::matrix::orthogonal(
			static_cast<
				sge::renderer::scalar
			>(
				0
			),
			static_cast<
				sge::renderer::scalar
			>(
				window_dim.w()
			),
			static_cast<
				sge::renderer::scalar
			>(
				window_dim.h()
			),
			static_cast<
				sge::renderer::scalar
			>(
				0
			),
			static_cast<
				sge::renderer::scalar
			>(
				0
			),
			static_cast<
				sge::renderer::scalar
			>(
				1
			)
		)
	);

	line_strip border(
		sys.renderer(),
		line_strip_params()
			.style(
				sge::line_strip::style::loop)
			.color(
				line_strip::color(
					(mizuiro::color::init::red %= 1.)
					(mizuiro::color::init::green %= 0.)
					(mizuiro::color::init::blue %= 0.)
					(mizuiro::color::init::alpha %= 1.)
				)
			)
	);

	hole_vector holes;
	
	line_strip current_strip(
		sys.renderer(),
		line_strip_params()
			.style(
				sge::line_strip::style::loop)
			.color(
				line_strip::color(
					(mizuiro::color::init::red %= 1.)
					(mizuiro::color::init::green %= 1.)
					(mizuiro::color::init::blue %= 1.)
					(mizuiro::color::init::alpha %= 1.)
				)
			)
	);
	
	sge::bullet::test::default_texture_creator creator_(
		sys.image_loader(),
		sys.renderer());

	cursor_handler handler(
		sys.cursor_demuxer(),
		current_strip,
		border,
		holes
	);

	sys.renderer().state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color::clear_color = sge::image::colors::black()));
		
	while(running)
	{
		sys.window().dispatch();

		sge::renderer::scoped_block const block_(
			sys.renderer()
		);

		current_strip.draw();

		border.draw();

		BOOST_FOREACH(hole_vector::reference r,holes)
			r.draw();
	}

	fcppt::io::cout << border << FCPPT_TEXT('\n');

	BOOST_FOREACH(hole_vector::const_reference r,holes)
		fcppt::io::cout << r << FCPPT_TEXT('\n');
}
catch(fcppt::exception const &e)
{
	fcppt::io::cerr << e.string() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	fcppt::io::cerr << e.what() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
