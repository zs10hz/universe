#include "packets.h"

CToClient_user::CToClient_user(const CUser& user):
  CPacket( COMMAND_GROUP_USER, COMMAND_USER, user.ToData() )
{
}

CToClient_user::CToClient_user(const CPacket& packet):
  CPacket( packet )
{
}

CToClient_user::~CToClient_user()
{
}

CUser CToClient_user::GetUser()
{
return CUser( GetData() );
}
