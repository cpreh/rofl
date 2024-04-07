#!/usr/bin/env bash
set -e -u

update_cmake.sh \
	src/rofl_files.txt \
	include \
	impl \
	src
