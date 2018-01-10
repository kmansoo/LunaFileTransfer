#pragma once

#include <memory>

#include "ccCore/ccString.h"
#include "ccWebServer/ccWebsocket.h"

class FileSendingClient {
public:
  FileSendingClient();

public:
  bool send(const std::string &url, const std::string &filename);

private:
  void recv_data_from_websocket(Luna::ccWebsocket::ccWebSocketEvent ws_event,
                                const std::string &message);

private:
  std::shared_ptr<Luna::ccWebsocket> ws_client_;
  bool is_ws_closed_;
};
