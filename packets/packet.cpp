#include "packet.h"
#include <string.h>
#include "common_command.h"

CPacket::CPacket()
{
Init();
}

CPacket::CPacket(const CPacket& r_value):
  m_data(r_value.m_data)
{
m_version = r_value.m_version;
m_command_group = r_value.m_command_group;
m_command = r_value.m_command;
}

CPacket::CPacket(int command_group, int command)
{
Init( command_group, command );
}

CPacket::CPacket(const int command_group, const int command, const CData& data):
  m_data( data )
{
m_version = PACKET_VERSION;
m_command_group = command_group;
m_command = command;
}

CPacket::CPacket(s_packet* packet):
  m_data( packet->m_data, packet->m_datasize )
{
m_version = packet->m_version;
m_command_group = packet->m_command_group;
m_command = packet->m_command;
}

CPacket::~CPacket()
{
Clear();
}

void CPacket::Init()
{
m_version = PACKET_VERSION;
m_command_group = COMMAND_GROUP_UNKNOWN;
m_command = COMMAND_UNKNOWN;
m_data.Clear();
}

void CPacket::Init(int command_group, int command)
{
Init();
m_command_group = command_group;
m_command = command;
}

void CPacket::Clear()
{
m_data.Clear();
Init();
}

CPacket& CPacket::operator = (const CPacket& r_value)
{
m_version = r_value.m_version;
m_command_group = r_value.m_command_group;
m_command = r_value.m_command;
m_data = r_value.m_data;

return *this;
}

int CPacket::GetVersion() const
{
return m_version;
}

size_t CPacket::GetPacketSize() const
{
return m_data.GetSize() + sizeof( s_packet );
}

void CPacket::SetCommandGroup(int command_group)
{
m_command_group = command_group;
}

void CPacket::SetCommand(int command)
{
m_command = command;
}

int CPacket::GetCommandGroup() const
{
return m_command_group;
}

int CPacket::GetCommand() const
{
return m_command;
}

bool CPacket::Send(SOCKET sock)
{
s_packet* packet = (s_packet*) new char[ GetPacketSize() ];

packet->m_version = m_version;
packet->m_command_group = m_command_group;
packet->m_command = m_command;
packet->m_datasize = m_data.GetSize();
memcpy( packet->m_data, m_data.GetData(), m_data.GetSize() );

bool result = (send( sock, (char*)packet, (int)GetPacketSize(), 0 ) == (int)GetPacketSize());

delete []packet;
return result;
}

void CPacket::SetData(const CData& data)
{
m_data = data;
}

CData CPacket::GetData() const
{
return m_data;
}

CPacket CPacket::ToPacket()
{
return *this;
}
