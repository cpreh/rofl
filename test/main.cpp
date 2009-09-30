
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
#include <rofl/graph/vertices_end.hpp>
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

	/*
	rofl::polygon kacke,kacke2;
	kacke.push_back(rofl::point(50,50,0));
	kacke.push_back(rofl::point(200,50,0));
	kacke.push_back(rofl::point(200,200,0));
	kacke.push_back(rofl::point(50,200,0));
	kacke2.push_back(rofl::point(75,75,0));
	kacke2.push_back(rofl::point(125,175,0));
	kacke2.push_back(rofl::point(175,75,0));
	
	rofl::polygon_with_holes polys(
		sge::assign::make_container<rofl::polygon>
			(rofl::point(50,50,0))
			(rofl::point(200,50,0))
			(rofl::point(200,200,0))
			(rofl::point(50,200,0))
	);
	
	polys.add_hole(
		sge::assign::make_container<rofl::polygon>
			(rofl::point(75,75,0))
			(rofl::point(125,175,0))
			(rofl::point(175,75,0))
	);
	*/
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
	
	typedef
	sge::line_strip::object<float,sge::image::color::rgba8>
	line_strip;
	
	typedef
	sge::line_strip::parameters<float,sge::image::color::rgba8>
	line_strip_params;
	
	std::vector<line_strip> strips;
	for(
		rofl::graph::const_vertex_iterator i = rofl::graph::vertices_begin(g);
		i != rofl::graph::vertices_end();
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
