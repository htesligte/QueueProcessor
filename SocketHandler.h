#ifndef SOCKETHANDLER_H
#define SOCKETHANDLER_H

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <list>
#include <string>
#include <ctime>
class WorkQueue;
#include "WorkQueue.h"
using namespace boost::asio;
using namespace boost::asio::ip;

class SocketHandler
{
private:
  io_service ioservice;
  tcp::endpoint tcp_endpoint{ tcp::v4(), 2486 };
  tcp::acceptor tcp_acceptor{ ioservice, tcp_endpoint };
  std::map<int, tcp::socket> tcp_sockets;
  void write(int, yield_context);
  void accept(yield_context);
  int socket_index;
  WorkQueue* workQueue;

public:
  SocketHandler(WorkQueue* workQueue);
  void run();
};
#endif
