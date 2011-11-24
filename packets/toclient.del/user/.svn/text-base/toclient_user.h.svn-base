#ifndef TOCLIENT_USERH
#define TOCLIENT_USERH

#include "packets.h"

class CToClient_user:
  public CPacket
{
public:
        CToClient_user(const CUser& user);
        CToClient_user(const CPacket& packet);
        ~CToClient_user();

CUser   GetUser();
};

#endif
