#include "packets.h"

CToServer_user_query::CToServer_user_query(int userid):
  CPacket( COMMAND_GROUP_USER, COMMAND_USER_QUERY, CData( &userid, sizeof(userid) ) )
{
}

CToServer_user_query::CToServer_user_query(const CPacket& packet):
  CPacket( packet )
{
}

CToServer_user_query::~CToServer_user_query()
{
}

int CToServer_user_query::GetUserid()
{
return *((int*)GetData().GetData());
}
