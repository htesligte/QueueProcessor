#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
class WorkQueue;
#include "WorkQueue.h"
#include <string>
class WorkerThread
{
public:
  WorkerThread( WorkQueue* workQueue );
  void findWork();
  void doWork( std::string WorkCommand );
  std::string getName();
private:
  WorkQueue* workQueue;
//  std::string ThreadName;
};
#endif
