#include <iostream>

#include "FileReceiver.h"

FileReceiver::FileReceiver() {
    this->add_function("/ws_filereceiver", std::bind(&FileReceiver::ws_filereceiver, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

bool FileReceiver::ws_filereceiver(Luna::ccWebsocket::ccWebSocketEvent eEvent, std::shared_ptr<Luna::ccWebsocket> pWS, const std::string strData) {
    std::cout << "[FileReceiver], eEvent = " << eEvent << std::endl;

    switch ((int)eEvent) {
    case Luna::ccWebsocket::ccWebSocketEvent_Connected:
    {
        std::cout << "[FileReceiver], Connected." << std::endl;
        //  Luna::ccString::format(strMessage, "%08x: Join", pWS->get_instance());        
    }
    break;

    case Luna::ccWebsocket::ccWebSocketEvent_ReceivedData:
    {
        std::cout << "[FileReceiver], ReceivedData, " << strData << std::endl;
        pWS->send(std::string("Nice meet you!"));
        //  Luna::ccString::format(strBroadcastMsg, "%08x: %s", pWS->get_instance(), strMessage.c_str());
    }
    break;

    case Luna::ccWebsocket::ccWebSocketEvent_Disconnected:
    {
        std::cout << "[FileReceiver], Disconnected." << std::endl;
        //  Luna::ccString::format(strMessage, "%08x: Leave", pWS->get_instance());
    }
    break;
    }
    return true;
}
