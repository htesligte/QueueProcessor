#include "SocketHandler.h"
#include "WorkCommand.h"
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

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
    if( wc->isCommandValid() )
    {
      this->workQueue->addWork(wc);
      return;
    }
    
    this->read( wc );
  });
}

void SocketHandler::run()
{
  tcp_acceptor.listen();
  spawn( ioservice, boost::bind(&SocketHandler::accept, this, _1) );
  ioservice.run();
}