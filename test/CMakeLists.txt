ADD_EXECUTABLE (roflmaintest main.cpp)
TARGET_LINK_LIBRARIES (roflmaintest sgecore rofl)
INSTALL (TARGETS roflmaintest DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
