#include <rofl/astar/generate_path.hpp>
#include <rofl/line_segment.hpp>
#include <sge/optional.hpp>
#include <sge/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/next_prior.hpp>

/* Pseudocode
 */
// Sei der Pfad hier gespeichert

/*
typedef (punkt,kante) paar;
paar pfad[n];

int current = 0;
while (true)
{
	int i;
	for (i = current+1; i < n; ++i)
	{
		c = 
			strecke
			(
				pfad[current].punkt,
				pfad[i].punkt
			);

		for (int j = current+1; j < i; ++j)
			if (!intersect(c,pfad[j].kante))
				break;
	}
	ergebnis.push_back(
		strecke(
			pfad[current].punkt,
			pfad[i-1].punkt));

	// in i-1 steht jetzt der letzte gueltige Index
	if (i == n)
		break;

	current = i-1;
}
*/


void 
rofl::astar::generate_path(
	graph::object const &g,
	trail const &t,
	point const &start,
	point const &end,
	path &p)
{
	// Erster Schritt: Generiere Uebergangspfad aus Paaren (Punkt,Kante), wobei Kante die Kante ist, die zwei
	// Polygone verbindet und Punkt der Mittelpunkt. Die Kante kann natuerlich leer sein, wenn es sich um den
	// Start- bzw. Endpunkt handelt.
	/*
	typedef
	sge::optional<rofl::line_segment>
	optional_line_segment;
	
	typedef 
	std::pair
	<
		optional_line_segment,
		rofl::point
	>
	pair;
	
	typedef 
	std::vector<pair> 
	intermediate_path;
	
	intermediate_path ip;
	ip.push_back(
		pair(
			optional_line_segment(),
			start));
	
	for (trail::const_iterator i = t.begin(); i != t.end(); ++i)
	{
		boost::edges(*i,*boost::next(i));
	}
	*/
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
