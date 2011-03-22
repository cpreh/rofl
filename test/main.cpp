#include "line_strip/object.hpp"
#include "line_strip/parameters.hpp"
#include "line_strip/object_impl.hpp"
#include "line_strip/parameters_impl.hpp"
#include <rofl/polygon_with_holes.hpp>
#include <rofl/graph/vertices_begin.hpp>
#include <rofl/graph/simplify.hpp>
#include <rofl/graph/vertices_end.hpp>
#include <rofl/math/barycenter.hpp>
#include <rofl/polygon.hpp>
#include <rofl/consume.hpp>
#include <rofl/astar/generate_trail.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/running_to_false.hpp>
#include <sge/image/colors.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/input/keyboard/action.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/instance.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/input.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/matrix/orthogonal.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/io/cin.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <exception>
#include <vector>
#include <iterator>
#include <ostream>
#include <string>

#include <rofl/create_polygonizer.hpp>
#include <rofl/polygonizer.hpp>

#include <cstdlib>
#include <ctime>

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
	
template
<
	typename Graph,
	typename EdgeIterator,
	typename StripContainer
>
void push_edges(
	Graph const &g,
	EdgeIterator i,
	EdgeIterator const end,
	StripContainer &strips,
	sge::renderer::device_ptr const rend)
{
	for (; i != end; ++i)
	{
		typename StripContainer::value_type
			s(
				rend,
				line_strip_params()
					.color(
						line_strip::color(
							(mizuiro::color::init::red %= 1.)
							(mizuiro::color::init::green %= 0.)
							(mizuiro::color::init::blue %= 0.)
							(mizuiro::color::init::alpha %= 1.)
						)
					)
			);
		
		rofl::point const 
			&p0 = g[boost::source(*i,g)].barycenter(),
			&p1 = g[boost::target(*i,g)].barycenter();
			
		s.push_back(
			fcppt::math::vector::structure_cast<line_strip::point>(
				p0));
		s.push_back(
			fcppt::math::vector::structure_cast<line_strip::point>(
				p1));
				
		strips.push_back(
			s);
	}
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
				),
				sge::systems::cursor_option_field::null()
			)
		)
	);
	
	sge::renderer::device_ptr const rend = sys.renderer();


	bool running = true;

	fcppt::signal::scoped_connection const cb(
		sys.keyboard_collector()->key_callback(
			sge::input::keyboard::action(
				sge::input::keyboard::key_code::escape,
				sge::systems::running_to_false(
					running
				)
			)
		)
	);

	rend->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color::clear_color = sge::image::colors::black())
	);

#if 0
	rend->transform(
		sge::renderer::matrix_mode::world,
		sge::renderer::matrix_pixel_to_space<float>( 
			rend->screen_size()));
#endif
	rend->transform(
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
		
	std::vector<line_strip> strips;
	
	fcppt::io::cout 
		<< FCPPT_TEXT("Enter polygons in the format \"(p+)\" where p has the format \"(a,b)\".\n")
		<< FCPPT_TEXT("Border: \n");
	rofl::polygon border;
	fcppt::string line;
	std::getline(
		fcppt::io::cin,
		line);
	fcppt::io::istringstream ss(
		line);
	ss >> border;
	fcppt::io::cout 
		<< FCPPT_TEXT("The polygon entered was:")
		<< border 
		<< FCPPT_TEXT("\n");
	rofl::polygon_with_holes polys(
		border);
	fcppt::io::cout 
		<< FCPPT_TEXT("Now the holes. An empty line exits the input mode and starts the program:\n");
	while(true)
	{
		std::getline(
			fcppt::io::cin,
			line);
		if (line.empty())
			break;
		fcppt::io::istringstream ss(
			line);
		rofl::polygon hole;
		ss >> hole;
		if (!ss)
			fcppt::io::cerr << FCPPT_TEXT("Invalid input!");
		else
		{
			fcppt::io::cout << FCPPT_TEXT("The hole entered was: ") << hole << FCPPT_TEXT("\n");
			polys.add_hole(
				hole);
			line_strip 
				s(
					rend,
					line_strip_params()
						.style(
							sge::line_strip::style::loop));
							
			BOOST_FOREACH(rofl::polygon::const_reference r,hole)
				s.push_back(
					fcppt::math::vector::structure_cast<line_strip::point>(
						r));
					
			strips.push_back(
				s);
		}
	}
		
	rofl::graph::object g;
	rofl::create_polygonizer()->polygonize(
		polys,
		g);

	rofl::graph::simplify(
		g);
	
	for(
		rofl::graph::const_vertex_iterator i = rofl::graph::vertices_begin(g);
		i != rofl::graph::vertices_end(g);
		++i)
	{
		rofl::indexed_polygon const &p = 
			g[*i].polygon();
		
		line_strip 
			s(
				rend,
				line_strip_params()
					.style(
						sge::line_strip::style::loop
					)
					.color(
						line_strip::color(
							(mizuiro::color::init::red %= 0.)
							(mizuiro::color::init::green %= 0.)
							(mizuiro::color::init::blue %= 1.)
							(mizuiro::color::init::alpha %= 1.)
						)
					)
			);
		
		BOOST_FOREACH(rofl::indexed_polygon::const_reference r,p)
			s.push_back(
				fcppt::math::vector::structure_cast<line_strip::point>(
					r.representation()));
				
		strips.insert(
			strips.begin(),
			s);
	}
		
	push_edges(
		g,
		boost::edges(g).first,
		boost::edges(g).second,
		strips,
		rend);
	
	typedef boost::graph_traits<rofl::graph::object>::vertex_descriptor vertex;
	
	unsigned number_of_vertices = 
		std::distance(
			boost::vertices(g).first,
			boost::vertices(g).second);
	
	std::srand(
		std::time(
			0));
	
	vertex 
		start = 
			*boost::next(
				boost::vertices(g).first,
				std::rand() % number_of_vertices),
		end = 
			*boost::next(
				boost::vertices(g).first,
				std::rand() % number_of_vertices);
		
		
	rofl::astar::trail splist;
	rofl::astar::generate_trail(
		g,
		start,
		end,
		splist);
	
	//fcppt::io::cerr << splist.size() << " elements\n";
	
	line_strip path_strip(
		rend,
		line_strip_params()
			.color(
				line_strip::color(
					(mizuiro::color::init::red %= 0.)
					(mizuiro::color::init::green %= 1.)
					(mizuiro::color::init::blue %= 0.)
					(mizuiro::color::init::alpha %= 1.)
				)
			)
	);
	
	BOOST_FOREACH(rofl::astar::trail::const_reference r,splist)
		path_strip.push_back(
			g[r].barycenter());
	
	strips.push_back(
		path_strip);

	while(running)
	{
		sys.window()->dispatch();
		sge::renderer::scoped_block const block_(rend);
		BOOST_FOREACH(std::vector<line_strip>::reference r,strips)
			r.draw();
	}
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
