#include "pch.h"
#include "ServerPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"
#include "ObjectUtils.h"
#include "Room.h"
#include "GameSession.h"
#include "Player.h"

/*
XCOPY /Y Enum.pb.h "../../../../Client/Client/Network"
XCOPY /Y Enum.pb.cc "../../../../Client/Client/Network"
XCOPY /Y Struct.pb.h "../../../../Client/Client/Network"
XCOPY /Y Struct.pb.cc "../../../../Client/Client/Network"
XCOPY /Y Protocol.pb.h "../../../../Client/Client/Network"
XCOPY /Y Protocol.pb.cc "../../../../Client/Client/Network"
XCOPY /Y ClientPacketHandler.h "../../../../Client/Client/Network"
*/

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO : Log
	return false;
}

bool Handle_C_LOGIN(PacketSessionRef& session, Protocol::C_LOGIN& pkt)
{
	// TODO : DB에서 Account 정보를 긁어온다
	// TODO : DB에서 유저 정보 긁어온다
	Protocol::S_LOGIN loginPkt;

	for (int32 i = 0; i < 3; i++)
	{
		Protocol::ObjectInfo* player = loginPkt.add_players();
		Protocol::PosInfo* posInfo = player->mutable_pos_info();

		posInfo->set_x(Utils::GetRandom(0.f, 100.f));
		posInfo->set_y(Utils::GetRandom(0.f, 100.f));
		posInfo->set_z(Utils::GetRandom(0.f, 100.f));
		posInfo->set_yaw(Utils::GetRandom(0.f, 45.f));
	}

	loginPkt.set_success(true);
	SEND_PACKET(loginPkt);

	return true;
}

bool Handle_C_ENTER_GAME(PacketSessionRef& session, Protocol::C_ENTER_GAME& pkt)
{
	return false;
}

bool Handle_C_CHAT(PacketSessionRef& session, Protocol::C_CHAT& pkt)
{
	return true;
}
