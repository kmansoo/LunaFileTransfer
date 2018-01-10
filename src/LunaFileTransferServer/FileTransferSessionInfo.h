#pragma once

#include <fstream>
#include <string>
#include <memory>

#include "ccWebServer/ccWebsocket.h"

class FileTransferSessionInfo {
public:
  FileTransferSessionInfo(std::shared_ptr<Luna::ccWebsocket> websocket);

public:
  bool parse_packet(const std::string& message);
  void close();

public:
  std::shared_ptr<Luna::ccWebsocket> websocket_;

  std::string filename_;
  std::streampos filesize_;

  std::fstream recv_file_;
};
