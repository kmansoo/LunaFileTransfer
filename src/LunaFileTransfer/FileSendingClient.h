#pragma once

#include "ccCore/ccString.h"
#include "ccWebsocketClient/ccEasyWebsocketClient.h"

class FileSendingClient {
public:
  FileSendingClient();

public:
  bool send(const std::string &url, const std::string &filename);

private:
  void recv_data_from_websocket(Luna::ccWebsocket::ccWebSocketEvent ws_event,
                                const std::string &message);

private:
  Luna::ccEasyWebsocketClient ws_client_;
};
