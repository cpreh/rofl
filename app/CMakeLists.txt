find_package(awl REQUIRED)

# FIXME
find_package(mizuiro REQUIRED)

# Find SGE

set(SGE_COMPONENTS
    media
    image
    image2d
    input
    renderer
    systems
    texture
    viewport
    window)

find_package(sge REQUIRED COMPONENTS ${SGE_COMPONENTS})

include(AwlMainGenerator)

awl_utils_add_portable_executable(rofl_main "test_main" main.cpp)

fcppt_utils_set_target_compiler_flags(rofl_main)

target_link_libraries(
  rofl_main
  PRIVATE rofl
          ${fcppt_core_TARGET}
          ${awl_TARGET}
          ${sgecore_TARGET}
          ${sgeimagecolor_TARGET}
          ${sgeinput_TARGET}
          ${sgerenderer_TARGET}
          ${sgesystems_TARGET}
          ${sgeviewport_TARGET}
          ${sgewindow_TARGET})

target_include_directories(rofl_main PRIVATE line_strip/include)

# awl_utils_add_portable_executable( rofl_polygonbuilder "test_main"
# "polygon.cpp" )

# target_link_libraries( rofl_polygonbuilder ${fcppt_core_TARGET} ${awl_TARGET}
# ${sgecore_TARGET} ${sgemedia_TARGET} ${sgeimagecolor_TARGET}
# ${sgeimage2d_TARGET} ${sgeinput_TARGET} ${sgerenderer_TARGET}
# ${sgesystems_TARGET} ${sgetexture_TARGET} ${sgeviewport_TARGET}
# ${sgewindow_TARGET} )

install(TARGETS rofl_main DESTINATION ${CMAKE_INSTALL_BINDIR})

# install( TARGETS rofl_polygonbuilder DESTINATION ${CMAKE_INSTALL_PREFIX}/bin )
