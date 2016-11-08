#ifndef __Tank_H__
#define __Tank_H__

#include "cocos2d.h"
#include "Warrior.h"

USING_NS_CC;

class ManagerComponent;
class MapLayer;

class Tank : public Warrior
{
public:
	Tank();
	Tank(MapLayer& i_parentGameScene);
	Tank(Tank& i_tank);

	~Tank();

	virtual void Update(ManagerComponent& i_manager);

private:

};

#endif