add_definitions(
	"-DTRILIBRARY -DLINUX"
)

# remove broken timer code
add_definitions(
	-D NO_TIMER
)

include_directories(
	include
)

add_library(
	rofltriangleimpl
	SHARED
	src/triangle.c
	include/triangle/impl.hpp
	include/triangle/triangle.h
)

if(
	UNIX
)
	target_link_libraries(
		rofltriangleimpl
		m
	)
endif()

install(
	TARGETS
	rofltriangleimpl
	DESTINATION
	${CMAKE_INSTALL_PREFIX}/lib
)
