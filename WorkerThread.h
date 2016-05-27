#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
class WorkQueue;
#include "WorkQueue.h"
#include <string>
#include "WorkCommand.h"
class WorkerThread
{
public:
  WorkerThread( WorkQueue* workQueue );
  void findWork();
  void doWork( WorkCommand* wc );
  std::string getName();
  int getRandom();
private:
  WorkQueue* workQueue;
};
#endif
