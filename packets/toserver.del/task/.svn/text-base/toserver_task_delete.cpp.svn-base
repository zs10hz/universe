#include "packets.h"

CPacket_task_delete::CPacket_task_delete(int taskid):
  CPacket( COMMAND_GROUP_TASK, COMMAND_TASK_DELETE, CData( &taskid, sizeof(taskid) ) )
{
}

CPacket_task_delete::CPacket_task_delete(const CPacket& packet):
  CPacket( packet )
{
}

CPacket_task_delete::~CPacket_task_delete()
{
}

int CPacket_task_delete::GetTaskid()
{
return *((int*)GetData().GetData());
}
