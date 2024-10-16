cmake_minimum_required(VERSION 3.5)

project(3DViewer_v2_1 VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -W -Wextra)

#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGLWidgets)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGLWidgets)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGL)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGLWidgets)

set(PROJECT_SOURCES
        ../main.cc
        glview.h
        glview.cc
        mainwindow.h
        mainwindow.cc
        mainwindow.ui
        settings.h
        settings.cc
        ../model/facade.h
        ../model/parser.h
        ../model/parser.cc
        ../model/transform.cc
        ../model/transform.h
        # ../model/texture.cc
        ../model/texture.h
        ../controller/controller.h
        ../observer/observer.h

         gif/gif.h
#        gifimage/gif_hash.h
#        gifimage/gif_lib_private.h
#        gifimage/gif_lib.h
#        gifimage/qgifimage.h
#        gifimage/qgifimage_p.h
#        gifimage/qgifglobal.h
#        gifimage/dgif_lib.c
#        gifimage/egif_lib.c
#        gifimage/gif_err.c
#        gifimage/gif_font.c
#        gifimage/gif_hash.c
#        gifimage/gifalloc.c
#        gifimage/quantize.c
#        gifimage/qgifimage.cpp
)

#foreach(dir ${SOURCE_DIRS})
#    file(GLOB CPP_SOURCES "${dir}/*.cpp")
#    file(GLOB C_SOURCES "${dir}/*.c")
#    file(GLOB HEADER_SOURCES "${dir}/*.h")
#    file(GLOB UI_SOURCES "${dir}/*.ui")
#    list(APPEND PROJECT_SOURCES ${CPP_SOURCES} ${C_SOURCES} ${HEADER_SOURCES} ${UI_SOURCES})
#endforeach()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3DViewer_v2_1
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 3DViewer_v2_1 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(3DViewer_v2_1 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(3DViewer_v2_1
            ${PROJECT_SOURCES}
        )
    endif()
endif()

#target_link_libraries(3DViewer_v2_1 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#target_link_libraries(3DViewer_v2_1 PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
#target_link_libraries(3DViewer_v2_1 PRIVATE OpenGL -lGL -lGLU)
target_link_libraries(3DViewer_v2_1 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(3DViewer_v2_1 PRIVATE Qt${QT_VERSION_MAJOR}::OpenGL)
target_link_libraries(3DViewer_v2_1 PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)

set_target_properties(3DViewer_v2_1 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
set(props_to_set INTERFACE_INCLUDE_DIRECTORIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES
                         INTERFACE_COMPILE_DEFINITIONS INTERFACE_COMPILE_OPTIONS
                         INTERFACE_COMPILE_FEATURES)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3DViewer_v2_1)
endif()
