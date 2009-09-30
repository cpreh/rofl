ADD_SUBDIRECTORY(impl)

ADD_DEFINITIONS(-DTRILIBRARY -DANSI_DECLARATORS -DREAL=float -DVOID=int)

FILE(GLOB trianglefiles src/*.cpp)

ADD_LIBRARY(triangle ${trianglefiles})
TARGET_LINK_LIBRARIES(triangle impl)
