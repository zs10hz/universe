#include "packets.h"

CToClient_login_accept::CToClient_login_accept(const CUser& user):
  CPacket( COMMAND_GROUP_LOGIN, COMMAND_LOGIN_ACCEPT, user.ToData() )
{
}

CToClient_login_accept::CToClient_login_accept(const CPacket& packet):
  CPacket( packet )
{
}

CToClient_login_accept::~CToClient_login_accept()
{
}

CUser CToClient_login_accept::GetUser()
{
return CUser( GetData() );
}
