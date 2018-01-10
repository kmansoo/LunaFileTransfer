
#include <sys/stat.h>

#include "json/reader.h"
#include "json/value.h"

#include "ccCore/ccString.h"

#include "FileTransferSessionInfo.h"

FileTransferSessionInfo::FileTransferSessionInfo(
    std::shared_ptr<Luna::ccWebsocket> websocket)
    : websocket_(websocket) {}

void FileTransferSessionInfo::close() {
  recv_file_.close();
}

bool FileTransferSessionInfo::parse_packet(const std::string &message) {
  Json::Reader json_reader;
  Json::Value protocol_json;

  if (!json_reader.parse(message, protocol_json))
    return false;

  if (protocol_json.isObject() == false)
    return false;

  if (protocol_json["type"].isNull())
    return false;

  if (protocol_json["type"].asString() == "fileinfo") {
    Json::Value fileinfo = protocol_json["info"];

    std::string peer_ip = websocket_->get_peer_ip();

    if (peer_ip.size() == 0)
      peer_ip = "recv_files";
    
    filename_ =  "./" + peer_ip + "/" + fileinfo["name"].asString();
    filesize_ = fileinfo["size"].asUInt();

    if (filename_.size() == 0)
      return false;

#if defined(_WIN32)
    _mkdir(peer_ip.c_str());
#else 
    mkdir(peer_ip.c_str(), 0777); // notice that 777 is different than 0777
#endif

    recv_file_.open(filename_, std::ios::out | std::ios::binary);
  } else {
    if (protocol_json["type"].asString() == "data") {

      if (recv_file_.is_open()) {
        std::string converted_data;

        Luna::ccString::decode_base64(converted_data,
                                      protocol_json["chunk"].asString());

        recv_file_.write(converted_data.data(), converted_data.size());
      }
    } else {
      if (protocol_json["type"].asString() == "completed") {
        recv_file_.close();
      }
    }
  }

  return true;
}
