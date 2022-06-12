###############################################################################
##########          MINIMUM REQUIREMENTS (some need to be BEFORE project command)
###############################################################################
find_package(OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )
###############################################################################
##########          REQUIREMENTS + GLOBAL DEFINITION
###############################################################################
set(TARGET_NAME LibCircularBuffer)

set(${TARGET_NAME}_SOURCES 
libcircularbuffer_1.h
libcircularbuffer_1.cpp
)
set(${TARGET_NAME}_TESTS
${CMAKE_CURRENT_SOURCE_DIR}/libcircularbuffer_1_tests.cpp

PARENT_SCOPE # must be reused from main testing program
)

###############################################################################
##########          PLATFORM SPECIFIC GLOBAL SETTINGS
###############################################################################

###############################################################################
##########          INTERNAL PROJECTS (OUR OWN)
###############################################################################
add_library(${TARGET_NAME} ${${TARGET_NAME}_SOURCES})
target_include_directories(${TARGET_NAME} PUBLIC ..)
