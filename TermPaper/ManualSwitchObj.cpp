#include "ManualSwitchObj.h"

void ManualSwitchObj::makeAction(Action)
{
	is_active = !is_active;
}

bool ManualSwitchObj::isActive()
{
	return is_active;
}

ManualSwitchObj::~ManualSwitchObj()
{
}
