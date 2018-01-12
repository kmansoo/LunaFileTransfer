
#include <iostream>
#include <fstream>

#include "ccCore/ccCoreAPI.h"
#include "ccCore/ccString.h"

#include "json/reader.h"
#include "json/value.h"
#include "json/writer.h"

#include "FileSendingClient.h"

#include "ccWebsocketClient/ccEasyWebsocketClient.h"

FileSendingClient::FileSendingClient() : is_ws_closed_(true) {
  ws_client_ = std::make_shared<Luna::ccEasyWebsocketClient>();

  ws_client_->set_event_listener(
      std::bind(&FileSendingClient::recv_data_from_websocket, this,
                std::placeholders::_1, std::placeholders::_2));
}

std::string get_file_name(const std::string& src) {
   char sep = '/';

#ifdef _WIN32
   sep = '\\';
#endif

   size_t pos = src.rfind(sep, src.length());

   if (pos != std::string::npos)
      return(src.substr(pos + 1, src.length() - pos));

   return src;
}

bool FileSendingClient::send(const std::string &url,
                             const std::string &filename) {

  std::streampos filesize;
  std::ifstream myfile (filename, std::ios::binary);

  if (!myfile.is_open()) {
      std::cout << "I couldn't open '" << filename << "'. Check please!" << std::endl;
      return false;
  }

  myfile.seekg (0, std::ios::end);
  filesize = myfile.tellg();
  myfile.seekg (0, std::ios::beg);

  Json::Value protocol_json;
  Json::StyledWriter json_writer;

  if (ws_client_->open(url) == true) {
    is_ws_closed_ = false;

    {
      protocol_json.clear();
      Json::Value info_json;

      protocol_json["type"] = "fileinfo";

      info_json["name"] = get_file_name(filename);
      info_json["size"] = (unsigned int)filesize;

      protocol_json["info"] = info_json;

	  ws_client_->send(json_writer.write(protocol_json));
    }

    char buffer[3100];
    std::streamsize sent_bytes = 0;
    int back_space_count = 10;

    while (!myfile.eof() && is_ws_closed_ == false) {
        size_t size = 3072;

        myfile.read(buffer, size);    
        std::streamsize read_bytes = myfile.gcount();

        // std::cout << "[FileSendingClient], read_bytes = " << read_bytes << std::endl;

        // make protocol to send to server
        std::string encoded_data;

        protocol_json.clear();
        
        protocol_json["type"] = "data";

        Luna::ccString::encode_base64(encoded_data, buffer, read_bytes);

        protocol_json["chunk"] = encoded_data;

		    ws_client_->send(json_writer.write(protocol_json));

        sent_bytes += read_bytes;

        for (int count = 0; count < back_space_count; count++)
          std::cout << "\b";

        Luna::ccString output_msg;

        Luna::ccString::format(output_msg, "%ld / %ld(%4.2f%%)", sent_bytes, filesize, (float)sent_bytes / (float)filesize * 100.0f);

        back_space_count = output_msg.length() + 5;

        std::cout << output_msg;
        
        Luna::sleep(3);
    }

    protocol_json.clear();
    protocol_json["type"] = "completed";
	ws_client_->send(json_writer.write(protocol_json));
  }

  ws_client_->close();

  return false;
}

void FileSendingClient::recv_data_from_websocket(
    Luna::ccWebsocket::ccWebSocketEvent ws_event, const std::string &message) {

  switch ((int)ws_event) {
  case Luna::ccWebsocket::ccWebSocketEvent_Connected: {
      std::cout << "[FileSendingClient], ccWebSocketEvent_Connected." << std::endl;
  } break;

  case Luna::ccWebsocket::ccWebSocketEvent_Disconnected: {
    std::cout << "[FileSendingClient], Disconnected." << std::endl;
    is_ws_closed_ = true;
  } break;

  case Luna::ccWebsocket::ccWebSocketEvent_ReceivedData: {
    std::cout << "[FileSendingClient], ReceivedData, " << message << std::endl;
  } break;
  }
}
