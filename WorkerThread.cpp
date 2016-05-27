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
  std::string command = wc->getSystemCommand();
  delete wc;
  system( command.c_str() );
}

std::string WorkerThread::getName()
{
  return "";
}
