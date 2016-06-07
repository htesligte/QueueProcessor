#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include "WorkCommand.h"
class WorkerThread
{
public:
  void doWork( WorkCommand* wc );
};
#endif
