#pragma once

#define WIN32_LEAN_AND_MEAN // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

#ifdef _DEBUG
#pragma comment(lib, "ServerCore\\Debug\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#else
#pragma comment(lib, "ServerCore\\Release\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")
#endif

#include "CorePch.h"

#include "Protocol.pb.h"
#include "Enum.pb.h"
#include "Struct.pb.h"
#include "ServerPacketHandler.h"
#include "Utils.h"
#include "GameSession.h"

USING_SHARED_PTR(GameSession);
USING_SHARED_PTR(Room);
USING_SHARED_PTR(Object);
USING_SHARED_PTR(Creature);
USING_SHARED_PTR(Monster);
USING_SHARED_PTR(Player);

#define SEND_PACKET(pkt)													\
	SendBufferRef sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);	\
	session->Send(sendBuffer);



#if 0
GenPackets.. ��ɾ� ī���ϴ°���.
XCOPY / Y Enum.pb.h "../../../DummyClient"
XCOPY / Y Enum.pb.cc "../../../DummyClient"
XCOPY / Y Struct.pb.h "../../../DummyClient"
XCOPY / Y Struct.pb.cc "../../../DummyClient"
XCOPY / Y Protocol.pb.h "../../../DummyClient"
XCOPY / Y Protocol.pb.cc "../../../DummyClient"
XCOPY / Y ClientPacketHandler.h "../../../DummyClient"

XCOPY / Y Enum.pb.h "../../../../S1/Source/S1/Network"
XCOPY / Y Enum.pb.cc "../../../../S1/Source/S1/Network"
XCOPY / Y Struct.pb.h "../../../../S1/Source/S1/Network"
XCOPY / Y Struct.pb.cc "../../../../S1/Source/S1/Network"
XCOPY / Y Protocol.pb.h "../../../../S1/Source/S1/Network"
XCOPY / Y Protocol.pb.cc "../../../../S1/Source/S1/Network"
XCOPY / Y ClientPacketHandler.h "../../../../S1/Source/S1"
#endif 