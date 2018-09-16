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

INCLUDE("cmake/PluginConfigure.cmake")

#ADD_DEFINITIONS( "--std=gnu++11" )

SET(SRC_PYPILOT
            src/pypilot_pi.cpp
            src/signalk_client.cpp
            src/pypilot_signalk_client.cpp
            src/pypilotDialog.cpp
            src/GainsDialog.cpp
            src/ConfigurationDialog.cpp
            src/StatisticsDialog.cpp
            src/CalibrationDialog.cpp
            src/pypilotUI.cpp
            src/icons.cpp
	)

#INCLUDE("cmake/PluginNMEA.cmake")
INCLUDE("cmake/PluginJSON.cmake")
INCLUDE("cmake/PluginGL.cmake")

ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_PYPILOT} ${SRC_JSON} ${SRC_PLUGINGL})
ADD_DEFINITIONS(-DTIXML_USE_STL)

INCLUDE("cmake/PluginInstall.cmake")
INCLUDE("cmake/PluginLocalization.cmake")
INCLUDE("cmake/PluginPackage.cmake")
