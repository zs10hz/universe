#include "packets.h"

CPacket_task::CPacket_task(const CTask& task):
  CPacket( COMMAND_GROUP_TASK, COMMAND_TASK, task.ToData() )
{
}

CPacket_task::CPacket_task(const CPacket& packet):
  CPacket( packet )
{
}

CPacket_task::~CPacket_task()
{
}

CTask CPacket_task::GetTask()
{
return CTask( GetData() );
}
