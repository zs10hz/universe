#ifndef TOCLIENT_USER_LISTH
#define TOCLIENT_USER_LISTH

#include "packets.h"

class CToClient_user_list:
  public CPacket
{
public:
             CToClient_user_list(const CArray<int>& list);
             CToClient_user_list(const CPacket& packet);
             ~CToClient_user_list();

virtual	int  Count();
virtual	int  operator [] (int index);
};

#endif
