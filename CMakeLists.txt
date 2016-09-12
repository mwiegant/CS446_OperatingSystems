cmake_minimum_required (VERSION 2.6)
project (Tutorial)

set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
#configure_file (
#        "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
#        "${PROJECT_BINARY_DIR}/TutorialConfig.h"
#)

# include the directory that contains my class prototypes
include_directories("${PROJECT_SOURCE_DIR}/include")

# Set sources
FILE(GLOB_RECURSE SOURCES "src/*.cpp")
ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES})