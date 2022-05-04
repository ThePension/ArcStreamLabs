cmake_minimum_required(VERSION 3.5)

project(ArcStreamLabs VERSION 0.1 LANGUAGES CXX)

find_package( OpenCV REQUIRED)

add_subdirectory("lib/LibCircularBuffer")
add_subdirectory("lib/LibUndoRedo")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.h src/mainwindow.cpp
        src/helper.h src/helper.cpp
        src/videostream.h src/videostream.cpp
        src/arcstreamlab.h src/arcstreamlab.cpp
        src/settings.h src/settings.cpp
        src/imageprocessing.h src/imageprocessing.cpp
        src/dialog/colorimetry/colorimetry.h src/dialog/colorimetry/colorimetry.cpp
        src/dialog/colorimetry/colorimetrytabs.h src/dialog/colorimetry/colorimetrytabs.cpp
        src/dialog/colorimetry/colorimetryactions.h src/dialog/colorimetry/colorimetryactions.cpp
        src/dialog/colorimetry/colorimetryfilter.h src/dialog/colorimetry/colorimetryfilter.cpp
        src/dialog/filter/filter.h src/dialog/filter/filter.cpp
        src/dialog/filter/filteractions.h src/dialog/filter/filteractions.cpp
        src/dialog/filter/sobelfilter.h src/dialog/filter/sobelfilter.cpp
        src/dialog/specialEffect/specialeffect.h src/dialog/specialEffect/specialeffect.cpp
        src/dialog/animation/animation.h src/dialog/animation/animation.cpp
        src/dialog/filter/stylizationfilter.h src/dialog/filter/stylizationfilter.cpp
        Ressources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ArcStreamLabs
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ArcStreamLabs APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ArcStreamLabs SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ArcStreamLabs
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ArcStreamLabs PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${OpenCV_LIBS} LibCircularBuffer LibUndoRedo)

set_target_properties(ArcStreamLabs PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ArcStreamLabs)
endif()


####################################
#            Unit Test #
####################################
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
  )

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(tests test/tests.cpp ${LibCircularBuffer_TESTS} ${LibUndoRedo_TESTS}) # tests.cpp
target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tests gtest_main ${OpenCV_LIBS} LibCircularBuffer LibUndoRedo) # tests.cpp

include(GoogleTest)
gtest_discover_tests(tests)
enable_testing()

####################################
#             Doxygen #
####################################
find_package(Doxygen)

if(NOT DOXYGEN_FOUND)
message(FATAL_ERROR "Doxygen is needed to build the documentation.")
endif()

set(doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

add_custom_target(BuildDoc ALL
  COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..
  COMMENT "Generating Doxygen documentation"
  VERBATIM
)
