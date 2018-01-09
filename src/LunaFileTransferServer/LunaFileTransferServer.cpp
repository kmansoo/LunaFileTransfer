
#include <memory>

#include "ccCore/ccCoreAPI.h"
#include "ccCore/ccString.h"

#include "ccNetwork/ccNetworkManager.h"

#include "ccWebServer/ccWebServerManager.h"

#include "ccMongooseServer/ccMongooseWebServerObjectFactory.h"
#include "ccWebServer/ccWebsocketManager.h"

#include "FileReceiver.h"
#include "FileSender.h"

int main(int argc, char* argv[]) {

    Luna::ccNetworkManager::instance().init();

    //  choose a Web Server : Abstract Factory Design Pattern
    std::string html_path = ".";
    std::string port = "9097";

    if (argc == 2)
        html_path = argv[1];

    if (argc == 3) {
       port = argv[1];
       html_path = argv[2];
    }

    std::cout << "port = " << port << ", path = " << html_path << std::endl;
 
    Luna::ccWebServerManager::instance().attach_factory(std::make_shared<Luna::ccMongooseWebServerObjectFactory>());

    std::shared_ptr<Luna::ccWebsocketManager>   ws_filereceiver = std::make_shared<FileReceiver>();
    std::shared_ptr<Luna::ccWebsocketManager>   ws_filesender = std::make_shared<FileSender>();

    Luna::ccWebServerManager::instance().create_web_server("WebServer #1", port, html_path);

    Luna::ccWebServerManager::instance().add_websocket_manager(ws_filereceiver);
    Luna::ccWebServerManager::instance().add_websocket_manager(ws_filesender);

    Luna::ccWebServerManager::instance().start();

    while (1)
        Luna::sleep(100);
}
