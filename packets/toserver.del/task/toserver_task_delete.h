#ifndef PACKET_TASK_DELETEH
#define PACKET_TASK_DELETEH

#include "packets.h"

class CPacket_task_delete:
  public CPacket
{
public:
            CPacket_task_delete(int taskid);
	    CPacket_task_delete(const CPacket& packet);
	    ~CPacket_task_delete();

virtual int GetTaskid();
};

#endif
