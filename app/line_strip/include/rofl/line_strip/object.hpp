#ifndef ROFL_LINE_STRIP_OBJECT_HPP_INCLUDED
#define ROFL_LINE_STRIP_OBJECT_HPP_INCLUDED

#include <rofl/line_strip/object_fwd.hpp>
#include <rofl/line_strip/parameters_fwd.hpp>
#include <rofl/line_strip/style.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/static.hpp>
#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/declaration_unique_ptr.hpp>
#include <sge/renderer/vf/color.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/part.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace rofl::line_strip
{
template <typename Value, typename Color>
class object
{
  FCPPT_NONCOPYABLE(object);

public:
  using unit = Value;

  using point = fcppt::math::vector::static_<unit, 2>;

  using point_sequence = std::vector<point>;

  using color = Color;

  object(sge::renderer::device::core_ref, parameters<unit, color> const &);

  ~object();

  object(object &&) noexcept;

  object &operator=(object &&) noexcept;

  void push_back(point const &);

  void pop_back();

  void clear();

  void draw(sge::renderer::context::core & // NOLINT(google-runtime-references)
  ) const; // NOLINT(google-runtime-references)

  // only read access because we have to regenerate the vb afterwards
  [[nodiscard]] point_sequence const &points() const;

  void back(point const &);

private:
  using pos_type = sge::renderer::vf::pos<unit, 2>;

  using color_type = sge::renderer::vf::color<typename color::format>;

  using format_part = sge::renderer::vf::part<pos_type, color_type>;

  using format = sge::renderer::vf::format<format_part>;

  sge::renderer::device::core_ref renderer_;

  rofl::line_strip::style style_;

  color color_;

  point_sequence points_;

  sge::renderer::vertex::declaration_unique_ptr vertex_declaration_;

  using optional_vertex_buffer_ptr =
      fcppt::optional::object<sge::renderer::vertex::buffer_unique_ptr>;

  optional_vertex_buffer_ptr vertex_buffer_;

  void regenerate_vb();
};

}

#endif
