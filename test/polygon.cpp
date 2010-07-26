#include "line_strip/object.hpp"
#include "line_strip/parameters.hpp"
#include "line_strip/object_impl.hpp"
#include "line_strip/parameters_impl.hpp"
#include "line_strip_output.hpp"
#include "default_texture_creator.hpp"
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/image_loader.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/colors.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/matrix_pixel_to_space.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/input/system.hpp>
#include <sge/input/action.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/no_color.hpp>
#include <sge/sprite/choices.hpp>
#include <sge/sprite/type_choices.hpp>
#include <sge/sprite/with_texture.hpp>
#include <sge/sprite/render_one.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/all_extensions.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/matrix/orthogonal_xy.hpp>
#include <fcppt/math/almost_zero.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <exception>
#include <vector>
#include <ostream>

namespace
{

typedef sge::sprite::choices<
	sge::sprite::type_choices<
		int,
		float,
		sge::sprite::no_color
	>,
	boost::mpl::vector1<
		sge::sprite::with_texture
	>
> sprite_choices;

typedef sge::sprite::object<
	sprite_choices
> sprite_object;

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

fcppt::math::vector::static_
<
	sge::input::key_state,
	2
>::type
mouse_delta(
	sge::input::key_pair const &p)
{
	return 
		fcppt::math::vector::static_
		<
			sge::input::key_state,
			2
		>::type(
			p.key().code() == sge::input::kc::mouse_x_axis 
			? 
				p.value() 
			: 
				fcppt::math::null<sge::input::key_state>(),
			p.key().code() == sge::input::kc::mouse_y_axis 
			? 
				p.value() 
			: 
				fcppt::math::null<sge::input::key_state>());
}

class mouse_handler
{
public:
	mouse_handler(
		sge::input::system_ptr,
		line_strip &current,
		line_strip &border,
		hole_vector &holes,
		sprite_object &
	);
private:
	line_strip &current_;
	line_strip &border_;
	hole_vector &holes_;
	bool has_border_;
	fcppt::signal::scoped_connection connection_;
	sprite_object &cursor_sprite_;
	
	void
	callback(
		sge::input::key_pair const &);
};

mouse_handler::mouse_handler(
	sge::input::system_ptr _is,
	line_strip &_current,
	line_strip &_border,
	hole_vector &_holes,
	sprite_object &_cursor_sprite)
:
	current_(
		_current),
	border_(
		_border),
	holes_(
		_holes),
	has_border_(
		false),
	connection_(
		_is->register_callback(
			std::tr1::bind(
				&mouse_handler::callback,
				this,
				std::tr1::placeholders::_1))),
	cursor_sprite_(
		_cursor_sprite)
{
	current_.push_back(
		line_strip::point::null()
	);

	cursor_sprite_.pos( 
		sprite_object::point::null()
	);
}

void
mouse_handler::callback(
	sge::input::key_pair const &p)
{
	if(
		p.key().code() == sge::input::kc::mouse_x_axis || 
		p.key().code() == sge::input::kc::mouse_y_axis)
	{
		cursor_sprite_.pos(
			cursor_sprite_.pos()
			+ 
			fcppt::math::vector::structure_cast<
				sprite_object::point
			>(
				mouse_delta(
					p
				)
			)
		);

		current_.back(
			fcppt::math::vector::structure_cast<line_strip::point>(
				cursor_sprite_.pos()));
		return;
	}
	
	if (fcppt::math::almost_zero(p.value()))
		return;

	if (p.key().code() == sge::input::kc::mouse_l)
	{
		current_.push_back(
			current_.points().back());
		return;
	}
	
	if (p.key().code() == sge::input::kc::mouse_r)
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
	}
}

}


int main()
try
{
	sge::systems::instance const sys(
		sge::systems::list()
		(
			sge::window::parameters(
				FCPPT_TEXT("pathfinding test")
			)
		)
		(
			sge::renderer::parameters(
				sge::renderer::display_mode(
					sge::renderer::screen_size(
						1024,
						768
					),
					sge::renderer::bit_depth::depth32,
					sge::renderer::refresh_rate_dont_care
				),
				sge::renderer::depth_buffer::off,
				sge::renderer::stencil_buffer::off,
				sge::renderer::window_mode::windowed,
				sge::renderer::vsync::on,
				sge::renderer::no_multi_sampling
			)
		)	
		(
			sge::systems::parameterless::input
		)
		(
			sge::systems::image_loader(
				sge::image::capabilities_field::null(),
				sge::all_extensions
			)
		)
	);

	sge::input::system_ptr const    is   = sys.input_system();
	sge::renderer::device_ptr const rend = sys.renderer();

	bool running = true;

	fcppt::signal::scoped_connection const cb(
		is->register_callback(
			sge::input::action(
				sge::input::kc::key_escape,
				boost::phoenix::ref(running) = false
			)
		)
	);

	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color::clear_color = sge::image::colors::black())
	);

	sys.renderer()->transform(
		sge::renderer::matrix_mode::world,
		sge::renderer::matrix_pixel_to_space<float>( 
			sys.renderer()->screen_size()));
	sys.renderer()->transform(
		sge::renderer::matrix_mode::projection,
		fcppt::math::matrix::orthogonal_xy<float>());

	typedef sge::sprite::system<
		sprite_choices
	>::type sprite_system;

	sprite_system ss(
		sys.renderer());
		
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

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	sprite_object cursor_sprite(
		sprite_parameters()
		.pos(
			sprite_object::point::null()
		)
		.texture(
			creator_.load(
				sge::config::media_path()/FCPPT_TEXT("gui")/FCPPT_TEXT("cursor.png")
			)
		)
		.texture_size()
		.elements()
	);

	mouse_handler m(
		sys.input_system(),
		current_strip,
		border,
		holes,
		cursor_sprite);

	// this is set by sprite::system as well, but rather set it here explicitly
	sys.renderer()->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color::clear_color = sge::image::colors::black()));
		
	while(running)
	{
		sge::mainloop::dispatch();
		sge::renderer::scoped_block const block_(
			sys.renderer()
		);

		sge::sprite::render_one(
			ss,
			cursor_sprite
		);

		current_strip.draw();

		border.draw();

		BOOST_FOREACH(hole_vector::reference r,holes)
			r.draw();
	}

	fcppt::io::cout << border << "\n";
	BOOST_FOREACH(hole_vector::const_reference r,holes)
		fcppt::io::cout << r << "\n";
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
