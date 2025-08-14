#pragma once
class Object : enable_shared_from_this<Object>
{
public:
	Object();
	virtual ~Object();

public:
	bool IsPlayer() { return _isPlayer; }

public:
	Protocol::ObjectInfo* objectInfo;
	Protocol::PosInfo* posInfo;

public:
	atomic<weak_ptr<Room>> room;

protected:
	bool _isPlayer = false;
};

