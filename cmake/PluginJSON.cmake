##---------------------------------------------------------------------------
## Author:      Sean D'Epagnier
## Copyright:   2015
## License:     GPLv3+
##---------------------------------------------------------------------------

SET(SRC_JSON
	    src/jsoncpp/json_reader.cpp
	    src/jsoncpp/json_value.cpp
	    src/jsoncpp/json_writer.cpp
            )

set_source_files_properties(src/jsoncpp/json_reader.cpp PROPERTIES COMPILE_FLAGS "-std=c++11")
set_source_files_properties(src/jsoncpp/json_value.cpp PROPERTIES COMPILE_FLAGS "-std=c++11")
set_source_files_properties(src/jsoncpp/json_writer.cpp PROPERTIES COMPILE_FLAGS "-std=c++11")

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/jsoncpp)
