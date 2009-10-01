#include <rofl/graph/simplify.hpp>
#include <rofl/graph/edge_iterator.hpp>
#include <sge/assert.hpp>

namespace
{
#if 0
int area_sign(
	rofl::point const &a,
	rofl::point const &b,
	rofl::point const &c)
{
	rofl::point::value_type area2 = 
		(b[0] - a[0]) * (c[1] - a[1]) -
		(c[0] - a[0]) * (b[1] - a[1]);

    if (area2 > static_cast<rofl::point::value_type>(0.5)) 
		return 1;
	return 
		area2 < static_cast<rofl::point::value_type>(-0.5)
		?
			-1
		: 
			0;

}
	
bool left_on(
	rofl::point const &a,
	rofl::point const &b,
	rofl::point const &c)
{
	return 
		area_sign(
			a,
			b,
			c) >= 0;
}

rofl::point const find_previous(
	rofl::polygon const &p,
	rofl::point const &a,
	rofl::point const &b)
{
	for (rofl::polygon::const_iterator i = p.begin(); i != p.end(); ++i)
	{
		if (*i != a)
			continue;
		
		rofl::point const 
			&next = 
				i == boost::prior(p.end())
				?
					p.front()
				:
					*boost::next(i),
			&prev = 
				i == p.begin()
				?
					p.back()
				:
					*boost::prior(i);
					
		return 
			next == b 
			? 
				prev 
			: 
				next;
	}
	SGE_ASSERT(false);
}
	
bool mergeable(
	rofl::polygon const &a,
	rofl::polygon const &b,
	rofl::line_segment const &l)
{
	rofl::point const 
		p0 = 
			find_previous(a,l.start(),l.end()),
		p1 = 
			find_previous(b,l.start(),l.end());
	
	if (left_on(l.start(),p0,p1))
		return false;
	
	rofl::point const 
		p2 = 
			find_previous(a,l.end(),l.start()),
		p3 = 
			find_previous(b,l.end(),l.start());
	
	if (left_on(l.end(),p2,p3))
		return false;

	return true;
}
#endif
}

void rofl::graph::simplify(
	object &g)
{
	/*
	for (std::pair<edge_iterator> i = boost::edges(g); i.first != i.second; ++i.first)
	{
		
	}
	*/
	#if 0
	foreach (vertex v : g)
	{
		ecken = ecken(v,u) in edges;
		while (!ecken.empty())
		{
			(v,u,kante) = ecken.pop(); // u = neue Ecke
			
			if (!verschmelzbar(v,u,kante)) // guckt, ob kante unnötig ist
				continue;
		
			v.polygon() = 
				verschmelze(
					u.polygon(),
					v.polygon(),
					kante);
					
			// Nachbarn übernehmen und später durchgehen
			foreach (w in ecken(u,w,anderekante)) // w = neue (transitive) Ecke
			{
				if (w == u) // keine Selbstverschmelzung
					continue;
				add_edge(
					v,w,anderekante);
				ecken.insert(
					(v,w,anderekante));
			}
			
			// alle Kanten, die u betreffen
			delete (u,*,*);
			// u selber
			delete u;
		}
	}
	#endif
}