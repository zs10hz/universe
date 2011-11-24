#ifndef PACKET_TASKH
#define PACKET_TASKH

#include "packets.h"

class CPacket_task:
  public CPacket
{
public:
       CPacket_task(const CTask& task);
       CPacket_task(const CPacket& packet);
       ~CPacket_task();

CTask  GetTask();
};

#endif
