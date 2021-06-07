##---------------------------------------------------------------------------
## Author:      Sean D'Epagnier
## Copyright:
## License:     GPLv3+
### *   This program is free software; you can redistribute it and/or modify  *
## *   it under the terms of the GNU General Public License as published by  *
## *   the Free Software Foundation; either version 2 of the License, or     *
## *   (at your option) any later version.                                   *
## *                                                                         *
## *   This program is distributed in the hope that it will be useful,       *
## *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
## *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
## *   GNU General Public License for more details.                          *
## *                                                                         *
## *   You should have received a copy of the GNU General Public License     *
## *   along with this program; if not, write to the                         *
## *   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx,                                       *
## *   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx                                       *
## ***
#-----------------------------------------------------------------------------
# Frontend2 Author: Jon Gough  Frontend2: v1.0.167.0  17/05/2021
# ---------------------------------------------------------------------------
## ----- When changing this file do NOT change the order in which sections occur        ----- ##
## ----- Changes should only be made between the section blocks that identify where     ----- ##
## ----- these changes should be. The whole configuration process relies on this        ----- ##
## ----- sequence to be successful                                                      ----- ##
##                                                                                      ----- ##
##----- Modify section below to include all the details for your plugin                 ----- ##

set(CMLOC "CMakeLists: ")

# define minimum cmake version
cmake_minimum_required(VERSION 3.1.1)
if(COMMAND cmake_policy)
    if(POLICY CMP0043)
        cmake_policy(SET CMP0043 NEW)
    endif(POLICY CMP0043)
    cmake_policy(SET CMP0048 NEW)
    if(POLICY CMP0077)
        cmake_policy(SET CMP0077 NEW)
    endif(POLICY CMP0077)
endif(COMMAND cmake_policy)

# define plugin name, owner and versions
set(VERBOSE_NAME "Pypilot")
set(COMMON_NAME "pypilot")  # Search "getcommonname"in <plugin_pi>.cpp
set(TITLE_NAME "PYPILOT")
set(PACKAGE_CONTACT "Sean D'Epagnier")
set(PACKAGE "pypilot")
set(SHORT_DESCRIPTION "Pypilot PlugIn for OpenCPN")
set(LONG_DESCRIPTION "Control the free software autopilot pypilot. See http://pypilot.org for more details. The plugin connects to pypilot directly implementing a control interface to configure, calibrate and command pypilot from opencpn. For more control and tuning route-following logic, consider the autopilot route plugin.")

# PROJECT(pypilot_pi)
# SET(PACKAGE_NAME pypilot_pi)

set(VERSION_MAJOR "0")
set(VERSION_MINOR "22")
set(VERSION_PATCH "6")
set(VERSION_TWEAK "0")
set(VERSION_DATE "08/06/2021")
set(OCPN_MIN_VERSION "ov50")
set(OCPN_API_VERSION_MAJOR "1")
set(OCPN_API_VERSION_MINOR "16")
set(TP_COMMENT "  * Release for O5 using CI")

set(PARENT "opencpn")

# The next line allows setup of a local webserver with git for testing purposes.
# The default is shown below, but it is done in cmake/pluginconfigure.cmake now.
# This default is needed to build locally and to build flatpak.
#set(GIT_REPOSITORY_SERVER "github.com")

#No longer needed, queried.
#set(GIT_USER "rgleason")
#set(GIT_USER "seandepagnier")
#set(GIT_REPOSITORY_NAME "pypilot_pi")

# Specifies Cloudsmith upload repository suffix for each catalog
set(PROD "prod")    #Standard Repos
set(BETA "beta")    #Standard Repos
set(ALPHA "alpha")  #Standard Repos

set(CLOUDSMITH_USER "opencpn")
#set(CLOUDSMITH_USER "rick-gleason")

# Set if yourCloudsmith Base Repository name does not match your Git Repository name.
#set(CLOUDSMITH_BASE_REPOSITORY "opencpn-plugins") #Rick's customization
set (CLOUDSMITH_BASE_REPOSITORY "pypilot")  #without the pi

set(XML_INFO_URL "https://opencpn.org/wiki/dokuwiki/doku.php?id=opencpn:opencpn_user_manual:plugins:safety:odraw1.6_pi")
set(XML_SUMMARY ${SHORT_DESCRIPTION})
set(XML_DESCRIPTION ${LONG_DESCRIPTION})

## ----- Modify section above to include all the details for your plugin ----- ##
## ----- Modify section below if there are special requirements for the plugin ----- ##

option(PLUGIN_USE_SVG "Use SVG graphics" ON)

set(CMAKE_CXX_STANDARD 11)

# Prefer libGL.so to libOpenGL.so, see CMP0072
set(OpenGL_GL_PREFERENCE "LEGACY")
# Don't use local version of GLU library
set(USE_LOCAL_GLU FALSE)

option(USE_GL "Enable OpenGL support" ON)
message(STATUS "${CMLOC}USE_GL: ${USE_GL}")

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE
        "Release"
        CACHE STRING "Choose the type of build" FORCE)
