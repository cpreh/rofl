#include "line_strip/object.hpp"
#include "line_strip/parameters.hpp"
#include "line_strip/object_impl.hpp"
#include "line_strip/parameters_impl.hpp"
#include <rofl/polygon_with_holes.hpp>
#include <rofl/graph/vertices_begin.hpp>
#include <rofl/graph/simplify.hpp>
#include <rofl/graph/vertices_end.hpp>
#include <rofl/math/barycenter.hpp>
#include <rofl/math/polygon_input.hpp>
#include <rofl/math/polygon_output.hpp>
#include <rofl/polygon.hpp>
#include <rofl/consume.hpp>
#include <rofl/astar/generate_trail.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/keyboard_collector.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
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
#include <sge/viewport/center_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/object.hpp>
#include <sge/window/parameters.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/input.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/io/cin.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <exception>
#include <vector>
#include <iterator>
#include <iostream>
#include <ostream>
#include <string>

#include <rofl/create_polygonizer.hpp>
#include <rofl/polygonizer.hpp>

#include <ctime>

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
	sge::renderer::device::core &rend)
{
	for (; i != end; ++i)
	{
		typename StripContainer::value_type
			s(
				rend,
				line_strip_params()
					.color(
						line_strip::color(
							(mizuiro::color::init::red() %= 1.)
							(mizuiro::color::init::green() %= 0.)
							(mizuiro::color::init::blue() %= 0.)
							(mizuiro::color::init::alpha() %= 1.)
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
		boost::mpl::vector3<
			sge::systems::with_window,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_input<
				boost::mpl::vector1<
					sge::systems::keyboard_collector
				>
			>
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
			.dont_show()
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
	);

	fcppt::signal::scoped_connection const escape_connection(
		sge::systems::quit_on_escape(
			sys
		)
	);

	std::vector<line_strip> strips;

	fcppt::io::cout()
		<< FCPPT_TEXT("Enter polygons in the format \"(p+)\" where p has the format \"(a,b)\".\n")
		<< FCPPT_TEXT("Border: \n");

	rofl::polygon border;

	fcppt::string line;

	while(
		std::getline(
			fcppt::io::cin(),
			line
		)
	)
	{
		fcppt::io::istringstream ss(
			line
		);

		if(
			ss >> border
		)
			break;

		fcppt::io::cerr()
			<< FCPPT_TEXT("Invalid border!\n");
	}

	fcppt::io::cout()
		<< FCPPT_TEXT("The polygon border entered was:")
		<< border
		<< FCPPT_TEXT('\n');

	rofl::polygon_with_holes polys(
		border
	);

	fcppt::io::cout()
		<< FCPPT_TEXT("Now the holes. An empty line exits the input mode and starts the program:\n");
	while(
		std::getline(
			fcppt::io::cin(),
			line
		)
	)
	{
		if (line.empty())
			break;

		fcppt::io::istringstream ss(
			line);

		rofl::polygon hole;

		if(
			!(ss >> hole)
		)
		{
			fcppt::io::cerr()
				<< FCPPT_TEXT("Invalid input!");

			continue;
		}

		fcppt::io::cout()
			<< FCPPT_TEXT("The hole entered was: ")
			<< hole
			<< FCPPT_TEXT("\n");

		polys.add_hole(
			hole);

		line_strip
			s(
				sys.renderer_core(),
				line_strip_params()
					.style(
						rofl::line_strip::style::loop));

		BOOST_FOREACH(rofl::polygon::const_reference r,hole)
			s.push_back(
				fcppt::math::vector::structure_cast<line_strip::point>(
					r));

		strips.push_back(
			s);
	}

	rofl::graph::object g;
	rofl::create_polygonizer()->polygonize(
		polys,
		g);

	/*
	rofl::graph::simplify(
		g);
	*/

	for(
		rofl::graph::const_vertex_iterator i = rofl::graph::vertices_begin(g);
		i != rofl::graph::vertices_end(g);
		++i)
	{
		rofl::indexed_polygon const &p =
			g[*i].polygon();

		line_strip
			s(
				sys.renderer_core(),
				line_strip_params()
					.style(
						rofl::line_strip::style::loop
					)
					.color(
						line_strip::color(
							(mizuiro::color::init::red() %= 0.)
							(mizuiro::color::init::green() %= 0.)
							(mizuiro::color::init::blue() %= 1.)
							(mizuiro::color::init::alpha() %= 1.)
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
		sys.renderer_core());

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


	rofl::astar::trail splist(
		rofl::astar::generate_trail(
			g,
			start,
			end
		)
	);

	//fcppt::io::cerr << splist.size() << " elements\n";

	line_strip path_strip(
		sys.renderer_core(),
		line_strip_params()
			.color(
				line_strip::color(
					(mizuiro::color::init::red() %= 0.)
					(mizuiro::color::init::green() %= 1.)
					(mizuiro::color::init::blue() %= 0.)
					(mizuiro::color::init::alpha() %= 1.)
				)
			)
	);

	BOOST_FOREACH(rofl::astar::trail::const_reference r,splist)
		path_strip.push_back(
			g[r].barycenter());

	strips.push_back(
		path_strip);

	sys.window().show();

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
				sge::image::color::predef::black()
			)
		);


		BOOST_FOREACH(std::vector<line_strip>::reference r,strips)
			r.draw(
				scoped_block.get());
	}

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
