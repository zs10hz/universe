#ifndef TOSERVER_LOGINH
#define TOSERVER_LOGINH

#include "packets.h"

class CToServer_login:
  public CPacket
{
public:
       CToServer_login(const CHash& hash);
       CToServer_login(const CPacket& packet);
       ~CToServer_login();

CHash  GetHash();
};

#endif
