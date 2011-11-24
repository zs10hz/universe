#ifndef PACKETH
#define PACKETH

#include "common_sock.h"
#include "common_data.h"

#define PACKET_VERSION 2

struct s_packet
{
int     m_version;
int     m_command_group;
int     m_command;
size_t  m_datasize;
char    m_data[1];
};

class CPacket
{
private:
int     m_version;
int     m_command_group;
int	    m_command;
CData   m_data;

void	  Init();
void	  Init(int command_group, int command);
void	  Clear();

protected:
CData	  GetData() const;
void	  SetData(const CData& data);

public:
	      CPacket();
	      CPacket(const int command_group, const int command);
        CPacket(const int command_group, const int command, const CData& data);
	      CPacket(const CPacket& r_value);
	      CPacket(s_packet* packet);
virtual ~CPacket();

CPacket&  operator = (const CPacket& packet);

int     GetVersion() const;
size_t  GetPacketSize() const;

void    SetCommandGroup(const int command_group);
void    SetCommand(const int command);

int	    GetCommandGroup() const;
int	    GetCommand() const;

bool	  Send(const SOCKET sock);

CPacket ToPacket();
};

#endif
