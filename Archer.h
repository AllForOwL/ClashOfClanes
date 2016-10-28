#ifndef __ARCHER_H__
#define __ARCHER_H__

#include "cocos2d.h"
#include "Warrior.h"

USING_NS_CC;

class ManagerComponent;

class Archer : public Warrior
{
public:
	Archer();
	Archer(GameScene& i_parentGameScene);
	Archer(Archer& heroGraphiComponent);

	~Archer();

	virtual void Update(ManagerComponent& i_manager);

private:

};

#endif