#ifndef TOSERVER_USER_DELETE
#define TOSERVER_USER_DELETE

#include "packets.h"

class CToServer_user_delete:
  public CPacket
{
public:
	CToServer_user_delete(int userid);
	CToServer_user_delete(const CPacket& packet);
	~CToServer_user_delete();

int	GetUserid();
};

#endif
