#include "SocketHandler.h"
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

SocketHandler::SocketHandler(WorkQueue* workQueue)
{
  this->workQueue = workQueue;
  // tcp_endpoint = tcp::endpoint( tcp::v4(), port );
  // tcp_acceptor = tcp::acceptor( ioservice, tcp_endpoint );

}

void SocketHandler::accept(yield_context yield)
{
  socket_index = 0;
  while( true )
  {
    socket_index++;
    tcp_sockets.emplace(socket_index, tcp::socket(ioservice) );
    tcp_acceptor.async_accept( tcp_sockets.at(socket_index), yield );
    spawn(ioservice, [&](yield_context yield) {

      // do work
      std::cout << "Should be adding work..." << std::endl;
      workQueue->addWork("hello world!");

      this->write(this->socket_index, yield);
    });
  }
}

void SocketHandler::write( int pos, yield_context yield )
{
  std::time_t now = std::time(nullptr);
  std::string data = std::ctime(&now);
  async_write( tcp_sockets.at(pos), buffer(data), yield );
  tcp_sockets.at(pos).shutdown(tcp::socket::shutdown_send);
  tcp_sockets.erase(pos);
}

void SocketHandler::run()
{
  tcp_acceptor.listen();
  spawn( ioservice, boost::bind(&SocketHandler::accept, this, _1) );
  ioservice.run();
}
