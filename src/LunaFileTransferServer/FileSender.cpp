
#include "FileSender.h"

FileSender::FileSender() {
    this->add_function("/ws_filesender", std::bind(&FileSender::ws_filesender, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

bool FileSender::ws_filesender(Luna::ccWebsocket::ccWebSocketEvent eEvent, std::shared_ptr<Luna::ccWebsocket> pWS, const std::string strData) {
    switch ((int)eEvent) {
    case Luna::ccWebsocket::ccWebSocketEvent_Connected:
    {
        //  Luna::ccString::format(strMessage, "%08x: Join", pWS->get_instance());
    }
    break;

    case Luna::ccWebsocket::ccWebSocketEvent_ReceivedData:
    {
        std::string strMessage(strData);

        //  Luna::ccString::format(strBroadcastMsg, "%08x: %s", pWS->get_instance(), strMessage.c_str());
    }
    break;

    case Luna::ccWebsocket::ccWebSocketEvent_Disconnected:
    {
        //  Luna::ccString::format(strMessage, "%08x: Leave", pWS->get_instance());
    }
    break;
    }
    return true;
}
