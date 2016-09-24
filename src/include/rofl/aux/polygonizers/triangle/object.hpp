#ifndef ROFL_AUX_POLYGONIZERS_TRIANGLE_OBJECT_HPP_INCLUDED
#define ROFL_AUX_POLYGONIZERS_TRIANGLE_OBJECT_HPP_INCLUDED

#include <rofl/polygonizer.hpp>
#include <rofl/polygon_with_holes_fwd.hpp>
#include <rofl/graph/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/object.hpp>


namespace rofl
{
namespace aux
{
namespace polygonizers
{
namespace triangle
{

class object
:
	public rofl::polygonizer
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		fcppt::log::context &
	);

	~object()
	override;
private:
	void
	polygonize(
		rofl::polygon_with_holes const &,
		rofl::graph::object &
	)
	override;

	fcppt::log::object log_;
};

}
}
}
}

#endif
