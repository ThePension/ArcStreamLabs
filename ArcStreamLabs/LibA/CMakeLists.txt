###############################################################################
##########          MINIMUM REQUIREMENTS (some need to be BEFORE project command)
###############################################################################

###############################################################################
##########          REQUIREMENTS + GLOBAL DEFINITION
###############################################################################
set(TARGET_NAME LibA)

set(${TARGET_NAME}_SOURCES 
liba_1.h
liba_1.cpp
)
set(${TARGET_NAME}_TESTS
${CMAKE_CURRENT_SOURCE_DIR}/liba_1_tests.cpp

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
