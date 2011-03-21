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
	CMakeLists.txt \
	ROFL_CORE_INCLUDE_FILES \
	include/rofl

update_cmake_file \
	CMakeLists.txt \
	ROFL_CORE_SRC_FILES \
	-n \
	src \
	-r \
	src/astar \
	src/graph \
	src/math

pushd src/polygonizers/triangle > /dev/null || die

update_cmake_file \
	CMakeLists.txt \
	ROFL_TRIANGLE_FILES \
	-n \
	. \
	-r \
	src/

popd > /dev/null
