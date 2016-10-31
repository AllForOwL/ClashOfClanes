#ifndef __WARRIOR_FACTORY_H__
#define __WARRIOR_FACTORY_H__

#include "cocos2d.h"
#include "Factory.h"
#include "ManagerArmy.h"

USING_NS_CC;

class WarriorFactory : public Factory
{
public:

	enum StateFactoryWarrior
	{
		START_ARCHER,
		START_KNIGHT_BLACK,
		START_KNIGHT_BRONZE,
		START_KNIGHT_SILVER,
		WORKING,
		LISTEN,
		NOTHING
	};

	WarriorFactory();
	WarriorFactory(GameScene& i_parentGameScene);
	WarriorFactory(WarriorFactory& i_warriorFactory);

	~WarriorFactory();

	virtual void Update(ManagerComponent& i_manager);

	bool isComplete();

	StateFactoryWarrior& GetStateWarrior();

	void SetState(StateFactoryWarrior& i_stateWarrior);

private:
	StateFactoryWarrior m_stateFactory;
	std::chrono::time_point<std::chrono::system_clock> m_startSecond;
	int m_timeForCompleteWarrior;
	ManagerArmy::StateManagerArmy m_stateTypeAddWarrior;

	StateFactoryWarrior m_stateWarrior;
	Vec2				m_locationTouch;
	Rect				m_rectFactory;
};

#endif