endif("${CMAKE_BUILD_TYPE}" STREQUAL "")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "" "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
message(STATUS "${CMLOC}Build type: ${CMAKE_BUILD_TYPE}")

##
## ----- The statements below are used to setup standard variables that are required by the CMAKE process - do not remove ----- ##
##

project(${PACKAGE})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

##=======================================
include("PluginSetup")
##=======================================
##
## ----- The above is used to setup standard variables that are required by the CMAKE process - do not remove ----- ##
## ----- Modify section below if there are special requirements for the plugin ----- ##
##

set(CMAKE_VERBOSE_MAKEFILE "Activate verbose mode for make files" ON)

option(Plugin_CXX11 "Use c++11" OFF)


## ----- Modify section above if there are special requirements for the plugin ----- ##
## ----- do not change next section - needed to configure build process ----- ##
##=======================================
include("PluginConfigure")
##=======================================
## ----- do not change section above - needed to configure build process ----- ##
## ----- Change below to match project requirements for source, headers, etc. ----- ##

add_definitions(-DUSE_S57)

SET(SRCS
            src/pypilot_pi.cpp
            src/pypilot_client.cpp
            src/pypilotDialog.cpp
            src/GainsDialog.cpp
            src/ConfigurationDialog.cpp
            src/StatisticsDialog.cpp
            src/pypilotClientDialog.cpp
            src/pypilotUI.cpp
            src/icons.cpp
	)

SET(HDRS
            src/CalibrationPlot.h
            src/ConfigurationDialog.h
			src/GainsDialog.h
            src/icons.h
            src/msvcdefs.h
            src/pypilot_client.h
            src/pypilot_pi.h
            src/pypilotClientDialog.h
            src/pypilotDialog.h
            src/pypilotUI.h
            src/StatisticsDialog.h
            src/wxWTranslateCatalog.h
    )


if(NOT QT_ANDROID)
  SET(SRCS ${SRCS}
     src/CalibrationDialog.cpp
     src/CalibrationPlot.cpp
     )
endif(NOT QT_ANDROID)


#added for android
set(LIBHDRS
    libs/GL/gl.h
    libs/GL/gl_private.h
    libs/GL/glext.h
    libs/GL/glu.h
    libs/wx/include/json_defs.h
    libs/wx/include/jsonreader.h
    libs/wx/include/jsonval.h
    libs/wx/include/jsonwriter.h)

add_definitions(-DPLUGIN_USE_SVG)

##
## Modify/configure 'Include' Directories below for the Plugin
##

# include_directories(BEFORE ${PROJECT_SOURCE_DIR}/include)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/)
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/ocpn-api)
# include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/wx/include)
# include_directories(BEFORE ${PROJECT_SOURCE_DIR}/libs/wxJSON/include)
# may need some of these later

## These are NOT used in Testplugin, used for other plugins
##=======================================
include("PluginJSON")
include("PluginGL")
##=======================================

##
## Statement below is required to collect all the set( headers and SRCS  - Adjust as required
## This add_library  can be used in conditionals below.
####
##==========================================================================
# add_library(${PACKAGE_NAME} SHARED ${SRCS} ${LIBSSRC}  ${SRC_JSON} ${SRC_PLUGINGL})
##==========================================================================
target_sources(${PACKAGE_NAME} PUBLIC ${SRCS} ${HDRS} ${LIBSSRC} ${SRC_JSON} ${SRC_PLUGINGL})

#add_library(${PACKAGE_NAME} SHARED ${SRCS_PYPILOT} ${HDRS} ${EXTSRC} ${LIBSSRC}  ${SRC_JSON} ${SRC_PLUGINGL})
# add_library(${PACKAGE_NAME} SHARED ${SRC_PYPILOT} ${SRC_JSON} ${SRC_PLUGINGL})


# Pypilot does not require tinyxml 
#if(NOT OCPN_FLATPAK_CONFIG)
#    # Build environment not available when flatpak is being configured so following statements will not work
#    message(STATUS "${CMLOC}Adding target link libraries to ${PACKAGE_NAME}")
#
#    add_subdirectory(libs/tinyxml)
#
#    target_link_libraries(${PACKAGE_NAME} ocpn::tinyxml)
#endif(NOT OCPN_FLATPAK_CONFIG)




add_definitions(-DTIXML_USE_STL)

# This may be old, perhaps remove?
#needed only if glshim project is included.
if(QT_ANDROID)
  target_link_libraries(${PACKAGE_NAME}  GL_static)
endif(QT_ANDROID)


##
## ----- Change above to match project requirements ----- ##

# Needed for android builds  - current
if(QT_ANDROID)
    include_directories(BEFORE ${qt_android_include})
endif(QT_ANDROID)

# Needed for all builds
## Do not change next section - needed to configure build process ----- ##
##=======================================
include("PluginInstall")
include("PluginLocalization")
include("PluginPackage")
##=======================================
## ----- do not change section above - needed to configure build process ----- ##


message(STATUS "${CMLOC}include directories: ")
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
    message(STATUS "${CMLOC}dir='${dir}'")
endforeach()
