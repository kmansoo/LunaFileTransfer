#pragma once

#include "ccCore/ccString.h"

#include "ccWebServer/ccWebsocketManager.h"
#include "FileTransferSessionInfo.h"
#include <fstream>

class FileReceiver : public Luna::ccWebsocketManager {
public:
    FileReceiver();

private:
    bool ws_filereceiver(Luna::ccWebsocket::ccWebSocketEvent eEvent, std::shared_ptr<Luna::ccWebsocket> pWS, const std::string message);

private:
    std::mutex mtx_;
    std::map< std::int32_t, std::shared_ptr<FileTransferSessionInfo> >  file_transfer_session_list_;
};
