#include "WorkQueue.h"
WorkQueue::WorkQueue(boost::mutex *mutex)
{
  this->mutex = mutex;
}

WorkQueue::~WorkQueue()
{
  std::cout << "i am destroyed";
}

void WorkQueue::addWork(std::string WorkCommand)
{
  std::cout << "Adding work..." << std::endl;
  this->mutex->lock();
  std::cout << "Passed lock..." << std::endl;
  work.push_back(WorkCommand);
  this->mutex->unlock();
}

void WorkQueue::retrieveWork( WorkerThread* workerThread )
{
  std::string WorkCommand = "";
  bool hasWork = false;

  this->mutex->lock();
  if( work.size() > 0 )
  {
    std::cout << "Work size is > 0 " << std::endl;
    hasWork = true;
    WorkCommand = work.front();
    work.pop_front();
  }
  this->mutex->unlock();

  if( hasWork )
  {
    std::cout << "hasWork is true..." << std::endl;
    workerThread->doWork( WorkCommand );
  }
}
