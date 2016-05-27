#ifndef WORKCOMMAND_H
#define WORKCOMMAND_H
#include <boost/asio.hpp>
#include <array>

using namespace boost::asio::ip;

class WorkCommand {
private:
  tcp::socket socket;
  std::array<char, 4096> bufferData;
  boost::asio::mutable_buffers_1 buffer;
  void validateJSON();
  bool json_valid;
  std::string command;

public:
  WorkCommand( boost::asio::io_service* ioservice );
  ~WorkCommand();
  tcp::socket* getSocket();
  boost::asio::mutable_buffers_1* getBuffer();

  void processBuffer( size_t bytes );
  bool isCommandValid();
  std::string getSystemCommand();
};
#endif
