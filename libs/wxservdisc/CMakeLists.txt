cmake_minimum_required(VERSION 3.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(WXSERVDISC_INSTALL "Generate installation target" ON)

add_subdirectory(src)
#add_subdirectory(examples)


########### install files ###############

if(WXSERVDISC_INSTALL)
    install(FILES  README.md 	AUTHORS 	NEWS DESTINATION doc/wxservdisc)
endif()

