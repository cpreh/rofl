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
	${fcppt_core_TARGET}
	${awl_TARGET}
	${sgecore_TARGET}
	${sgeimagecolor_TARGET}
	${sgeinput_TARGET}
	${sgerenderer_TARGET}
	${sgesystems_TARGET}
	${sgeviewport_TARGET}
	${sgewindow_TARGET}
)

awl_utils_add_portable_executable(
	roflpolygonbuilder
	"test_main"
	"polygon.cpp"
)

target_link_libraries(
	roflpolygonbuilder
	${fcppt_core_TARGET}
	${awl_TARGET}
	${sgecore_TARGET}
	${sgemedia_TARGET}
	${sgeimagecolor_TARGET}
	${sgeimage2d_TARGET}
	${sgeinput_TARGET}
	${sgerenderer_TARGET}
	${sgesystems_TARGET}
	${sgetexture_TARGET}
	${sgeviewport_TARGET}
	${sgewindow_TARGET}
)

install(
	TARGETS roflmaintest
	DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)

install(
	TARGETS roflpolygonbuilder
	DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)
