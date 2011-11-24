#ifndef TOSERVER_USER_ADDH
#define TOSERVER_USER_ADDH

#include "packets.h"

class CToServer_user_add:
  public CToServer_user
{
public:
	CToServer_user_add(const CUser& user);
	CToServer_user_add(const CPacket& packet);
	~CToServer_user_add();
};

#endif
