#ifndef ROFL_POLYGONIZERS_TRIANGLE_ACCUMULATE_SIZES_HPP_INCLUDED
#define ROFL_POLYGONIZERS_TRIANGLE_ACCUMULATE_SIZES_HPP_INCLUDED

namespace rofl
{
namespace polygonizers
{
namespace triangle
{
template<typename Container>
typename Container::size_type accumulate_sizes(
	Container const &_container)
{
	typename Container::size_type s(0u);

	for(
		typename Container::const_iterator it(
			_container.begin()
		);
		it != _container.end();
		++it
	)
		s += it->size();
	return s;
}

}
}
}

#endif
