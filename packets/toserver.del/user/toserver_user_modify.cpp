#include "packets.h"

CToServer_user_modify::CToServer_user_modify(const CUser& user):
  CToServer_user( user )
{
SetCommand( COMMAND_USER_MODIFY );
}

CToServer_user_modify::CToServer_user_modify(CPacket packet):
  CToServer_user( packet )
{
}

CToServer_user_modify::~CToServer_user_modify()
{
}
