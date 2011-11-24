#include "packets.h"

CToClient_log_msg::CToClient_log_msg(const CLog_msg& msg):
  CPacket( COMMAND_GROUP_LOG, COMMAND_LOG_MSG, msg.ToData() ) 
{
}

CToClient_log_msg::CToClient_log_msg(const CPacket& packet):
  CPacket( packet )
{ 
}

CToClient_log_msg::~CToClient_log_msg()
{  
}

CLog_msg CToClient_log_msg::GetMsg()
{
return CLog_msg( GetData() );
}
