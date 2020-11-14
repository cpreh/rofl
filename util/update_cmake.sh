#!/bin/sh
set -e -u

update_cmake \
	src/CMakeLists.txt \
	ROFL_FILES \
	include \
	impl \
	src
