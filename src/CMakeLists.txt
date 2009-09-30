FILE (GLOB roflcorefiles 
	*.cpp
	graph/*.cpp
	math/*.cpp)

FILE (GLOB_RECURSE roflcoreheaders
	../include/*.hpp)

SET (roflcorefiles ${roflcorefiles} ${roflcoreheaders})

ADD_LIBRARY (rofl SHARED ${roflcorefiles})

IF (NOT MSVC)
	TARGET_LINK_LIBRARIES (
		rofl
		${Boost_LIBRARIES}
		sgecore
		triangle
	)
ENDIF ()

IF (UNIX)
ELSEIF (WIN32)
	TARGET_LINK_LIBRARIES (rofl gdi32 kernel32 user32)
ENDIF ()

INSTALL (TARGETS rofl DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

ADD_SUBDIRECTORY (polygonizers)
