#include "find_previous.hpp"
#include <sge/assert.hpp>
#include <boost/next_prior.hpp>

rofl::indexed_point const rofl::graph::find_previous(
	rofl::indexed_polygon const &p,
	rofl::indexed_point const &a,
	rofl::indexed_point const &b)
{
	for (rofl::indexed_polygon::const_iterator i = p.begin(); i != p.end(); ++i)
	{
		if ((*i) != a)
			continue;
		
		rofl::indexed_point const 
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