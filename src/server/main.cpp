#include <iostream>

#include "database/database.h"
#include "websocket/server.h"
#include "handler/client_message_handler.h"

int main(int argc, char *argv[])
{
    using namespace std::chrono_literals;

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " port" << std::endl;
        return 1;
    }

    uint16_t port = static_cast<uint16_t>(std::stoul(argv[1]));
    
    auto path = std::filesystem::current_path();
    auto db_path = path / "db.db";

    galament::server::database::Database db;
    if (!db.Initialize(db_path)) {
        std::cerr << "Can't initialize database" << std::endl;
        return 1;
    }

    galament::server::handler::ClientMessageHandler message_handler(db);
    galament::server::websocket::Server server(message_handler);
    server.Run(port);

    return 0;
}