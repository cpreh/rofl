cmake_minimum_required(VERSION 3.27.0)

project(rofl)

include(GNUInstallDirs)

# This is done before the warning flags are set
add_subdirectory(triangle)

find_package(Boost 1.50.0 REQUIRED)

# Find FCPPT

find_package(fcppt REQUIRED)

# mizuiro uses too many default arguments
list(
  APPEND
  FCPPT_UTILS_CLANG_TIDY_ADDITIONAL_CHECKS
  "-cppcoreguidelines-avoid-const-or-ref-data-members"
  "-fuchsia-default-arguments-calls"
  "-fuchsia-default-arguments-declarations"
  "-misc-misplaced-const")

set(FCPPT_UTILS_CLANG_TIDY_WHITELIST "fcppt" "awl" "mizuiro" "sge" "rofl")

include(FcpptCMakeUtils)

add_subdirectory(src)

option(ENABLE_APP "Build the applications" ON)

if(ENABLE_APP)
  add_subdirectory(app)
endif()

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
