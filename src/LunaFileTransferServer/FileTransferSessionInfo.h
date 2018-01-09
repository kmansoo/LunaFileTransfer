#pragma once

#include <string>

class FileTransferSessionInfo {
public:
  FileTransferSessionInfo();

public:
  std::shared_ptr<Luna::ccWebsocket> websocket_;
  std::string filename_;
};