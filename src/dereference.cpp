#include <rofl/dereference.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <boost/foreach.hpp>

rofl::polygon const rofl::dereference(
	indexed_polygon const &i)
{
	rofl::polygon g;
	BOOST_FOREACH(indexed_polygon::const_reference r,i)
		g.push_back(
			r.representation());
	return g;
}
