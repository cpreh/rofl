CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)
SET (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

PROJECT (rofl)

IF(${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
	message(FATAL_ERROR "In-source builds are not permitted. Make a separate folder for building:\nmkdir build; cd build; cmake ..\nBefore that, remove the files that cmake just created:\nrm -rf CMakeCache.txt CMakeFiles")
ENDIF()

INCLUDE (FindPkgConfig)

SET (CMAKE_VERBOSE_MAKEFILE ON)

IF (CMAKE_COMPILER_IS_GNUCXX)
	#CHECK_CXX_COMPILER_FLAG(
	#	"-std=c++0x"
	#	SGE_HAVE_VARIADIC_TEMPLATES
	#)

	OPTION (ENABLE_DEBUG_WARNINGS "Enable -Wpadded and -Weffc++" OFF)

	#	ADD_DEFINITIONS ("-pedantic-errors -Wall -Wextra -Wconversion"
	#"-Wfloat-equal -Wredundant-decls -Wstrict-null-sentinel -Winit-self"
	#"-Woverloaded-virtual -Wnon-virtual-dtor -Wctor-dtor-privacy"
	#"-Wsign-promo -Wstrict-aliasing=1 -Wmissing-declarations"
	#"-Wold-style-cast")

	IF(ENABLE_DEBUG_WARNINGS)
		SET (CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG}" -Wpadded -Weffc++")
	ENDIF()

	ADD_DEFINITIONS(-D BOOST_FILESYSTEM_NO_DEPRECATED -fPIC)

	SET (CMAKE_CXX_FLAGS_RELEASE "-O3 -fomit-frame-pointer -DNDEBUG")
	
# -fvisibility=hidden causes problems without inlining, so just switch it on
# in release mode
#IF (SGE_HAVE_GCC_VISIBILITY)
#	ADD_DEFINITIONS(-fvisibility=hidden)
		#SET (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fvisibility=hidden")
		#ENDIF ()

	#IF (SGE_HAVE_VARIADIC_TEMPLATES)
	#	ADD_DEFINITIONS ("-std=c++0x")
	#ELSE ()
		# C++ 98 has no long long but boost insists on using it anyway
		#ADD_DEFINITIONS ("-Wno-long-long -ansi")
	#ENDIF ()
ENDIF ()

INCLUDE_DIRECTORIES (${CMAKE_SOURCE_DIR}/include)

SET (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

SET (Boost_ADDITIONAL_VERSIONS "1.41" "1.41.0" "1.42" "1.42.0")

IF(MSVC)
	SET(Boost_USE_STATIC_LIBS ON)
ENDIF()

FIND_PACKAGE(
	Boost 1.41.0 REQUIRED COMPONENTS
	program_options
)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

OPTION(ENABLE_TEST "Build the tests" ON)

IF (ENABLE_TEST)
	ADD_SUBDIRECTORY (test)
ENDIF ()

ADD_SUBDIRECTORY (src)

INSTALL (DIRECTORY include/ DESTINATION include)
