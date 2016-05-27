#include "WorkerThread.h"
WorkerThread::WorkerThread(WorkQueue* workQueue )
{
  this->workQueue = workQueue;
}
void WorkerThread::findWork()
{
  while( true )
    workQueue->retrieveWork( this );
}
void WorkerThread::doWork( WorkCommand* wc )
{
  system( wc->getSystemCommand().c_str() );
  delete wc;
}

std::string WorkerThread::getName()
{
  return "";
}
