#include <rofl/aux/polygonizers/triangle/triangulation.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstring>
#include <string>
#include <fcppt/config/external_end.hpp>


rofl::aux::polygonizers::triangle::triangulation::triangulation(
	char const *_options,
	triangulateio &_in,
	triangulateio &_out)
:
	out_(
		_out)
{
	// Why this? Because triangulate incorrectly takes a "char*" instead of "char const*"
	std::string options(
		_options);

	::triangulate(
		&(*options.begin()),
		&_in,
		&_out,
		nullptr
	);
}

rofl::aux::polygonizers::triangle::triangulation::~triangulation()
{
	std::free(
		out_.trianglelist);
	std::free(
		out_.pointlist);
	std::free(
		out_.neighborlist);
}
