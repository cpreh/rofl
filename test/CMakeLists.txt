include(
	AwlMainGenerator
)

awl_utils_add_portable_executable(
	roflmaintest
	"test_main"
	main.cpp
)

target_link_libraries(
	roflmaintest
	rofl
	${Fcppt_core_LIBRARIES}
	${Awl_LIBRARIES}
	${SGE_CORE_LIBRARY}
	${SGE_IMAGE_LIBRARY}
	${SGE_INPUT_LIBRARY}
	${SGE_RENDERER_LIBRARY}
	${SGE_SYSTEMS_LIBRARY}
	${SGE_VIEWPORT_LIBRARY}
	${SGE_WINDOW_LIBRARY}
)

awl_utils_add_portable_executable(
	roflpolygonbuilder
	"test_main"
	"polygon.cpp;default_texture_creator.cpp"
)

target_link_libraries(
	roflpolygonbuilder
	${Fcppt_core_LIBRARIES}
	${Awl_LIBRARIES}
	${SGE_CORE_LIBRARY}
	${SGE_MEDIA_LIBRARY}
	${SGE_IMAGE_LIBRARY}
	${SGE_IMAGE2D_LIBRARY}
	${SGE_INPUT_LIBRARY}
	${SGE_RENDERER_LIBRARY}
	${SGE_SYSTEMS_LIBRARY}
	${SGE_VIEWPORT_LIBRARY}
	${SGE_TEXTURE_LIBRARY}
	${SGE_WINDOW_LIBRARY}
)

install(
	TARGETS roflmaintest
	DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)

install(
	TARGETS roflpolygonbuilder
	DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)
