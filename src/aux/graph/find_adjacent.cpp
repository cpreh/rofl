#include <rofl/indexed_point.hpp>
#include <rofl/indexed_polygon.hpp>
#include <rofl/aux/graph/find_adjacent.hpp>
#include <rofl/aux/graph/placement.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <utility>
#include <fcppt/config/external_end.hpp>


std::pair
<
	rofl::indexed_point,
	rofl::aux::graph::placement
> const
rofl::aux::graph::find_adjacent(
	rofl::indexed_polygon const &_p,
	rofl::indexed_point const &_a,
	rofl::indexed_point const &_b
)
{
	for(
		rofl::indexed_polygon::const_iterator it(
			_p.begin()
		);
		it != _p.end();
		++it
	)
	{
		if(
			(*it) != _a
		)
			continue;

		rofl::indexed_point const
			&next =
				it
				==
				std::prev(
					_p.end()
				)
				?
					_p.front()
				:
					*std::next(
						it
					)
				,
			&prev =
				it == _p.begin()
				?
					_p.back()
				:
					*std::prev(
						it
					)
			;

		return
			next == _b
			?
				std::make_pair(
					prev,
					rofl::aux::graph::placement::previous
				)
			:
				std::make_pair(
					next,
					rofl::aux::graph::placement::next
				)
			;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
