#ifndef WORKQUEUE_H
#define WORKQUEUE_H
class WorkerThread;
#include <boost/thread/thread.hpp>
#include <string>
#include "WorkerThread.h"
class WorkQueue
{
private:
  std::deque<std::string> work;
  boost::mutex* mutex;
public:
  WorkQueue(boost::mutex *mutex);
  void addWork(std::string workCommand);
  void retrieveWork( WorkerThread* workerThread );
  ~WorkQueue();
};
#endif
