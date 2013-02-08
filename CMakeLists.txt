cmake_minimum_required(
	VERSION
	2.8
)

project(
	rofl
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

# TODO: Only find AWL and SGE when tests are enabled
# Find AWL

find_package(
	awl REQUIRED
)

add_definitions(
	${awl_DEFINITIONS}
)

include_directories(
	${awl_INCLUDE_DIRS}
)

# Find SGE

set(
	SGE_COMPONENTS
	media image image2d input renderer window
)

option(
	ENABLE_TEST
	"Build the tests" ON
)

if(
	ENABLE_TEST
)
	set(
		SGE_COMPONENTS
		${SGE_COMPONENTS} systems texture viewport
	)
endif()

find_package(
	sge REQUIRED
	COMPONENTS
	${SGE_COMPONENTS}
)

include_directories(
	${sge_INCLUDE_DIRS}
)

if(
	ENABLE_TEST
)
	add_subdirectory(
		test
	)
endif()

install(
	DIRECTORY
	include
	DESTINATION
	include
)
