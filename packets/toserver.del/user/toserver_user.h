#ifndef TOSERVER_USERH
#define TOSERVER_USERH

#include "packets.h"

class CToServer_user:
  public CPacket
{
public:
        CToServer_user(const CUser& user);
	CToServer_user(const CPacket& packet);
	~CToServer_user();

CUser	GetUser();
};

#endif
