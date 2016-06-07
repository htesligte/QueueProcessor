#include "WorkQueue.h"
#include "WorkerThread.h"
WorkQueue::WorkQueue() : bWork(ioService)
{
  for( int i = 0; i < 10; i++ )
    this->threads.create_thread( boost::bind( &boost::asio::io_service::run, &ioService ) );
}

WorkQueue::~WorkQueue()
{
  ioService.stop();
  threads.join_all();
}

void WorkQueue::addWork(WorkCommand* wc)
{
  ioService.post([=]() {
    WorkerThread thread;
    thread.doWork(wc);
    delete wc;
  });
}
