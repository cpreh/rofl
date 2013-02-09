function die()
{
	exit -1
}

function update_cmake_file()
{
	local cmakefile="$1"

	update_cmake \
		"${cmakefile}" \
		"${@:2}" \
		|| die

	mv "${cmakefile}".new "${cmakefile}" || die

	chmod -x "${cmakefile}" || die
}

update_cmake_file \
	src/CMakeLists.txt \
	ROFL_CORE_INCLUDE_FILES \
	include/rofl

update_cmake_file \
	src/CMakeLists.txt \
	ROFL_CORE_SRC_FILES \
	-n \
	src \
	-r \
	src/aux \
	src/astar \
	src/graph \
	src/include \
	-n \
	src/polygonizers \
	src/polygonizers/src

update_cmake_file \
	src/CMakeLists.txt \
	ROFL_TRIANGLE_FILES \
	-n \
	src/polygonizers/triangle \
	-r \
	src/polygonizers/triangle/src
