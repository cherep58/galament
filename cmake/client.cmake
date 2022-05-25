set(CLIENT_SOURCES 
	${SOURCE_DIR}/client/main.cpp
	${SOURCE_DIR}/client/helper/random_generator.cpp
	${SOURCE_DIR}/client/helper/statistic_printer.cpp
	${SOURCE_DIR}/client/websocket/client.cpp
	${SOURCE_DIR}/client/work_mode/abstract.cpp
	${SOURCE_DIR}/client/work_mode/factory.cpp
	${SOURCE_DIR}/client/work_mode/get_statistic.cpp
	${SOURCE_DIR}/client/work_mode/send_data_packet.cpp
	${SOURCE_DIR}/common/data_types/data_packet.cpp
	${SOURCE_DIR}/common/data_types/timestamp.cpp
	${SOURCE_DIR}/common/data_types/uuid.cpp
	${SOURCE_DIR}/common/data_types/uuid_statistic.cpp
	${SOURCE_DIR}/common/protobuf/message_serializer.cpp
	${SOURCE_DIR}/common/protobuf/messages.pb.cc
	)
	
add_executable(client ${CLIENT_SOURCES})
	
target_include_directories(client PUBLIC ${SOURCE_DIR})
target_include_directories(client PUBLIC ${SOURCE_DIR}/client)
target_include_directories(client PUBLIC ${SOURCE_DIR}/third_party/websocketpp)

if (MSVC)
	target_compile_options(client PRIVATE /W4)
else()
	target_compile_options(client PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

target_link_libraries(client PUBLIC ${EXTRA_LIBS})