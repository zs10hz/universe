#ifndef TOSERVER_USER_MODIFYH
#define TOSERVER_USER_MODIFYH

#include "packets.h"

class CToServer_user_modify:
  public CToServer_user
{
public:
	CToServer_user_modify(const CUser& user);
	CToServer_user_modify(CPacket packet);
	~CToServer_user_modify();
};

#endif
