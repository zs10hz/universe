#ifndef PACKET_TASK_PROCESS
#define PACKET_TASK_PROCESS

#include "packets.h"

class CPacket_task_process:
  public CPacket
{
public:
	CPacket_task_process(int taskid, int process);
	CPacket_task_process(const CPacket& packet);
	~CPacket_task_process();

int	GetTaskid();
int	GetProcess();
};

#endif
