#ifndef ROFL_AUX_POLYGONIZERS_TRIANGLE_OBJECT_HPP_INCLUDED
#define ROFL_AUX_POLYGONIZERS_TRIANGLE_OBJECT_HPP_INCLUDED

#include <rofl/polygonizer.hpp>
#include <rofl/polygon_with_holes_fwd.hpp>
#include <rofl/graph/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>


namespace rofl::aux::polygonizers::triangle
{

class object : public rofl::polygonizer
{
  FCPPT_NONMOVABLE(object);

public:
  explicit object(fcppt::log::context_reference);

  ~object() override;

private:
  void polygonize(rofl::polygon_with_holes const &, fcppt::reference<rofl::graph::object>) override;

  fcppt::log::object log_;
};
}

#endif
