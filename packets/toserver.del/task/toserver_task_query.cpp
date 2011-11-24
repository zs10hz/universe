#include "packets.h"

CPacket_task_query::CPacket_task_query(int taskid):
  CPacket( COMMAND_GROUP_TASK, COMMAND_TASK_QUERY, CData( &taskid, sizeof(taskid)) )
{	
}

CPacket_task_query::CPacket_task_query(const CPacket& packet):
  CPacket( packet )
{
}

CPacket_task_query::~CPacket_task_query()
{
}

int CPacket_task_query::GetTaskid()
{
return *((int*)GetData().GetData());
}
