#include "packets.h"

struct s_toclient_user_list
{
int m_count;
int m_data[1];
};

CToClient_user_list::CToClient_user_list(const CArray<int>& list):
  CPacket( COMMAND_GROUP_USER, COMMAND_USER_LIST )
{
int count = list.GetCount();
size_t datasize = sizeof(s_toclient_user_list) + sizeof(int) * (count-1);

char* data = new char[ datasize ];
s_toclient_user_list* packet = (s_toclient_user_list*)data;
packet->m_count = count;
for (int pos = 0; pos < count; ++pos)
  packet->m_data[ pos ] = list[ pos ];

SetData( CData( data, datasize ) );
delete []data;
}

CToClient_user_list::CToClient_user_list(const CPacket& packet):
  CPacket( packet )
{
}

CToClient_user_list::~CToClient_user_list()
{
}

int CToClient_user_list::Count()
{
s_toclient_user_list* data = (s_toclient_user_list*)GetData().GetData();
return data->m_count;
}

int CToClient_user_list::operator [] (int index)
{
s_toclient_user_list* data = (s_toclient_user_list*)GetData().GetData();
if ( index >= 0 && index < Count() )
  return (data->m_data)[ index ];

return -1;
}
