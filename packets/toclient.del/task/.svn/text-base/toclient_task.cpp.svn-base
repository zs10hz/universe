#include "packets.h"

CToClient_task::CToClient_task(CTask& task):
  CPacket( COMMAND_GROUP_TASK, COMMAND_TASK, task.ToData() )
{
}

CToClient_task::CToClient_task(const CPacket& packet):
  CPacket( packet )
{
}

CToClient_task::~CToClient_task()
{
}

CTask CToClient_task::GetTask()
{
return CTask( GetData() );
}
