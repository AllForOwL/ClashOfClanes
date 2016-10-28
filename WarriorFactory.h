#ifndef __WARRIOR_FACTORY_H__
#define __WARRIOR_FACTORY_H__

#include "cocos2d.h"
#include "Factory.h"

USING_NS_CC;

class WarriorFactory : public Factory
{
public:

	enum StateFactory
	{
		START_ARCHER,
		WORKING,
		NOTHING
	};

	WarriorFactory();
	WarriorFactory(GameScene& i_parentGameScene);
	WarriorFactory(WarriorFactory& i_warriorFactory);

	~WarriorFactory();

	virtual void Update(ManagerComponent& i_manager);

	bool isComplete();

private:
	StateFactory m_stateFactory;
	std::chrono::time_point<std::chrono::system_clock> m_startSecond;
	int m_timeForCompleteWarrior;

};

#endif