ADD_SUBDIRECTORY(impl)

ADD_DEFINITIONS(
	-DTRILIBRARY
	-DANSI_DECLARATORS
	-DREAL=float
	-DVOID=int
)

SET(
	ROFL_TRIANGLE_FILES
	./accumulate_sizes.hpp
	./add_polygon.hpp
	./clear_pod.hpp
	./determine_adjacent_edge.hpp
	./edge_angle.hpp
	./fill_intermediate.hpp
	./fill_points.hpp
	./intermediate.hpp
	./is_convex.hpp
	./line_segments.hpp
	./log.hpp
	./object.hpp
	./triangle_line_segments.hpp
	./triangulation.hpp
	src/intermediate.cpp
	src/log.cpp
	src/object.cpp
	src/triangulation.cpp
)

ADD_LIBRARY(
	triangle
	${ROFL_TRIANGLE_FILES}
)

TARGET_LINK_LIBRARIES(
	triangle
	triangleimpl
	${SGE_CORE_LIBRARY}
)
