#include "packets.h"

CToServer_user::CToServer_user(const CUser& user):
  CPacket( COMMAND_GROUP_USER, COMMAND_USER, user.ToData() )
{
}

CToServer_user::CToServer_user(const CPacket& packet):
  CPacket( packet )
{
}

CToServer_user::~CToServer_user()
{
}

CUser CToServer_user::GetUser()
{
return CUser( GetData() );
}
