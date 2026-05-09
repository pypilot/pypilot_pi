# ~~~
# Summary:      Local, generic plugin setup
# Copyright (c) 2020-2021 Mike Rossiter
# License:      GPLv3+
# ~~~

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.


# -------- Options ----------

set(OCPN_TEST_REPO
    "opencpn/pypilot-alpha"
    CACHE STRING "Default repository for untagged builds"
)
set(OCPN_BETA_REPO
    "opencpn/pypilot-beta"
    CACHE STRING
    "Default repository for tagged builds matching 'beta'"
)
set(OCPN_RELEASE_REPO
    "opencpn/pypilot-prod"
    CACHE STRING
    "Default repository for tagged builds not matching 'beta'"
)

#
#
# -------  Plugin setup --------
#
set(PKG_NAME pypilot_pi) #or _pi
set(PKG_VERSION  0.7.0)
set(PKG_PRERELEASE "")  # Empty, or a tag like 'beta'

set(DISPLAY_NAME pypilot)    # Dialogs, installer artifacts, ...
set(PLUGIN_API_NAME pypilot) # As of GetCommonName() in plugin API
set(PKG_SUMMARY "pypilot plugin")
set(PKG_DESCRIPTION "pypilot plugin, illustrates the use of the different OpenCPN Plugin API's ")
set(PKG_AUTHOR "Sean D'Epagnier")
set(PKG_IS_OPEN_SOURCE "yes")
set(PKG_HOMEPAGE https://github.com/pypilot/pypilot)
set(PKG_INFO_URL https://opencpn.org/OpenCPN/plugins/pypilotplugin.html)
set(PKG_API_LIB api-18)   # Specify the plugin API level

add_definitions(-DocpnUSE_GL) # Specifiy the use of OpenGL

include_directories(${CMAKE_SOURCE_DIR}/inc)

set(SRC
            ${CMAKE_SOURCE_DIR}/src/pypilot_pi.cpp
            ${CMAKE_SOURCE_DIR}/src/pypilot_client.cpp
            ${CMAKE_SOURCE_DIR}/src/pypilotDialog.cpp
            ${CMAKE_SOURCE_DIR}/src/GainsDialog.cpp
            ${CMAKE_SOURCE_DIR}/src/ConfigurationDialog.cpp
            ${CMAKE_SOURCE_DIR}/src/StatisticsDialog.cpp
            ${CMAKE_SOURCE_DIR}/src/SettingsDialog.cpp
            ${CMAKE_SOURCE_DIR}/src/pypilotClientDialog.cpp
            ${CMAKE_SOURCE_DIR}/src/pypilotUI.cpp
            ${CMAKE_SOURCE_DIR}/src/CalibrationDialog.cpp
            ${CMAKE_SOURCE_DIR}/src/CalibrationPlot.cpp
            ${CMAKE_SOURCE_DIR}/src/icons.cpp
	)

set(INC
            ${CMAKE_SOURCE_DIR}/src/CalibrationPlot.h
            ${CMAKE_SOURCE_DIR}/src/ConfigurationDialog.h
            ${CMAKE_SOURCE_DIR}/src/GainsDialog.h
            ${CMAKE_SOURCE_DIR}/src/icons.h
            ${CMAKE_SOURCE_DIR}/src/msvcdefs.h
            ${CMAKE_SOURCE_DIR}/src/pypilot_client.h
            ${CMAKE_SOURCE_DIR}/src/pypilot_pi.h
            ${CMAKE_SOURCE_DIR}/src/pypilotClientDialog.h
            ${CMAKE_SOURCE_DIR}/src/pypilotDialog.h
            ${CMAKE_SOURCE_DIR}/src/pypilotUI.h
            ${CMAKE_SOURCE_DIR}/src/StatisticsDialog.h
            ${CMAKE_SOURCE_DIR}/src/SettingsDialog.h
            ${CMAKE_SOURCE_DIR}/src/wxWTranslateCatalog.h
)


set (SOURCE_FILES ${SRC} ${INC})

macro(late_init)
  # Perform initialization after the PACKAGE_NAME library, compilers
  # and ocpn::api is available.
  if (APPLE)
    target_compile_definitions(${PACKAGE_NAME} PUBLIC OCPN_GHC_FILESYSTEM)
  endif ()
endmacro ()

macro(add_plugin_libraries)

  message(STATUS "${CMLOC}Adding target link libraries to ${PACKAGE_NAME}")

  if (WIN32)
    add_subdirectory(opencpn-libs/WindowsHeaders)
    target_link_libraries(${PACKAGE_NAME} windows::headers)
  endif (WIN32)

  add_subdirectory(opencpn-libs/tinyxml)
  target_link_libraries(${PACKAGE_NAME} ocpn::tinyxml)

    add_subdirectory(opencpn-libs/jsoncpp)
    target_link_libraries(${PACKAGE_NAME} ocpn::jsoncpp)

  add_subdirectory(opencpn-libs/wxJSON)
  target_link_libraries(${PACKAGE_NAME} ocpn::wxjson)

  add_subdirectory(opencpn-libs/plugin_dc)
  target_link_libraries(${PACKAGE_NAME} ocpn::plugin-dc)

  add_subdirectory(libs/wxservdisc)
  target_link_libraries(${PACKAGE_NAME} wxservdisc)

endmacro ()

  include_directories(${CMAKE_SOURCE_DIR}/libs/wxservdisc/src)

