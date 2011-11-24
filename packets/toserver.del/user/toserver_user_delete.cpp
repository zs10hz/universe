#include "packets.h"

CToServer_user_delete::CToServer_user_delete(int userid):
  CPacket( COMMAND_GROUP_USER, COMMAND_USER_DELETE, CData( &userid, sizeof(userid) ) )
{
}

CToServer_user_delete::CToServer_user_delete(const CPacket& packet):
  CPacket( packet )
{
}

CToServer_user_delete::~CToServer_user_delete()
{
}

int CToServer_user_delete::GetUserid()
{
return *((int*)GetData().GetData());
}
