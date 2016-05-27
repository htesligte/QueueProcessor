#include "WorkQueue.h"
WorkQueue::WorkQueue(boost::mutex *mutex)
{
  this->mutex = mutex;
}

WorkQueue::~WorkQueue()
{
}

void WorkQueue::addWork(WorkCommand* wc)
{
  this->mutex->lock();
  work.push_back(wc);
  this->mutex->unlock();
}

void WorkQueue::retrieveWork( WorkerThread* workerThread )
{
  WorkCommand* wc;
  bool hasWork = false;

  this->mutex->lock();
  if( work.size() > 0 )
  {
    hasWork = true;
    wc = work.front();
    work.pop_front();
  }
  this->mutex->unlock();

  if( hasWork )
    workerThread->doWork( wc );
}
