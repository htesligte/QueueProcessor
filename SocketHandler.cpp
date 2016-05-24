#include "SocketHandler.h"
#include "WorkCommand.h"
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
  while( true )
  {
    WorkCommand* wc = new WorkCommand(&ioservice);
    tcp_acceptor.async_accept( (*wc->getSocket()), yield );
    spawn(ioservice, [&](yield_context yield) {

      // do work
      std::cout << "Should be adding work..." << std::endl;
      workQueue->addWork("hello world!");

      this->write(wc, yield);
    });
  }
}

//void SocketHandler::read( int pos, yield_context yield )
//{ 
  //tcp_sockets.at(pos)->async_read_some()
//}

void SocketHandler::write( WorkCommand* wc, yield_context yield )
{
  std::time_t now = std::time(nullptr);
  std::string data = std::ctime(&now);
  async_write( (*wc->getSocket()), buffer(data), yield );

  delete wc;
  //tcp_sockets.erase(pos);
}

void SocketHandler::run()
{
  tcp_acceptor.listen();
  spawn( ioservice, boost::bind(&SocketHandler::accept, this, _1) );
  ioservice.run();
}
