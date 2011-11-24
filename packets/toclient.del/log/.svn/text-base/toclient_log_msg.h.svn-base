#ifndef TOCLIENT_LOG_MSGH
#define	TOCLIENT_LOG_MSGH

#include "packets.h"
#include "common_log_msg.h"

class CToClient_log_msg:
  public CPacket
{
public:
          CToClient_log_msg(const CLog_msg& msg);
          CToClient_log_msg(const CPacket& packet);
          ~CToClient_log_msg();

CLog_msg  GetMsg();
};

#endif
