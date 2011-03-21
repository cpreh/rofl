CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

SET(EXTRA_CMAKE_MODULE_PATH "" CACHE PATH "Extra paths to search for cmake modules")

SET (CMAKE_MODULE_PATH "${EXTRA_CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}/CMakeModules")

PROJECT (rofl)

IF(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
	message(FATAL_ERROR "In-source builds are not permitted. Make a separate folder for building:\nmkdir build; cd build; cmake ..\nBefore that, remove the files that cmake just created:\nrm -rf CMakeCache.txt CMakeFiles")
ENDIF()

INCLUDE (CheckCXXSourceRuns)

CHECK_CXX_SOURCE_RUNS(
	"#include <cstdlib>
	int main()
	{
	#ifdef __clang__
		return EXIT_SUCCESS;
	#else
		return EXIT_FAILURE;
	#endif
	}
	"
	COMPILER_IS_CLANGPP
)

IF (CMAKE_COMPILER_IS_GNUCXX OR COMPILER_IS_CLANGPP)
	ADD_DEFINITIONS (
		"-pedantic-errors -Wall -Wextra -Wconversion"
		"-Wfloat-equal -Wredundant-decls -Winit-self"
		"-Woverloaded-virtual -Wnon-virtual-dtor"
		"-Wsign-promo -Wstrict-aliasing=1 -Wmissing-declarations"
		"-Wold-style-cast"
	)

	SET (CMAKE_CXX_FLAGS_RELEASE "-O3 -fomit-frame-pointer -DNDEBUG")
ENDIF ()

INCLUDE_DIRECTORIES (${CMAKE_SOURCE_DIR}/include)

SET (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

SET (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# Find Boost
SET (Boost_ADDITIONAL_VERSIONS "1.41" "1.41.0" "1.42" "1.42.0" "1.43" "1.43.0" "1.44" "1.44.0" "1.45" "1.45.0" "1.46" "1.46.0" "1.46.1")

FIND_PACKAGE(
	Boost 1.41.0 REQUIRED COMPONENTS
	program_options
)

INCLUDE_DIRECTORIES(
	SYSTEM
	${Boost_INCLUDE_DIR}
)

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

# Find Mizuiro

FIND_PACKAGE(
	Mizuiro REQUIRED
)

INCLUDE_DIRECTORIES(${MIZUIRO_INCLUDE_DIRS})

# Find FCPPT

FIND_PACKAGE(
	Fcppt REQUIRED
)

INCLUDE_DIRECTORIES(${FCPPT_INCLUDE_DIRS})

LINK_DIRECTORIES(${FCPPT_LIBRARY_DIRS})

# Find AWL

FIND_PACKAGE(
	AWL REQUIRED
)

INCLUDE_DIRECTORIES(${AWL_INCLUDE_DIRS})

# Find SGE

FIND_PACKAGE(
	SGE REQUIRED
)

INCLUDE_DIRECTORIES(${SGE_INCLUDE_DIRS})

OPTION(ENABLE_TEST "Build the tests" ON)

IF (ENABLE_TEST)
	ADD_SUBDIRECTORY (test)
ENDIF ()

SET(
	ROFL_CORE_INCLUDE_FILES
	include/rofl/astar/generate_path.hpp
	include/rofl/astar/generate_trail.hpp
	include/rofl/astar/path.hpp
	include/rofl/astar/trail.hpp
	include/rofl/consume.hpp
	include/rofl/create_polygonizer.hpp
	include/rofl/dereference.hpp
	include/rofl/graph/const_vertex_iterator.hpp
	include/rofl/graph/edge_descriptor.hpp
	include/rofl/graph/edge_iterator.hpp
	include/rofl/graph/edge_properties.hpp
	include/rofl/graph/object.hpp
	include/rofl/graph/object_fwd.hpp
	include/rofl/graph/out_edge_iterator.hpp
	include/rofl/graph/properties.hpp
	include/rofl/graph/simplify.hpp
	include/rofl/graph/vertex_descriptor.hpp
	include/rofl/graph/vertex_iterator.hpp
	include/rofl/graph/vertex_properties.hpp
	include/rofl/graph/vertices_begin.hpp
	include/rofl/graph/vertices_end.hpp
	include/rofl/index.hpp
	include/rofl/indexed_line_segment.hpp
	include/rofl/indexed_point.hpp
	include/rofl/indexed_polygon.hpp
	include/rofl/line_segment.hpp
	include/rofl/log.hpp
	include/rofl/log_context.hpp
	include/rofl/math/barycenter.hpp
	include/rofl/math/line_segment.hpp
	include/rofl/math/polygon.hpp
	include/rofl/math/polygon_with_holes.hpp
	include/rofl/math/polygon_with_holes_fwd.hpp
	include/rofl/point.hpp
	include/rofl/polygon.hpp
	include/rofl/polygon_with_holes.hpp
	include/rofl/polygonizer.hpp
	include/rofl/polygonizer_fwd.hpp
	include/rofl/unit.hpp
)

SET(
	ROFL_CORE_SRC_FILES
	src/astar/found_goal.hpp
	src/astar/generate_path.cpp
	src/astar/generate_trail.cpp
	src/astar/goal_visitor.hpp
	src/astar/goal_visitor_impl.hpp
	src/astar/heuristic.hpp
	src/astar/heuristic_impl.hpp
	src/create_polygonizer.cpp
	src/cyclic_iterator.hpp
	src/cyclic_iterator_impl.hpp
	src/dereference.cpp
	src/graph/edge_properties.cpp
	src/graph/find_adjacent.cpp
	src/graph/find_adjacent.hpp
	src/graph/merge.cpp
	src/graph/merge.hpp
	src/graph/mergeable.cpp
	src/graph/mergeable.hpp
	src/graph/on_boundary.hpp
	src/graph/placement.hpp
	src/graph/properties.cpp
	src/graph/simplify.cpp
	src/graph/vertex_properties.cpp
	src/graph/vertices_begin.cpp
	src/graph/vertices_end.cpp
	src/indexed_point.cpp
	src/log.cpp
	src/log_context.cpp
	src/math/area_sign.hpp
	src/math/left.hpp
	src/math/left_on.hpp
	src/polygonizer.cpp
)

SET(
	ROFL_CORE_FILES
	"${ROFL_CORE_INCLUDE_FILES};${ROFL_CORE_SRC_FILES}"
)

ADD_LIBRARY(
	rofl SHARED ${ROFL_CORE_FILES}
)

TARGET_LINK_LIBRARIES(
	rofl
	${SGE_CORE_LIBRARY}
)

INSTALL(
	TARGETS
	rofl
	DESTINATION
	${CMAKE_INSTALL_PREFIX}/lib
)

ADD_SUBDIRECTORY(
	src/polygonizers/triangle
)

INSTALL (DIRECTORY include/ DESTINATION include)
