cmake_minimum_required(
	VERSION
	2.8
)

project(
	rofl
)

# This is done before the warning flags are set
add_subdirectory(
	triangle
)

include(
	FcpptCMakeUtils
)

include_directories(
	${CMAKE_SOURCE_DIR}/include
)

find_package(
	Boost 1.50.0 REQUIRED
)

include_directories(
	${Boost_INCLUDE_DIR}
)

# Find FCPPT

find_package(
	fcppt REQUIRED
)

add_subdirectory(
	src
)

option(
	ENABLE_APP
	"Build the applications" ON
)

if(
	ENABLE_APP
)
	add_subdirectory(
		app
	)
endif()

install(
	DIRECTORY
	include/
	DESTINATION
	${INSTALL_INCLUDE_DIR}
)
