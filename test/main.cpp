#include <fcppt/math/vector/input.hpp>
#include <fcppt/math/vector/output.hpp>
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
#include <sge/config/media_path.hpp>
#include <sge/image/colors.hpp>
#include <sge/assign/make_container.hpp>
#include <sge/signal/scoped_connection.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/scoped_block.hpp>
#include <sge/renderer/refresh_rate_dont_care.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/filter/linear.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/input/system.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length.hpp>
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
#include <sge/cout.hpp>
#include <sge/istringstream.hpp>
#include <sge/cin.hpp>
#include <sge/exception.hpp>
#include <sge/renderer/matrix_pixel_to_space.hpp>
#include <fcppt/math/matrix/orthogonal_xy.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/vector_property_map.hpp>
#include <cstdlib>
#include <exception>
#include <ostream>

#include <rofl/create_polygonizer.hpp>
#include <rofl/polygonizer.hpp>

#include <sge/assign/make_array.hpp>

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
								mizuiro::color::init::red %= 1.0f,
								mizuiro::color::init::green %= 0.0,
								mizuiro::color::init::blue %= 0.0,
								mizuiro::color::init::alpha %= 1.0f )));
		
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
		(sge::systems::parameterless::input)
		(sge::systems::parameterless::image)
	);
	
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

	rend->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color::clear_color = sge::image::colors::black())
	);

	rend->transform(
		sge::renderer::matrix_pixel_to_space<float>( 
			rend->screen_size()));
	rend->projection(
		fcppt::math::matrix::orthogonal_xy<float>());
		
	std::vector<line_strip> strips;
	
	sge::cout 
		<< FCPPT_TEXT("Enter polygons in the format \"(p+)\" where p has the format \"(a,b)\".\n")
		<< FCPPT_TEXT("Border: \n");
	rofl::polygon border;
	sge::string line;
	std::getline(
		sge::cin,
		line);
	sge::istringstream ss(
		line);
	ss >> border;
	sge::cout 
		<< FCPPT_TEXT("The polygon entered was:")
		<< border 
		<< FCPPT_TEXT("\n");
	rofl::polygon_with_holes polys(
		border);
	sge::cout 
		<< FCPPT_TEXT("Now the holes. An empty line exits the input mode and starts the program:\n");
	while(true)
	{
		std::getline(
			sge::cin,
			line);
		if (line.empty())
			break;
		sge::istringstream ss(
			line);
		rofl::polygon hole;
		ss >> hole;
		if (!ss)
			sge::cerr << FCPPT_TEXT("Invalid input!");
		else
		{
			sge::cout << FCPPT_TEXT("The hole entered was: ") << hole << SGE_TEXT("\n");
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
						sge::line_strip::style::loop)
					.color(
						line_strip::color(
								mizuiro::color::init::red %= 0.0f,
								mizuiro::color::init::green %= 0.0,
								mizuiro::color::init::blue %= 1.0,
								mizuiro::color::init::alpha %= 1.0f )));
		
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
	
	//sge::cerr << splist.size() << " elements\n";
	
	line_strip path_strip(
			rend,
			line_strip_params()
				.color(
					line_strip::color(
							mizuiro::color::init::red %= 0.0f,
							mizuiro::color::init::green %= 1.0,
							mizuiro::color::init::blue %= 0.0,
							mizuiro::color::init::alpha %= 1.0f )));
		
	BOOST_FOREACH(rofl::astar::trail::const_reference r,splist)
		path_strip.push_back(
			g[r].barycenter());
	
	strips.push_back(
		path_strip);

	while(running)
	{
		sge::mainloop::dispatch();
		sge::renderer::scoped_block const block_(rend);
		BOOST_FOREACH(std::vector<line_strip>::reference r,strips)
			r.draw();
	}
}
catch(sge::exception const &e)
{
	sge::cerr << e.string() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	sge::cerr << e.what() << FCPPT_TEXT('\n');
	return EXIT_FAILURE;
}
