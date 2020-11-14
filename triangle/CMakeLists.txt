add_definitions(
	"-DTRILIBRARY -DLINUX"
)

# remove broken timer code
add_definitions(
	-D NO_TIMER
)

add_library(
	rofltriangleimpl
	SHARED
	src/triangle.c
	include/triangle/impl.hpp
	include/triangle/triangle.h
)

target_include_directories(
	rofltriangleimpl
	PUBLIC
	include
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
	${CMAKE_INSTALL_LIBDIR}
)
