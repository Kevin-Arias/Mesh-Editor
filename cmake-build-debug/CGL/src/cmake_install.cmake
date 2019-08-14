# Install script for directory: /Users/Family/Desktop/p2-meshedit-Kevin-Arias-master/CGL/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/Family/Desktop/p2-meshedit-Kevin-Arias-master/cmake-build-debug/CGL/src/libCGL.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCGL.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCGL.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCGL.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/CGL" TYPE FILE FILES
    "/Users/Family/Desktop/p2-meshedit-Kevin-Arias-master/CGL/src/CGL.h"
    "/Users/Family/Desktop/p2-meshedit-Kevin-Arias-master/CGL/src/vector2D.h"
    "/Users/Family/Desktop/p2-meshedit-Kevin-Arias-master/CGL/src/vector3D.h"
    "/Users/Family/Desktop/p2-meshedit-Kevin-Arias-master/CGL/src/vector4D.h"
    "/Users/Family/Desktop/p2-meshedit-Kevin-Arias-master/CGL/src/matrix3x3.h"
    "/Users/Family/Desktop/p2-meshedit-Kevin-Arias-master/CGL/src/matrix4x4.h"
    "/Users/Family/Desktop/p2-meshedit-Kevin-Arias-master/CGL/src/quaternion.h"
    "/Users/Family/Desktop/p2-meshedit-Kevin-Arias-master/CGL/src/complex.h"
    "/Users/Family/Desktop/p2-meshedit-Kevin-Arias-master/CGL/src/color.h"
    "/Users/Family/Desktop/p2-meshedit-Kevin-Arias-master/CGL/src/osdtext.h"
    "/Users/Family/Desktop/p2-meshedit-Kevin-Arias-master/CGL/src/viewer.h"
    "/Users/Family/Desktop/p2-meshedit-Kevin-Arias-master/CGL/src/base64.h"
    "/Users/Family/Desktop/p2-meshedit-Kevin-Arias-master/CGL/src/tinyxml2.h"
    "/Users/Family/Desktop/p2-meshedit-Kevin-Arias-master/CGL/src/renderer.h"
    )
endif()

