FIND_PACKAGE(
	SGE REQUIRED
	COMPONENTS sprite systems texture viewport
)

ADD_EXECUTABLE(
	roflmaintest
	main.cpp
)

TARGET_LINK_LIBRARIES(
	roflmaintest
	rofl
	${SGE_CORE_LIBRARY}
	${SGE_viewport_LIBRARY}
	${SGE_systems_LIBRARY}
)

ADD_EXECUTABLE(
	roflpolygonbuilder
	polygon.cpp
	default_texture_creator.cpp
)

TARGET_LINK_LIBRARIES(
	roflpolygonbuilder
	${SGE_CORE_LIBRARY}
	${SGE_viewport_LIBRARY}
	${SGE_sprite_LIBRARY}
	${SGE_systems_LIBRARY}
	${SGE_texture_LIBRARY}
)

INSTALL(
	TARGETS roflmaintest
	DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)

INSTALL(
	TARGETS roflpolygonbuilder
	DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)
