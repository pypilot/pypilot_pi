##---------------------------------------------------------------------------
## Author:      Sean D'Epagnier
## Copyright:   
## License:     GPLv3+
##---------------------------------------------------------------------------
 
# define minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)

PROJECT(pypilot_pi)
SET(PACKAGE_NAME pypilot_pi)
SET(VERBOSE_NAME Pypilot)
SET(TITLE_NAME PYPILOT)
SET(CPACK_PACKAGE_CONTACT "Sean D'Epagnier ")

SET(BUNDLE_DATA FALSE)

INCLUDE( VERSION.cmake )
SET(VERSION_MAJOR ${PLUGIN_VERSION_MAJOR})
SET(VERSION_MINOR ${PLUGIN_VERSION_MINOR})
SET(VERSION_PATCH ${PLUGIN_VERSION_PATCH})
SET(VERSION_DATE ${PLUGIN_VERSION_DATE})

SET(PLUGIN_VERSION "${PLUGIN_VERSION_MAJOR}.${PLUGIN_VERSION_MINOR}.${PLUGIN_VERSION_PATCH}" )

INCLUDE("cmake/PluginConfigure.cmake")

ADD_DEFINITIONS( "--std=gnu++11" )

SET(SRC_PYPILOT
            src/pypilot_pi.cpp
            src/signalk_client.cpp
            src/pypilot_signalk_client.cpp
            src/pypilotDialog.cpp
            src/GainsDialog.cpp
            src/ConfigurationDialog.cpp
            src/StatisticsDialog.cpp
            src/CalibrationDialog.cpp
            src/pydc.cpp
            src/TexFont.cpp
            src/pypilotUI.cpp
            src/icons.cpp
	)

#INCLUDE("cmake/PluginNMEA.cmake")
INCLUDE("cmake/PluginJSON.cmake")

ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_PYPILOT} ${SRC_JSON})
ADD_DEFINITIONS(-DTIXML_USE_STL)

INCLUDE("cmake/PluginInstall.cmake")
INCLUDE("cmake/PluginLocalization.cmake")
INCLUDE("cmake/PluginPackage.cmake")
