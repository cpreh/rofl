#!/bin/sh
set -e -u

update_cmake \
	src/CMakeLists.txt \
	ROFL_INCLUDE_FILES \
	include/rofl

update_cmake \
	src/CMakeLists.txt \
	ROFL_SRC_FILES \
	src
