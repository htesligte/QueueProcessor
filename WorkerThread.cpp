#include "WorkerThread.h"
#include <boost/random.hpp>

void WorkerThread::doWork( WorkCommand* wc )
{
  std::string command = wc->getSystemCommand();
  std::cout << "Doing work: " << command << std::endl;
  system( command.c_str() );
}
