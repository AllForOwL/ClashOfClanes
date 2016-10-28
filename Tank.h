#ifndef __Tank_H__
#define __Tank_H__

#include "cocos2d.h"
#include "Warrior.h"

USING_NS_CC;

class ManagerComponent;
class GameScene;

class Tank : public Warrior
{
public:
	Tank();
	Tank(GameScene& i_parentGameScene);
	Tank(Tank& i_tank);

	~Tank();

	virtual void Update(ManagerComponent& i_manager);

private:

};

#endif