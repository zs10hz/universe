#ifndef TOCLIENT_TASKH
#define TOCLIENT_TASKH

#include "packets.h"

class CToClient_task:
  public CPacket
{
public:
       CToClient_task(CTask& task);
       CToClient_task(const CPacket& packet);
       ~CToClient_task();

CTask  GetTask();
};

#endif
