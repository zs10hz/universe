#ifndef PACKET_TASK_QUERY
#define PACKET_TASK_QUERY

#include "packets.h"

class CPacket_task_query:
  public CPacket
{
public:
             CPacket_task_query(int taskid);
             CPacket_task_query(const CPacket& packet);
             ~CPacket_task_query();

virtual int  GetTaskid();
};

#endif
