#include <rofl/aux/polygonizers/triangle/triangulation.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstring>
#include <string>
#include <fcppt/config/external_end.hpp>


rofl::aux::polygonizers::triangle::triangulation::triangulation(
	char const *_options,
	fcppt::reference<
		triangulateio
	> const _in,
	fcppt::reference<
		triangulateio
	> const _out
)
:
	out_(
		_out
	)
{
	// Why this? Because triangulate incorrectly takes a "char*" instead of "char const*"
	std::string options(
		_options
	);

	::triangulate(
		&(*options.begin()),
		&_in.get(),
		&_out.get(),
		nullptr
	);
}

rofl::aux::polygonizers::triangle::triangulation::~triangulation()
{
	std::free(
		out_.get().trianglelist
	);
	std::free(
		out_.get().pointlist
	);
	std::free(
		out_.get().neighborlist)
	;
}
