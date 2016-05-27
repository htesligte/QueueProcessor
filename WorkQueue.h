#ifndef WORKQUEUE_H
#define WORKQUEUE_H
class WorkerThread;
class WorkCommand;
#include <boost/thread/thread.hpp>
#include <string>
#include "WorkerThread.h"
#include "WorkCommand.h"
class WorkQueue
{
private:
  std::deque<WorkCommand*> work;
  boost::mutex* mutex;
public:
  WorkQueue(boost::mutex *mutex);
  void addWork(WorkCommand* work);
  void retrieveWork( WorkerThread* workerThread );
  ~WorkQueue();
};
#endif
