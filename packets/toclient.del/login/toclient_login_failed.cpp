#include "packets.h"

CToClient_login_failed::CToClient_login_failed():
  CPacket( COMMAND_GROUP_LOGIN, COMMAND_LOGIN_FAILED )
{
}

CToClient_login_failed::~CToClient_login_failed()
{
}
