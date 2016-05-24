#ifndef WORKCOMMAND_H
#define WORKCOMMAND_H
#include <boost/asio.hpp>
#include <array>

using namespace boost::asio::ip;

class WorkCommand {
private:
  tcp::socket socket;
  std::array<char, 4096> buffer;
  std::string command;
public:
  WorkCommand( boost::asio::io_service* ioservice );
  ~WorkCommand();
  tcp::socket* getSocket();
};
#endif
