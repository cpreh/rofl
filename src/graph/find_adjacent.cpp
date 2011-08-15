#include "find_adjacent.hpp"
#include <fcppt/assert/unreachable.hpp>
#include <boost/next_prior.hpp>

std::pair
<
	rofl::indexed_point,
	rofl::graph::placement::type
> const
rofl::graph::find_adjacent(
	indexed_polygon const &p,
	indexed_point const &a,
	indexed_point const &b)
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
				std::make_pair(prev,placement::previous)
			:
				std::make_pair(next,placement::next);
	}

	FCPPT_ASSERT_UNREACHABLE
}
