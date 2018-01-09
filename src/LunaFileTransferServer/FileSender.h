#pragma once

#include "ccCore/ccString.h"

#include "ccWebServer/ccWebsocketManager.h"

class FileSender : public Luna::ccWebsocketManager {
public:
    FileSender();

public:
    bool ws_filesender(Luna::ccWebsocket::ccWebSocketEvent eEvent, std::shared_ptr<Luna::ccWebsocket> pWS, const std::string strData);
};
