#ifndef ROFL_AUX_POLYGONIZERS_TRIANGLE_ACCUMULATE_SIZES_HPP_INCLUDED
#define ROFL_AUX_POLYGONIZERS_TRIANGLE_ACCUMULATE_SIZES_HPP_INCLUDED


namespace rofl::aux::polygonizers::triangle
{

template<
	typename Container
>
typename
Container::size_type
accumulate_sizes(
	Container const &_container
)
{
	typename Container::size_type ret(
		0U
	);

	for(
		auto const &elem : _container
	)
	{
		ret += elem.size();
	}

	return ret;
}

}

#endif
