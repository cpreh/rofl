#include <rofl/astar/generate_path.hpp>
#include <rofl/line_segment.hpp>
#include <sge/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/next_prior.hpp>

void 
rofl::astar::generate_path(
	graph::object const &g,
	trail const &t,
	point const &start,
	point const &end,
	path &p)
{
	/*
	SGE_ASSERT(
		!t.empty());
		
	if (t.size() == 1)
	{
		p.push_back(
			start);
		p.push_back(
			end);
		return;
	}
	
	point last_point = 
		start;
	graph::vertex_descriptor last_vertex = 
		t.front();

	for(
		trail::const_iterator i = 
			boost::next(
				t.begin()); 
		i != t.end(); 
		++i)
	{
		line_segment const &r = 
			g[boost::edge(
				last_vertex,
				*i,
				g)].adjacent_edge();
	
		if (!math::line_segments_intersect(l,r))
			break;
	}
	*/
}
