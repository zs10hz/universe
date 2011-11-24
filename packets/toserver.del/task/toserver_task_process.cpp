#include "packets.h"

struct s_packet_task_process
{
int	m_taskid;
int	m_process;
};

CPacket_task_process::CPacket_task_process(int taskid, int process):
	CPacket( COMMAND_GROUP_TASK, COMMAND_TASK_PROCESS )
{
s_packet_task_process data;
data.m_taskid = taskid;
data.m_process = process;
SetData( CData( &data, sizeof(data) ) );
}

CPacket_task_process::CPacket_task_process(const CPacket& packet):
  CPacket( packet )
{
}

CPacket_task_process::~CPacket_task_process()
{
}

int CPacket_task_process::GetTaskid()
{
s_packet_task_process* data = (s_packet_task_process*)GetData().GetData();
return data->m_taskid;
}

int CPacket_task_process::GetProcess()
{
s_packet_task_process* data = (s_packet_task_process*)GetData().GetData();
return data->m_process;
}
