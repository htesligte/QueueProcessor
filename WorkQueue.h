#ifndef WORKQUEUE_H
#define WORKQUEUE_H
#include <boost/asio/io_service.hpp>
#include <boost/thread/thread.hpp>
#include <string>
#include "WorkerThread.h"
#include "WorkCommand.h"
class WorkerThread;
class WorkCommand;

class WorkQueue
{
private:
  boost::asio::io_service ioService;
  boost::asio::io_service::work bWork;
  boost::thread_group threads;
public:
  WorkQueue();
  ~WorkQueue();
  void addWork(WorkCommand* work);
};
#endif
