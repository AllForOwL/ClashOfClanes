#ifndef __EnemyWarrior_H__
#define __EnemyWarrior_H__

#include "cocos2d.h"
#include "Warrior.h"

USING_NS_CC;

class ManagerComponent;
class MapLayer;

class EnemyWarrior : public Warrior
{
public:

	enum StateEnemyWarrior
	{
		ATTACK,
		RUN,
		WANDER,
		HIDE,
		FIND_ACT,
		NOTHING
	};

	EnemyWarrior();
	EnemyWarrior(std::string i_typeEnemyWarrior, MapLayer& i_parentMapLayer);
	EnemyWarrior(EnemyWarrior& heroGraphiComponent);

	~EnemyWarrior();

	void ActAttack();
	void ActRun();
	void ActWander();
	void ActHide();

	virtual void Update(ManagerComponent& i_manager);

private:
	StateEnemyWarrior	m_state;
};

#endif