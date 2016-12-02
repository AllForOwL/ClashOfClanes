#ifndef __WARRIOR_FACTORY_H__
#define __WARRIOR_FACTORY_H__

#include "cocos2d.h"
#include "Factory.h"
#include "ManagerArmy.h"

USING_NS_CC;

class MapLayer;

class WarriorFactory : public Factory
{
public:

	enum StateFactoryWarrior
	{
		START_KNIGHT_BLACK,
		START_KNIGHT_BRONZE,
		START_KNIGHT_SILVER,
		WORKING,
		LISTEN,
		NOTHING
	};

	WarriorFactory();
	WarriorFactory(Point i_positionVisible, MapLayer& i_mapLayer);
	WarriorFactory(WarriorFactory& i_warriorFactory);

	~WarriorFactory();

	virtual void Update(ManagerComponent& i_manager);

	StateFactoryWarrior& GetStateWarrior();

	void SetState(StateFactoryWarrior& i_stateWarrior);

	void LoadNameForSprites();
	bool DetermineCommand();

private:
	StateFactoryWarrior				m_stateWarrior;
	ManagerArmy::StateManagerArmy	m_stateTypeAddWarrior;
};

#endif