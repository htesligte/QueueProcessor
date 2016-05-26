#include "SocketHandler.h"
#include "WorkCommand.h"
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <typeinfo>

SocketHandler::SocketHandler(WorkQueue* workQueue)
{
  this->workQueue = workQueue;
}

void SocketHandler::accept(yield_context yield)
{
  while( true )
  {
    WorkCommand* wc = new WorkCommand(&ioservice);
    tcp_acceptor.async_accept( (*wc->getSocket()), yield );
    spawn(ioservice, [&](yield_context yield) {
      this->read( wc );
    });
  }
}

void SocketHandler::read( WorkCommand* wc )
{
  wc->getSocket()->async_read_some( (*wc->getBuffer()), [=]( const boost::system::error_code& ec, std::size_t bytes_transferred ) {
    if( bytes_transferred == 0 && ec.value() == boost::asio::error::eof )
    {
      delete wc;
      return;
    }
      
    wc->processBuffer( bytes_transferred );
    this->read( wc );
  });
}

void SocketHandler::write( WorkCommand* wc, yield_context yield )
{
  std::time_t now = std::time(nullptr);
  std::string data = std::ctime(&now);
  async_write( (*wc->getSocket()), buffer(data), yield );

  delete wc;
}

void SocketHandler::run()
{
  tcp_acceptor.listen();
  spawn( ioservice, boost::bind(&SocketHandler::accept, this, _1) );
  ioservice.run();
}