#include "default_texture_creator.hpp"
#include <sge/renderer/texture/filter/linear.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/image2d/multi_loader.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/fragmented.hpp>
#include <sge/texture/fragmented_unique_ptr.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>

sge::bullet::test::default_texture_creator::default_texture_creator(
	sge::image2d::multi_loader &_il, 
	sge::renderer::device_ptr const _rend
)
:
	il_(
		_il
	),
	man_(
		_rend,
		boost::phoenix::construct<
			sge::texture::fragmented_unique_ptr
		>(
			boost::phoenix::new_<
				sge::texture::no_fragmented
			>(
				_rend,
				sge::image::color::format::rgba8,
				sge::renderer::texture::filter::linear,
				sge::renderer::texture::address_mode2(
					sge::renderer::texture::address_mode::repeat
				)
			)
		)
	)
{
}

sge::texture::const_part_ptr
sge::bullet::test::default_texture_creator::load(
	fcppt::filesystem::path const &_path)
{
	return 
		sge::texture::add_image(
			man_,
			il_.load(
				_path));
}
