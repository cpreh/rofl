#include "default_texture_creator.hpp"
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/image2d/system.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/fragmented.hpp>
#include <sge/texture/fragmented_unique_ptr.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>
#include <fcppt/config/external_end.hpp>

sge::bullet::test::default_texture_creator::default_texture_creator(
	sge::image2d::system &_il,
	sge::renderer::device &_rend
)
:
	il_(
		_il
	),
	man_(
		boost::phoenix::construct<
			sge::texture::fragmented_unique_ptr
		>(
			boost::phoenix::new_<
				sge::texture::no_fragmented
			>(
				fcppt::ref(
					_rend
				),
				sge::image::color::format::rgba8,
				sge::renderer::texture::mipmap::off()
			)
		)
	)
{
}

sge::texture::const_part_ptr
sge::bullet::test::default_texture_creator::load(
	boost::filesystem::path const &_path)
{
	return
		sge::texture::add_image(
			man_,
			*il_.load(
				_path));
}
