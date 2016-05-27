#include "WorkerThread.h"
#include <boost/random.hpp>
WorkerThread::WorkerThread(WorkQueue* workQueue )
{
  this->workQueue = workQueue;
}
void WorkerThread::findWork()
{
  while( true )
  {
    workQueue->retrieveWork( this );
    boost::this_thread::sleep( boost::posix_time::milliseconds(getRandom()) );
  }

}

int WorkerThread::getRandom()
{
  std::time_t now = std::time(0);
  boost::random::mt19937 gen{static_cast<std::uint32_t>(now)};
  boost::random::uniform_int_distribution<> dist{1, 1000};
  return dist(gen);
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
