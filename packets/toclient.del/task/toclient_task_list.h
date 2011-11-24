#ifndef TOCLIENT_TASK_LISTH
#define TOCLIENT_TASK_LISTH

#include "packets.h"

class CToClient_task_list:
public CPacket
{
protected:
public:
      CToClient_task_list(const CArray<CTask>& list);
      CToClient_task_list(const CPacket& packet);
      ~CToClient_task_list();

int   GetCount();
CTask GetTask(int Index);
};

#endif
