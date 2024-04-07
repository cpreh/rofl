file(STRINGS rofl_files.txt ROFL_FILES)

fcppt_utils_append_source_dir_and_make_groups("${ROFL_FILES}" NEW_ROFL_FILES)

add_library(rofl SHARED ${NEW_ROFL_FILES})

fcppt_utils_set_target_compiler_flags(rofl)

target_link_libraries(rofl PRIVATE ${fcppt_core_TARGET} ${fcppt_log_TARGET}
                                   rofltriangleimpl)

target_include_directories(
  rofl
  PUBLIC ${CMAKE_SOURCE_DIR}/include
  PRIVATE ${CMAKE_SOURCE_DIR}/triangle/include ${CMAKE_SOURCE_DIR}/impl/include)

install(TARGETS rofl DESTINATION ${CMAKE_INSTALL_LIBDIR})
