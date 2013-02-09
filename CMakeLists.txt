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
	Boost 1.41.0 REQUIRED
)

include_directories(
	${Boost_INCLUDE_DIR}
)

link_directories(
	${Boost_LIBRARY_DIRS}
)

# Find Mizuiro

FIND_PACKAGE(
	mizuiro REQUIRED
)

include_directories(
	${mizuiro_INCLUDE_DIRS}
)

# Find FCPPT

find_package(
	fcppt REQUIRED
)

add_definitions(
	${fcppt_DEFINITIONS}
)

include_directories(
	${fcppt_INCLUDE_DIRS}
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
