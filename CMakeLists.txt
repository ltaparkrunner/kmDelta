cmake_minimum_required(VERSION 3.14)

project(kmdelta6 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(QT_DIR "~/Qt/6_5_2/qtbase/lib/cmake/Qt6/")
#set(QT6_DIR "/home/alex/Qt/6_5_2/qtbase/lib/cmake/Qt6/")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick Charts Network Test)
message("QT_VERSION_MAJOR= ${QT_VERSION_MAJOR}" )
# if(QT_VERSION_MAJOR EQUAL 6)
#     set(QT_DIR "~/Qt/6_5_2/qtbase/lib/cmake/Qt6/")
#     set(QT6_DIR "/home/alex/Qt/6_5_2/qtbase/lib/cmake/Qt6/")
# endif()
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Charts Network Test)
set(src_dir "src/")
set(inc_dir "inc/")
if(QT_VERSION_MAJOR EQUAL 6)
    set(PROJECT_SOURCES
        ${src_dir}main2.cpp
            qml/qml.qrc
            ${inc_dir}ipAddr.h
            ${src_dir}ipAddr.cpp
            ${inc_dir}mbtcpClient.h
            ${src_dir}mbtcpClient.cpp
            ${inc_dir}crc32.h
            ${src_dir}crc32.cpp
    )
elseif(QT_VERSION_MAJOR EQUAL 5)
    set(PROJECT_SOURCES
        ${src_dir}main2.cpp
            qml/qml_5.qrc
            ${inc_dir}ipAddr.h
            ${src_dir}ipAddr.cpp
            ${inc_dir}mbtcpClient.h
            ${src_dir}mbtcpClient.cpp
            ${inc_dir}crc32.h
            ${src_dir}crc32.cpp
    )
else()
    message(FATAL_ERROR "Unsupported Qt version")
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(kmdelta6
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
#            ${inc_dir}tcpIntrfc.h
            ${inc_dir}configs.h ${src_dir}configs.cpp
            ${inc_dir}vmConfigsChat.h ${src_dir}vmConfigsChat.cpp
            ${inc_dir}chat.h ${src_dir}chat.cpp
            ${inc_dir}pointtimer.h ${src_dir}pointtimer.cpp
#            ${inc_dir}pTmrIntrfc.h
#            main2.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET kmdelta6 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(kmdelta6 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(kmdelta6
          ${PROJECT_SOURCES}
#          tcpIntrfc.h
#           ${inc_dir}tcpIntrfc.h
#          tcpIntrfc.h
#          tcpIntrfc.cpp
#          tcpIntrfc.cpp
          ${inc_dir}configs.h ${src_dir}configs.cpp
          ${inc_dir}vmConfigsChat.h ${src_dir}vmConfigsChat.cpp
          ${inc_dir}chat.h ${src_dir}chat.cpp
          ${inc_dir}pointtimer.h ${src_dir}pointtimer.cpp
#          ${inc_dir}pTmrIntrfc.h
        )
    endif()
endif()

target_compile_definitions(kmdelta6
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(kmdelta6
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick  Qt${QT_VERSION_MAJOR}::Charts Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Test)
target_include_directories(kmdelta6 PUBLIC "inc")
set_target_properties(kmdelta6 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(kmdelta6)
    qt_finalize_executable(kmdelta6)
endif()
