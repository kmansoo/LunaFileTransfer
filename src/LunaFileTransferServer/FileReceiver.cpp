#include <iostream>

#include "json/reader.h"
#include "json/value.h"

#include "FileReceiver.h"

FileReceiver::FileReceiver() {
    this->add_function("/ws_filereceiver", std::bind(&FileReceiver::ws_filereceiver, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

bool FileReceiver::ws_filereceiver(Luna::ccWebsocket::ccWebSocketEvent eEvent, std::shared_ptr<Luna::ccWebsocket> websocket, const std::string message) {
    switch ((int)eEvent) {
    case Luna::ccWebsocket::ccWebSocketEvent_Connected:
    {
        std::lock_guard<std::mutex> lock(mtx_);

        auto ftsi = std::make_shared<FileTransferSessionInfo>(websocket);
        file_transfer_session_list_[websocket->get_instance()] = ftsi;    
    }
    break;

    case Luna::ccWebsocket::ccWebSocketEvent_ReceivedData:
    {
        auto ftsi = file_transfer_session_list_[websocket->get_instance()];

        ftsi->parse_packet(message);
    }
    break;

    case Luna::ccWebsocket::ccWebSocketEvent_Disconnected:
    {
        std::lock_guard<std::mutex> lock(mtx_);

        auto it = file_transfer_session_list_.find(websocket->get_instance());

        if (it == file_transfer_session_list_.end())
            return false;

        it->second->close();
        file_transfer_session_list_.erase(it);
    }
    break;
    }
    return true;
}
