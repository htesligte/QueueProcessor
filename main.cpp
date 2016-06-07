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
  boost::mutex *mutex = new boost::mutex();
  // Create WorkQueue
  WorkQueue workQueue(mutex);

  // socketThread
  boost::thread socketThread{startSocketHandler, &workQueue};

  // thread pool for work - yeah I know I should have used boosts' threadpool :-(
  for( int i = 0; i < 10; i++ )
  {
    WorkerThread *workerThread = new WorkerThread( &workQueue );
    new boost::thread( &WorkerThread::findWork, workerThread );
  }

  // hang main thread
  while(true) {
    boost::this_thread::sleep_for(boost::chrono::minutes(60));
  }



  return 0;
}
