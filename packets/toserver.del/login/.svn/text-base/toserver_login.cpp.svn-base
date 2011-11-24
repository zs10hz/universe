#include "packets.h"

CToServer_login::CToServer_login(const CHash& hash):
  CPacket( COMMAND_GROUP_LOGIN, COMMAND_LOGIN, hash.ToData() )
{
}

CToServer_login::CToServer_login(const CPacket& packet):
  CPacket( packet )
{
}

CToServer_login::~CToServer_login()
{
}

CHash CToServer_login::GetHash()
{
return CHash( GetData() );
}
