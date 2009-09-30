#include "../triangulation.hpp"
#include <sge/container/raw_vector.hpp>
#include <cstring>
#include <cstdlib>

rofl::polygonizers::triangle::triangulation::triangulation(
	char const *_options,
	triangulateio &_in,
	triangulateio &_out)
:
	out_(
		_out)
{
	// Why this? Because triangulate incorrectly takes a "char*" instead of "char const*"
	sge::container::raw_vector<char> 
		options;
	options.resize(
		std::strlen(
			_options));
		
	::triangulate(
		options.data(),
		&_in,
		&_out,
		0);
}

rofl::polygonizers::triangle::triangulation::~triangulation()
{
	std::free(
		out_.trianglelist);
	std::free(
		out_.pointlist);
	std::free(
		out_.neighborlist);
}