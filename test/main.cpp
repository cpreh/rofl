
/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

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
#include <sge/log/global.hpp>
#include <sge/log/logger.hpp>
#include <sge/cerr.hpp>
#include <sge/exception.hpp>
#include <sge/renderer/matrix_pixel_to_space.hpp>
#include <sge/math/matrix/orthogonal_xy.hpp>
#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <boost/assign/list_of.hpp>
#include <cstdlib>
#include <exception>
#include <ostream>

#include <GL/glu.h>
#include <rofl/create_polygonizer.hpp>
#include <rofl/polygonizer.hpp>

#include <sge/assign/make_array.hpp>

#include <boost/graph/astar_search.hpp>
#include <cstdlib>
#include <ctime>

namespace
{
typedef
sge::line_strip::object<float,sge::image::color::rgba8>
line_strip;

typedef
sge::line_strip::parameters<float,sge::image::color::rgba8>
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
			sge::math::vector::structure_cast<line_strip::point>(
				p0));
		s.push_back(
			sge::math::vector::structure_cast<line_strip::point>(
				p1));
				
		strips.push_back(
			s);
	}
}

template
<
	typename Graph,
	typename Unit
>
class heuristic
{
public:
	typedef 
	Graph 
	graph;
	
	typedef 
	Unit
	unit;
	
	typedef typename
	boost::graph_traits<graph>::vertex_descriptor
	vertex;
	
	heuristic(
		graph const &,
		vertex const &);
		
	unit
	operator()(
		vertex const &) const;
private:
	graph const &graph_;
	vertex destination_;
};

template
<
	typename Graph,
	typename Unit
>
heuristic<Graph,Unit>::heuristic(
	graph const &_graph,
	vertex const &_destination)
:
	graph_(
		_graph),
	destination_(
		_destination)
{
}

template
<
	typename Graph,
	typename Unit
>
typename 
heuristic<Graph,Unit>::unit
heuristic<Graph,Unit>::operator()(
	vertex const &v) const
{
	return 
		sge::math::vector::length(
			graph_[v].barycenter()-graph_[destination_].barycenter());
}

class found_goal {};

template
<
	typename Vertex
>
class goal_visitor
:
	public boost::default_astar_visitor
{
public:
	goal_visitor(
		Vertex const &);
	template<typename Graph>
	void examine_vertex(
		Vertex const &,
		Graph const &);
private:
	Vertex goal_;
};

template<typename Vertex>
goal_visitor<Vertex>::goal_visitor(
	Vertex const &_goal)
:
	goal_(
		_goal)
{
}

template<typename Vertex>
template<typename Graph>
void 
goal_visitor<Vertex>::examine_vertex(
	Vertex const &v,
	Graph const &)
{
	if (v == goal_)
		throw found_goal();
}

template
<
	typename Graph,
	typename List
>
void astar_search(
	Graph const &g,
	typename boost::graph_traits<Graph>::vertex_descriptor const &start,
	typename boost::graph_traits<Graph>::vertex_descriptor const &goal,
	List &path)
{
	typedef typename
	boost::graph_traits<Graph>::vertex_descriptor
	vertex;
	
	typedef 
	std::vector
	<
		vertex
	>
	predecessors;
	
	predecessors p(
		boost::num_vertices(
			g));
	
	try
	{
		boost::astar_search(
			g,
			start,
			heuristic<Graph,rofl::unit>(
				g,
				goal),
			boost::predecessor_map(
				&p[0]).
			visitor(
				goal_visitor<vertex>(
					goal)).
			weight_map(
				boost::get(
					&rofl::graph::edge_properties::length,
					g)));
	}
	catch (found_goal const &)
	{
		sge::cerr << SGE_TEXT("found a goal\n");
	}
	
	for (vertex v = goal;;v = p[v])
	{
		path.push_front(
			v);
		if (p[v] == v)
			break;
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

	rend->state(
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::color::clear_color = sge::image::colors::black())
	);

	rend->transform(
		sge::renderer::matrix_pixel_to_space<float>( 
			rend->screen_size()));
	rend->projection(
		sge::math::matrix::orthogonal_xy<float>());
		
	rofl::polygon_with_holes polys(
		sge::assign::make_container<rofl::polygon>
			(rofl::point(10,10,0))
			(rofl::point(10,700,0))
			(rofl::point(700,700,0))
			(rofl::point(700,10,0))
	);
	
	polys.add_hole(
		sge::assign::make_container<rofl::polygon>
			(rofl::point(50,50,0))
			(rofl::point(400,50,0))
			(rofl::point(400,400,0))
			(rofl::point(50,400,0))
	);
	
	rofl::graph::object g;
	rofl::create_polygonizer()->polygonize(
		polys,
		g);
	
	std::vector<line_strip> strips;
	for(
		rofl::graph::const_vertex_iterator i = rofl::graph::vertices_begin(g);
		i != rofl::graph::vertices_end(g);
		++i)
	{
		rofl::polygon const &p = 
			g[*i].polygon();
		SGE_ASSERT(
			p.size() == static_cast<rofl::polygon::size_type>(3));
		
		line_strip 
			s(
				rend,
				line_strip_params()
					.style(
						sge::line_strip::style::loop));
		
		s.push_back(
			sge::math::vector::structure_cast<line_strip::point>(
				p[0]));
		s.push_back(
			sge::math::vector::structure_cast<line_strip::point>(
				p[1]));
		s.push_back(
			sge::math::vector::structure_cast<line_strip::point>(
				p[2]));
				
		strips.push_back(
			s);
	}

	rofl::graph::simplify(
		g);
/*
	push_edges(
		g,
		boost::edges(g).first,
		boost::edges(g).second,
		strips,
		rend);
		*/
	
		/*
	typedef boost::graph_traits<rofl::graph::object>::vertex_descriptor vertex;
	
	unsigned number_of_vertices = 
		std::distance(
			boost::vertices(g).first,
			boost::vertices(g).second);
	
	std::srand(
		std::time(0));
	
	vertex 
		start = 
			*boost::next(
				boost::vertices(g).first,
				std::rand() % number_of_vertices),
		end = 
			*boost::next(
				boost::vertices(g).first,
				std::rand() % number_of_vertices);
		
		
	typedef std::list<vertex> path_list;
	path_list splist;
	astar_search(
		g,
		start,
		end,
		splist);
	
	line_strip path_strip(
			rend,
			line_strip_params()
				.color(
					line_strip::color(
							mizuiro::color::init::red %= 0.0f,
							mizuiro::color::init::green %= 1.0,
							mizuiro::color::init::blue %= 0.0,
							mizuiro::color::init::alpha %= 1.0f )));
		
	BOOST_FOREACH(path_list::const_reference r,splist)
		path_strip.push_back(
			g[r].barycenter());
	
	strips.push_back(
		path_strip);
		*/

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
	sge::cerr << e.string() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
catch(std::exception const &e)
{
	sge::cerr << e.what() << SGE_TEXT('\n');
	return EXIT_FAILURE;
}
