#ifndef WORKCOMMAND_H
#define WORKCOMMAND_H
#include <boost/asio.hpp>
#include <array>

using namespace boost::asio::ip;

class WorkCommand {
private:
  tcp::socket socket;
  std::array<char, 4096> bufferData;
  //std::string buffer;
  boost::asio::mutable_buffers_1 buffer;

public:
  WorkCommand( boost::asio::io_service* ioservice );
  ~WorkCommand();
  tcp::socket* getSocket();
  boost::asio::mutable_buffers_1* getBuffer();

  size_t getBufferSize();
  void debug();
  void processBuffer( size_t bytes );
  std::string command;
};
#endif
