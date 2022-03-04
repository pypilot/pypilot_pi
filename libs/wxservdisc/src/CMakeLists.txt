
#
# source and targets
#
SET(wxservdisc_LIB_SRCS
   1035.c
   mdnsd.c
   wxServDisc.cpp
   wxServDisc.h
   1035.h
   mdnsd.h
)

SET(CMAKE_CXX_FLAGS "-fPIC")

add_library(wxservdisc STATIC ${wxservdisc_LIB_SRCS})


#
# dependencies
#
find_package(wxWidgets REQUIRED core base net)
include(${wxWidgets_USE_FILE})
target_link_libraries(wxservdisc ${wxWidgets_LIBRARIES})



#target_link_libraries(wxservdisc ws2_32)

#set_target_properties(wxservdisc PROPERTIES VERSION 4.2.0 SOVERSION 4)


#
# installation
#
if(WXSERVDISC_INSTALL)
  install(TARGETS wxservdisc DESTINATION lib)

  install(FILES  wxServDisc.h DESTINATION include)
endif()
