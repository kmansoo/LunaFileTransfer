#pragma once

#include "ccCore/ccString.h"

#include "ccWebServer/ccWebsocketManager.h"

class FileReceiver : public Luna::ccWebsocketManager {
public:
    FileReceiver();

public:
    bool ws_filereceiver(Luna::ccWebsocket::ccWebSocketEvent eEvent, std::shared_ptr<Luna::ccWebsocket> pWS, const std::string strData);
};
