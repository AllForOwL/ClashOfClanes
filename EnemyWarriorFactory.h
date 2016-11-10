#ifndef __ENEMY_WARRIOR_FACTORY_H__
#define __ENEMY_WARRIOR_FACTORY_H__

#include "cocos2d.h"
#include "Factory.h"
#include "ManagerArmy.h"

USING_NS_CC;

class MapLayer;

class EnemyWarriorFactory : public Factory
{
public:

	enum StateFactoryWarrior
	{
		WORKING,
		LISTEN,
		NOTHING
	};

	EnemyWarriorFactory();
	EnemyWarriorFactory(Point i_positionVisible, MapLayer& i_mapLayer);
	EnemyWarriorFactory(EnemyWarriorFactory& i_EnemyWarriorFactory);

	~EnemyWarriorFactory();

	virtual void Update(ManagerComponent& i_manager);

	StateFactoryWarrior& GetStateWarrior();

	void SetState(StateFactoryWarrior& i_stateWarrior);

	void LoadNameForSprites();

	bool DetermineCommand();

private:
	StateFactoryWarrior m_stateWarrior;
};

#endif