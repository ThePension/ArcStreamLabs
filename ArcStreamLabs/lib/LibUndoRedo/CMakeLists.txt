###############################################################################
##########          MINIMUM REQUIREMENTS (some need to be BEFORE project command)
###############################################################################
find_package( OpenCV REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )
###############################################################################
##########          REQUIREMENTS + GLOBAL DEFINITION
###############################################################################
set(TARGET_NAME LibUndoRedo)

set(${TARGET_NAME}_SOURCES
    actionmanager.h actionmanager.cpp
    undoableaction.h
)
set(${TARGET_NAME}_TESTS
${CMAKE_CURRENT_SOURCE_DIR}/undoredo_tests.cpp

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
