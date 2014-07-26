#include <rofl/create_polygonizer.hpp>
#include <rofl/polygonizer.hpp>
#include <rofl/polygon.hpp>
#include <rofl/polygon_with_holes.hpp>
#include <rofl/astar/generate_trail.hpp>
#include <rofl/graph/object.hpp>
#include <rofl/graph/simplify.hpp>
#include <rofl/graph/vertex_descriptor.hpp>
#include <rofl/graph/vertex_iterator.hpp>
#include <rofl/graph/vertices_begin.hpp>
#include <rofl/graph/vertices_end.hpp>
#include <rofl/line_strip/object.hpp>
#include <rofl/line_strip/parameters.hpp>
#include <rofl/line_strip/object_impl.hpp>
#include <rofl/line_strip/parameters_impl.hpp>
#include <rofl/math/barycenter.hpp>
#include <rofl/math/polygon_input.hpp>
#include <rofl/math/polygon_output.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/keyboard_collector.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/projection/orthogonal_viewport.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/state/ffp/transform/scoped.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport_is_null.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/viewport/center_on_resize.hpp>
#include <sge/window/dim.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system.hpp>
#include <sge/window/title.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/assert/error.hpp>
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
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>
#include <fcppt/random/generator/minstd_rand.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <exception>
#include <iterator>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


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
void
push_edges(
	Graph const &_graph,
	EdgeIterator const _begin,
	EdgeIterator const _end,
	StripContainer &_strips,
	sge::renderer::device::core &_rend
)
{
	for(
		EdgeIterator it(
			_begin
		);
		it != _end;
		++it
	)
	{
		typename StripContainer::value_type
			strip(
				_rend,
				line_strip_params()
					.color(
						line_strip::color(
							(sge::image::color::init::red() %= 1.)
							(sge::image::color::init::green() %= 0.)
							(sge::image::color::init::blue() %= 0.)
							(sge::image::color::init::alpha() %= 1.)
						)
					)
			);

		rofl::point const
			&p0(
				_graph[
					boost::source(
						*it,
						_graph
					)
				].barycenter()
			),
			&p1(
				_graph[
					boost::target(
						*it,
						_graph
					)
				].barycenter()
			);

		strip.push_back(
			fcppt::math::vector::structure_cast<
				line_strip::point
			>(
				p0
			)
		);

		strip.push_back(
			fcppt::math::vector::structure_cast<
				line_strip::point
			>(
				p1
			)
		);

		_strips.push_back(
			std::move(
				strip
			)
		);
	}
}

}

awl::main::exit_code const
test_main(
	awl::main::function_context const &
);

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
				sge::systems::original_window(
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
				sge::renderer::pixel_format::object(
					sge::renderer::pixel_format::color::depth32,
					sge::renderer::pixel_format::depth_stencil::off,
					sge::renderer::pixel_format::optional_multi_samples(),
					sge::renderer::pixel_format::srgb::no
				),
				sge::renderer::display_mode::parameters(
					sge::renderer::display_mode::vsync::on,
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

	std::vector<
		line_strip
	> strips;

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
		if(
			line.empty()
		)
			break;

		fcppt::io::istringstream ss(
			line
		);

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
			hole
		);

		line_strip
			strip(
				sys.renderer_device_core(),
				line_strip_params()
					.style(
						rofl::line_strip::style::loop
					)
			);

		for(
			rofl::polygon::const_reference elem : hole
		)
			strip.push_back(
				fcppt::math::vector::structure_cast<
					line_strip::point
				>(
					elem
				)
			);

		strips.push_back(
			std::move(
				strip
			)
		);
	}

	rofl::graph::object graph;

	rofl::create_polygonizer()->polygonize(
		polys,
		graph
	);

	/*
	rofl::graph::simplify(
		g);
	*/

	for(
		rofl::graph::const_vertex_iterator it(
			rofl::graph::vertices_begin(
				graph
			)
		);
		it
		!=
		rofl::graph::vertices_end(
			graph
		);
		++it
	)
	{
		rofl::indexed_polygon const &poly(
			graph[
				*it
			].polygon()
		);

		line_strip
			strip(
				sys.renderer_device_core(),
				line_strip_params()
					.style(
						rofl::line_strip::style::loop
					)
					.color(
						line_strip::color(
							(sge::image::color::init::red() %= 0.)
							(sge::image::color::init::green() %= 0.)
							(sge::image::color::init::blue() %= 1.)
							(sge::image::color::init::alpha() %= 1.)
						)
					)
			);

		for(
			rofl::indexed_polygon::const_reference elem : poly
		)
			strip.push_back(
				fcppt::math::vector::structure_cast<
					line_strip::point
				>(
					elem.representation()
				)
			);

		strips.insert(
			strips.begin(),
			std::move(
				strip
			)
		);
	}

	push_edges(
		graph,
		boost::edges(
			graph
		).first,
		boost::edges(
			graph
		).second,
		strips,
		sys.renderer_device_core()
	);

	typedef fcppt::random::generator::minstd_rand generator_type;

	generator_type generator(
		fcppt::random::generator::seed_from_chrono<
			generator_type::seed
		>()
	);

	typedef std::iterator_traits<
		rofl::graph::vertex_iterator
	>::difference_type iterator_difference;

	iterator_difference const num_vertices(
		std::distance(
			boost::vertices(
				graph
			).first,
			boost::vertices(
				graph
			).second
		)
	);

	FCPPT_ASSERT_ERROR(
		num_vertices > 0
	);

	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			iterator_difference
		>
	> uniform_int_type;

	fcppt::random::variate<
		generator_type,
		uniform_int_type
	> gen(
		generator,
		uniform_int_type(
			uniform_int_type::param_type::min(
				0
			),
			uniform_int_type::param_type::max(
				num_vertices
				- 1
			)
		)
	);

	rofl::graph::vertex_descriptor
		start =
			*std::next(
				boost::vertices(
					graph
				).first,
				gen()
			),
		end =
			*std::next(
				boost::vertices(
					graph
				).first,
				gen()
			);

	rofl::astar::trail trail(
		rofl::astar::generate_trail(
			graph,
			start,
			end
		)
	);

	//fcppt::io::cerr << trail.size() << " elements\n";

	{
		line_strip path_strip(
			sys.renderer_device_core(),
			line_strip_params()
				.color(
					line_strip::color(
						(sge::image::color::init::red() %= 0.)
						(sge::image::color::init::green() %= 1.)
						(sge::image::color::init::blue() %= 0.)
						(sge::image::color::init::alpha() %= 1.)
					)
				)
		);

		for(
			rofl::astar::trail::const_reference elem : trail
		)
			path_strip.push_back(
				graph[
					elem
				].barycenter()
			);

		strips.push_back(
			std::move(
				path_strip
			)
		);
	}

	sys.window().show();

	while(
		sys.window_system().poll()
	)
	{
		if(
			sge::renderer::target::viewport_is_null(
				sys.renderer_device_ffp().onscreen_target().viewport()
			)
		)
			continue;

		sge::renderer::context::scoped_ffp const scoped_block(
			sys.renderer_device_ffp(),
			sys.renderer_device_ffp().onscreen_target()
		);

		sge::renderer::state::ffp::transform::object_unique_ptr const transform_state(
			sys.renderer_device_ffp().create_transform_state(
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


		for(
			auto const &elem : strips
		)
			elem.draw(
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
