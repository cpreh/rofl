CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT (rofl)

SET(EXTRA_CMAKE_MODULE_PATH "" CACHE PATH "Extra paths to search for cmake modules")

SET (CMAKE_MODULE_PATH "${EXTRA_CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}/CMakeModules")

INCLUDE(FcpptCMakeUtils)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/include
)

FIND_PACKAGE(
	Boost 1.41.0 REQUIRED
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
	src/polygonizers/log.hpp
	src/polygonizers/src/log.cpp
)

SET(
	ROFL_TRIANGLE_FILES
	src/polygonizers/triangle/accumulate_sizes.hpp
	src/polygonizers/triangle/add_polygon.hpp
	src/polygonizers/triangle/clear_pod.hpp
	src/polygonizers/triangle/determine_adjacent_edge.hpp
	src/polygonizers/triangle/edge_angle.hpp
	src/polygonizers/triangle/fill_intermediate.hpp
	src/polygonizers/triangle/fill_points.hpp
	src/polygonizers/triangle/intermediate.hpp
	src/polygonizers/triangle/is_convex.hpp
	src/polygonizers/triangle/line_segments.hpp
	src/polygonizers/triangle/log.hpp
	src/polygonizers/triangle/object.hpp
	src/polygonizers/triangle/src/intermediate.cpp
	src/polygonizers/triangle/src/log.cpp
	src/polygonizers/triangle/src/object.cpp
	src/polygonizers/triangle/src/triangulation.cpp
	src/polygonizers/triangle/triangle_line_segments.hpp
	src/polygonizers/triangle/triangulation.hpp
)

SET_SOURCE_FILES_PROPERTIES(
	${ROFL_TRIANGLE_FILES}
	PROPERTIES
	COMPILE_FLAGS
	"-DTRILIBRARY -DANSI_DECLARATORS -DREAL=float -DVOID=int"
)

SET(
	ROFL_CORE_FILES
	"${ROFL_CORE_INCLUDE_FILES};${ROFL_CORE_SRC_FILES};${ROFL_TRIANGLE_FILES}"
)

ADD_LIBRARY(
	rofl SHARED ${ROFL_CORE_FILES}
)

TARGET_LINK_LIBRARIES(
	rofl
	${FCPPT_LIBRARIES}
	${SGE_CORE_LIBRARY}
	rofltriangleimpl
)

INSTALL(
	TARGETS
	rofl
	DESTINATION
	${CMAKE_INSTALL_PREFIX}/lib
)

ADD_SUBDIRECTORY(
	src/polygonizers/triangle/impl
)

INSTALL (DIRECTORY include/ DESTINATION include)
