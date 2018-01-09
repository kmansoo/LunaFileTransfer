
#include <iostream>
#include "ccCore/ccCoreAPI.h"

#include "FileSendingClient.h"

FileSendingClient::FileSendingClient() {
  ws_client_.set_event_listener(
      std::bind(&FileSendingClient::recv_data_from_websocket, this,
                std::placeholders::_1, std::placeholders::_2));
}

bool FileSendingClient::send(const std::string &url, const std::string &filename) {

  if (ws_client_.open(url) == true) {
      
      ws_client_.send(std::string("Hello!"));
      
      Luna::sleep(1000);
  }

  ws_client_.close();

  return false;
}

void FileSendingClient::recv_data_from_websocket(Luna::ccWebsocket::ccWebSocketEvent ws_event, const std::string& message) {
    switch ((int)ws_event) {
    case Luna::ccWebsocket::ccWebSocketEvent_Connected:
    {
        std::cout << "[FileSendingClient], Connected." << std::endl;
    }
    break;

    case Luna::ccWebsocket::ccWebSocketEvent_Disconnected:
    {
        std::cout << "[FileSendingClient], Disconnected." << std::endl;
    }
    break;

    case Luna::ccWebsocket::ccWebSocketEvent_ReceivedData:
    {
        std::cout << "[FileSendingClient], ReceivedData, " << message << std::endl;
    }
    break;
    }
}
