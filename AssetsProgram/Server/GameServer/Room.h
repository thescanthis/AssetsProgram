#pragma once
#include "JobQueue.h"

class Room : public JobQueue
{
public:
	Room();
	virtual ~Room();

public:
	void UpdateTick();

	RoomRef GetRoomRef();
private:
	bool AddObject(ObjectRef player);
	bool RemoveObject(uint64 objectId);

private:
	void Broadcast(SendBufferRef sendBuffer, uint64 exceptId = 0);

private:
	//1. 관리편안.
	unordered_map<uint64, ObjectRef> _objects;
};

extern RoomRef GRoom;