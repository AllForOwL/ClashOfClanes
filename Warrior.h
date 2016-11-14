#ifndef __WARRIOR_H__
#define __WARRIOR_H__

#include "cocos2d.h"

#include "Combatant.h"

USING_NS_CC;

class Warrior : public Combatant
{
public:
	Warrior(){};
	Warrior(MapLayer& i_parentMapLayer) : Combatant(i_parentMapLayer)
	{

	}
	~Warrior(){};

private:

};

#endif