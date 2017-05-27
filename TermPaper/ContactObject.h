#pragma once
#include "Box2D\Box2D.h"

enum class StaticType
{
	DANGER
};

enum EntityCategory {
	PLAYER = 0x0002,
	DANGERS = 0x0004,
	OTHERS = 0x0008,
	BONUSES = 0x0010
};

enum EntityGroup {
	MASK_PLAYER = ~PLAYER,
    MASK_DANGERS = PLAYER,
	MASK_OTHERS = PLAYER | OTHERS,
	MASK_BONUSES = PLAYER,
};

class ContactObject
{
public:
	virtual void contactEvent(b2Contact*, bool) = 0;
	virtual ~ContactObject(){}
};
