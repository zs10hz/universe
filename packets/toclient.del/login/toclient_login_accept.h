#ifndef TOCLIENT_LOGIN_ACCEPTH
#define TOCLIENT_LOGIN_ACCEPTH

#include "packets.h"
#include "common_user.h"

class CToClient_login_accept:
  public CPacket
{
public:
        CToClient_login_accept(const CUser& user);
        CToClient_login_accept(const CPacket& packet);
        ~CToClient_login_accept();

CUser   GetUser();
};

#endif
