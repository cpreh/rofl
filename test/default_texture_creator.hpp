#ifndef SGE_BULLET_TEST_DEFAULT_TEXTURE_CREATOR_HPP_INCLUDED
#define SGE_BULLET_TEST_DEFAULT_TEXTURE_CREATOR_HPP_INCLUDED

#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/texture/const_part_ptr.hpp>
#include <sge/texture/manager.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace bullet
{
namespace test
{
class default_texture_creator
{
	FCPPT_NONCOPYABLE(
		default_texture_creator
	);
public:
	default_texture_creator(
		sge::image2d::system &,
		sge::renderer::device &);

	sge::texture::const_part_ptr
	load(
		boost::filesystem::path const &);
private:
	sge::image2d::system &il_;

	sge::texture::manager man_;
};
}
}
}

#endif
