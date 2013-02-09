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
	ROFL_INCLUDE_FILES \
	include/rofl

update_cmake_file \
	src/CMakeLists.txt \
	ROFL_SRC_FILES \
	src
