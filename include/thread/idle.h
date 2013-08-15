#include "thread/thread.h"

class IdleThread : public Thread {
  void action() 
  {
    while(1);
  }
};
