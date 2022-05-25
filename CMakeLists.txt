cmake_minimum_required(VERSION 3.10)

project(galament)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

execute_process(COMMAND protoc -I=${SOURCE_DIR}/common/protobuf --cpp_out=${SOURCE_DIR}/common/protobuf ${SOURCE_DIR}/common/protobuf/messages.proto)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
	set(EXTRA_LIBS ${Boost_LIBRARIES} boost_system)
endif()

find_package(Protobuf REQUIRED)
if(Protobuf_FOUND)
    include_directories(${Protobuf_INCLUDE_DIRS})
	set(EXTRA_LIBS ${EXTRA_LIBS} ${Protobuf_LIBRARIES})
endif()

include(cmake/client.cmake)
include(cmake/server.cmake)