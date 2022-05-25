set(SERVER_SOURCES 
	${SOURCE_DIR}/server/main.cpp
	${SOURCE_DIR}/server/command/command/abstract.cpp
	${SOURCE_DIR}/server/command/command/get_statistic.cpp
	${SOURCE_DIR}/server/command/command/save_data_packet.cpp
	${SOURCE_DIR}/server/command/executor/get_statistic.cpp
	${SOURCE_DIR}/server/command/executor/save_data_packet.cpp
	${SOURCE_DIR}/server/command/command_executor.cpp
	${SOURCE_DIR}/server/command/command_producer.cpp
	${SOURCE_DIR}/server/command/command_queue.cpp
	${SOURCE_DIR}/server/database/database.cpp
	${SOURCE_DIR}/server/handler/client_message_handler.cpp
	${SOURCE_DIR}/server/websocket/server.cpp
	${SOURCE_DIR}/server/websocket/client.cpp
	${SOURCE_DIR}/common/data_types/data_packet.cpp
	${SOURCE_DIR}/common/data_types/timestamp.cpp
	${SOURCE_DIR}/common/data_types/uuid.cpp
	${SOURCE_DIR}/common/data_types/uuid_statistic.cpp
	${SOURCE_DIR}/common/protobuf/message_serializer.cpp
	${SOURCE_DIR}/common/protobuf/messages.pb.cc
	${SOURCE_DIR}/third_party/SQLiteCpp/sqlite3/sqlite3.c
	${SOURCE_DIR}/third_party/SQLiteCpp/src/Backup.cpp
	${SOURCE_DIR}/third_party/SQLiteCpp/src/Column.cpp
	${SOURCE_DIR}/third_party/SQLiteCpp/src/Database.cpp
	${SOURCE_DIR}/third_party/SQLiteCpp/src/Exception.cpp
	${SOURCE_DIR}/third_party/SQLiteCpp/src/Savepoint.cpp
	${SOURCE_DIR}/third_party/SQLiteCpp/src/Statement.cpp
	${SOURCE_DIR}/third_party/SQLiteCpp/src/Transaction.cpp
	)
	
add_executable(server ${SERVER_SOURCES})
	
target_include_directories(server PUBLIC ${SOURCE_DIR})
target_include_directories(server PUBLIC ${SOURCE_DIR}/server)
target_include_directories(server PUBLIC ${SOURCE_DIR}/third_party/websocketpp)
target_include_directories(server PUBLIC ${SOURCE_DIR}/third_party/SQLiteCpp/sqlite3)
target_include_directories(server PUBLIC ${SOURCE_DIR}/third_party/SQLiteCpp/include)

if (MSVC)
	target_compile_options(server PRIVATE /W4)
else()
	target_compile_options(server PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

target_compile_definitions(server PRIVATE 
	-DSQLITE_THREADSAFE=0 
	-DSQLITE_OMIT_LOAD_EXTENSION
	)

target_link_libraries(server PUBLIC ${EXTRA_LIBS})