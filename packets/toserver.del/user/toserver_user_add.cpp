#include "packets.h"

CToServer_user_add::CToServer_user_add(const CUser& user):
  CToServer_user( user )
{
SetCommand( COMMAND_USER_ADD );
}

CToServer_user_add::CToServer_user_add(const CPacket& packet):
  CToServer_user( packet )
{
}

CToServer_user_add::~CToServer_user_add()
{
}
