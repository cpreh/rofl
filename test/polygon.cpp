#include "line_strip/object.hpp"
#include "line_strip/parameters.hpp"
#include "line_strip/object_impl.hpp"
#include "line_strip/parameters_impl.hpp"
#include "default_texture_creator.hpp"
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/colors.hpp>
#include <sge/assign/make_container.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/input/system.hpp>
#include <sge/math/vector/structure_cast.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/length.hpp>
#include <sge/input/action.hpp>
#include <sge/image/loader.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/parameters.hpp>
#include <sge/sprite/texture_animation.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/default_creator.hpp>
#include <sge/texture/default_creator_impl.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/time/second.hpp>
#include <sge/time/resolution.hpp>
#include <sge/mainloop/dispatch.hpp>
#include <sge/cerr.hpp>
#include <sge/exception.hpp>
#include <sge/renderer/matrix_pixel_to_space.hpp>
#include <sge/math/matrix/orthogonal_xy.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/vector_property_map.hpp>
#include <cstdlib>
#include <exception>
#include <ostream>


#include <sge/assign/make_array.hpp>

#include <cstdlib>
#include <ctime>
#include <sge/input/key_pair.hpp>
#include <sge/math/almost_zero.hpp>

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

sge::math::vector::static_
<
	sge::input::key_state,
	2
>::type
mouse_delta(
	sge::input::key_pair const &p)
{
	return 
		sge::math::vector::static_
		<
			sge::input::key_state,
			2
		>::type(
			p.key().code() == sge::input::kc::mouse_x_axis 
			? 
				p.value() 
			: 
				sge::math::null<sge::input::key_state>(),
			p.key().code() == sge::input::kc::mouse_y_axis 
			? 
				p.value() 
			: 
				sge::math::null<sge::input::key_state>());
}

class mouse_handler
{
public:
	mouse_handler(
		sge::input::system_ptr,
		line_strip &current,
		line_strip &border,
		hole_vector &holes,
		sge::sprite::object &);
private:
	line_strip &current_;
	line_strip &border_;
	hole_vector &holes_;
	bool has_border_;
	sge::signal::scoped_connection connection_;
	sge::sprite::object &cursor_sprite_;
	
	void
	callback(
		sge::input::key_pair const &);
};

mouse_handler::mouse_handler(
	sge::input::system_ptr _is,
	line_strip &_current,
	line_strip &_border,
	hole_vector &_holes,
	sge::sprite::object &_cursor_sprite)
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
		line_strip::point::null());
	cursor_sprite_.pos() = 
		sge::sprite::point::null();
}

void
mouse_handler::callback(
	sge::input::key_pair const &p)
{
	if(
		p.key().code() == sge::input::kc::mouse_x_axis || 
		p.key().code() == sge::input::kc::mouse_y_axis)
	{
		cursor_sprite_.pos() += 
			sge::math::vector::structure_cast<sge::sprite::point>(
				mouse_delta(
					p));
		current_.back(
			sge::math::vector::structure_cast<line_strip::point>(
				cursor_sprite_.pos()));
		return;
	}
	
	if (sge::math::almost_zero(p.value()))
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
		(sge::window::parameters(
			SGE_TEXT("pathfinding test")
		))
		(sge::renderer::parameters(
			sge::renderer::display_mode(
				sge::renderer::screen_size(
					1024,
					768),
				sge::renderer::bit_depth::depth32,
				sge::renderer::refresh_rate_dont_care),
			sge::renderer::depth_buffer::off,
			sge::renderer::stencil_buffer::off,
			sge::renderer::window_mode::windowed))
		(sge::systems::parameterless::input)
		(sge::systems::parameterless::image));
	
	sge::input::system_ptr const    is   = sys.input_system();
	sge::renderer::device_ptr const rend = sys.renderer();
	sge::image::loader_ptr const    pl   = sys.image_loader();

	bool running = true;

	sge::signal::scoped_connection const cb(
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
		sge::renderer::matrix_pixel_to_space<float>( 
			sys.renderer()->screen_size()));
	sys.renderer()->projection(
		sge::math::matrix::orthogonal_xy<float>());

	sge::sprite::system ss(
		sys.renderer());
		
	line_strip border(
			sys.renderer(),
			line_strip_params()
				.style(
					sge::line_strip::style::loop)
				.color(
					line_strip::color(
							mizuiro::color::init::red %= 1.0f,
							mizuiro::color::init::green %= 0.0,
							mizuiro::color::init::blue %= 0.0,
							mizuiro::color::init::alpha %= 1.0f)));

	hole_vector holes;
	
	line_strip current_strip(
			sys.renderer(),
			line_strip_params()
				.style(
					sge::line_strip::style::loop)
				.color(
					line_strip::color(
							mizuiro::color::init::red %= 1.0f,
							mizuiro::color::init::green %= 1.0,
							mizuiro::color::init::blue %= 1.0,
							mizuiro::color::init::alpha %= 1.0f )));
	
	sge::bullet::test::default_texture_creator creator_(
		sys.image_loader(),
		sys.renderer());

	sge::sprite::object cursor_sprite(
		sge::sprite::parameters()
		.pos(
			sge::sprite::point(0,0))
		.texture(
				creator_.load(
					sge::config::media_path()/SGE_TEXT("gui")/SGE_TEXT("cursor.png"))));

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
		sge::renderer::scoped_block const block_(sys.renderer());
		ss.render(
			&cursor_sprite,
			&cursor_sprite+1);
		current_strip.draw();
		border.draw();
		BOOST_FOREACH(hole_vector::reference r,holes)
			r.draw();
	}

	// FIXME: serialize border and holes here!
}
catch(sge::exception const &e)
{
	sge::cerr << e.string() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
