#ifndef __WARRIOR_FACTORY_H__
#define __WARRIOR_FACTORY_H__

#include "cocos2d.h"
#include "Factory.h"

USING_NS_CC;

class WarriorFactory : public Factory
{
public:
	WarriorFactory();
	WarriorFactory(GameScene& i_parentGameScene);
	WarriorFactory(const WarriorFactory& i_warriorFactory);

	~WarriorFactory();

	virtual void Update(GameScene& i_gameScene);
};

#endif