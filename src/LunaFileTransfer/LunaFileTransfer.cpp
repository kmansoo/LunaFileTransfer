
#include <memory>

#include "ccCore/ccCoreAPI.h"

#include "ccNetwork/ccNetworkManager.h"

#include "FileReceivingClient.h"
#include "FileSendingClient.h"

int main(int argc, char *argv[]) {

  Luna::ccNetworkManager::instance().init();

  FileSendingClient fsc;

  fsc.send("ws://localhost:9097/ws_filereceiver", "CMakeLists.txt");
}
