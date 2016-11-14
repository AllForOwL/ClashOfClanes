#ifndef __MACHINE_H__
#define __MACHINE_H__

#include "cocos2d.h"
#include "Combatant.h"

USING_NS_CC;

class ManagerComponent;

class Machine : public Combatant
{
public:
	Machine(){};
	Machine(MapLayer& i_parentMapLayer) : Combatant(i_parentMapLayer){};
	~Machine(){};

	virtual void Update(ManagerComponent& i_manager) = 0;
};

#endif