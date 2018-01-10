
#include <memory>
#include <iostream>

#include "ccCore/ccCoreAPI.h"

#include "ccNetwork/ccNetworkManager.h"

#include "FileReceivingClient.h"
#include "FileSendingClient.h"

int main(int argc, char *argv[]) {

  Luna::ccNetworkManager::instance().init();

  if (argc < 3) {
    std::cout << "Usage:" << std::endl;
    std::cout << "   LunaFileTransfer [ip] [path]" << std::endl << std::endl;

    return -1;
  }

  FileSendingClient fsc;

  std::string url = "ws://";
  url += argv[1];
  url += ":9097/ws_filereceiver";

  fsc.send(url, argv[2]);

  return 0;
}
