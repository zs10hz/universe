#include "packets.h"

typedef unsigned int uint;

#define SUBJECT_SIZE 50

//TODO: Fix class on CData

struct s_task
{
int   m_taskid;
int   m_userid;
uint  m_attr;
int   m_priority;
int   m_process;
int   m_starttime;
int   m_deadline;
char  m_subject[SUBJECT_SIZE];
};

struct s_packet_task_list
{
int     m_count;
s_task  m_data[1];
};

CToClient_task_list::CToClient_task_list(const CArray<CTask>& list):
  CPacket( COMMAND_GROUP_TASK, COMMAND_TASK_LIST )
{
int count = list.GetCount();
size_t datasize = sizeof(s_packet_task_list) + sizeof(s_task)*(count-1);

char* data = new char[ datasize ];
s_packet_task_list* packet = (s_packet_task_list*)data;

packet->m_count = count;
for (int pos = 0; pos < count; ++pos)
  {
  s_task* ptask = packet->m_data + pos;
  CTask task = list[ pos ];
  ptask->m_taskid = task.GetTaskid();
  ptask->m_userid = task.GetUserid();
  ptask->m_attr = task.GetAttr();
  ptask->m_priority = task.GetPriority();
  ptask->m_process = task.GetProcess();
  ptask->m_starttime = task.GetStartTime();
  ptask->m_deadline = task.GetDeadLine();
  strcpy( ptask->m_subject, task.GetSubject().c_str() );
  }

SetData( CData( data , datasize ) );

delete []data;
}

CToClient_task_list::CToClient_task_list(const CPacket& packet):
  CPacket( packet )
{
}

CToClient_task_list::~CToClient_task_list()
{
}

int CToClient_task_list::GetCount()
{
s_packet_task_list* data = (s_packet_task_list*)GetData().GetData();
return data->m_count;
}

CTask CToClient_task_list::GetTask(int Index)
{
if ( Index > GetCount() || Index < 0) 
  throw;

CTask task;
s_packet_task_list* data = (s_packet_task_list*)GetData().GetData();
s_task* ptask = data->m_data + Index;
task.SetTaskid( ptask->m_taskid );
task.SetUserid( ptask->m_userid );
task.SetAttr( ptask->m_attr );
task.SetStartTime( ptask->m_starttime );
task.SetDeadLine( ptask->m_deadline );
task.SetSubject( ptask->m_subject );
return task;
}
