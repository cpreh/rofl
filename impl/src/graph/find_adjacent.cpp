#include <rofl/indexed_point.hpp>
#include <rofl/indexed_polygon.hpp>
#include <rofl/aux/graph/find_adjacent.hpp>
#include <rofl/aux/graph/placement.hpp>
#include <fcppt/config/external_begin.hpp>
#include <exception>
#include <iterator>
#include <utility>
#include <fcppt/config/external_end.hpp>

std::pair<rofl::indexed_point, rofl::aux::graph::placement> rofl::aux::graph::find_adjacent(
    rofl::indexed_polygon const &_p, rofl::indexed_point const &_a, rofl::indexed_point const &_b)
{
  for (auto it(_p.begin()); it != _p.end(); ++it)
  {
    if ((*it) != _a)
    {
      continue;
    }

    rofl::indexed_point const &next{
        it == std::prev( // NOLINT(fuchsia-default-arguments-calls)
                  _p.end())
            ? _p.front()
            : *std::next( // NOLINT(fuchsia-default-arguments-calls)
                  it)};

    rofl::indexed_point const &prev{
        it == _p.begin() ? _p.back()
                         : *std::prev( // NOLINT(fuchsia-default-arguments-calls)
                               it)};

    return next == _b ? std::make_pair(prev, rofl::aux::graph::placement::previous)
                      : std::make_pair(next, rofl::aux::graph::placement::next);
  }

  std::terminate();
}
