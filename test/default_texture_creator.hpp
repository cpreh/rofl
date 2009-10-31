#ifndef SGE_BULLET_TEST_DEFAULT_TEXTURE_CREATOR_HPP_INCLUDED
#define SGE_BULLET_TEST_DEFAULT_TEXTURE_CREATOR_HPP_INCLUDED

#include <sge/image/loader_fwd.hpp>

#include <sge/renderer/device_fwd.hpp>

#include <sge/filesystem/path.hpp>

#include <sge/texture/part_fwd.hpp>
#include <sge/texture/default_creator.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/manager.hpp>

#include <sge/noncopyable.hpp>

namespace sge
{
namespace bullet
{
namespace test
{
class default_texture_creator
{
SGE_NONCOPYABLE(default_texture_creator)
public:
	default_texture_creator(
		sge::image::loader_ptr,
		sge::renderer::device_ptr);
	
	sge::texture::const_part_ptr
	load(
		sge::filesystem::path const &);
private:
	sge::image::loader_ptr il_;
	sge::renderer::device_ptr rend_;
	sge::texture::default_creator
	<
		sge::texture::no_fragmented
	> const creator_;

	sge::texture::manager man_;
};
}
}
}

#endif
