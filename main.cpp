#include "WorkQueue.h"
#include "WorkerThread.h"
#include "SocketHandler.h"

void startSocketHandler(WorkQueue* workQueue)
{
  SocketHandler sh(workQueue);
  sh.run();
}
int main()
{
  WorkQueue workQueue;

  // start socketThread which hands work out to the workQueue.
  boost::thread socketThread{startSocketHandler, &workQueue};

  // hang main thread
  while(true) {
    boost::this_thread::sleep_for(boost::chrono::minutes(60));
  }



  return 0;
}
