#include "default_texture_creator.hpp"
#include <sge/renderer/filter/linear.hpp>
#include <sge/image/loader.hpp>
#include <sge/texture/add_image.hpp>
#include <sge/texture/default_creator_impl.hpp>

sge::bullet::test::default_texture_creator::default_texture_creator(
	sge::image::loader_ptr const _il, 
	sge::renderer::device_ptr const _rend)
:
	il_(
		_il),
	rend_(
		_rend),
	creator_(
		rend_,
		sge::image::color::format::rgba8,
		sge::renderer::filter::linear),
	man_(
		rend_,
		creator_)
{
}

sge::texture::const_part_ptr
sge::bullet::test::default_texture_creator::load(
	fcppt::filesystem::path const &_path)
{
	return 
		sge::texture::add_image(
			man_,
			il_->load(
				_path));
}
