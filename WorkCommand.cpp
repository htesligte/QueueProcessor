#include "WorkCommand.h"
WorkCommand::WorkCommand( boost::asio::io_service *ioservice) : socket(*ioservice) {}
WorkCommand::~WorkCommand()
{
  this->socket.shutdown(tcp::socket::shutdown_send);
}
tcp::socket* WorkCommand::getSocket()
{
  return &this->socket;
}
