#include "WorkerThread.h"
WorkerThread::WorkerThread(WorkQueue* workQueue )
{
  this->workQueue = workQueue;
  //this->ThreadName = ThreadName;
}
void WorkerThread::findWork()
{
  while( true )
  {
    workQueue->retrieveWork( this );
    //boost::this_thread::sleep_for(boost::chrono::seconds(1));
  }
}
void WorkerThread::doWork( std::string WorkCommand )
{
  std::cout << "" <<  ": Received command " << WorkCommand << " ! " << std::endl;
}

std::string WorkerThread::getName()
{
  return ""; // this->ThreadName;
}
