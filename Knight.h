#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "cocos2d.h"
#include "Warrior.h"

USING_NS_CC;

class ManagerComponent;
class MapLayer;

class Knight : public Warrior
{
public:

	enum StateKnight
	{
		ATTACK,
		RUN,
		MOVE_TOP,
		MOVE_RIGHT,
		MOVE_BOTTOM,
		MOVE_LEFT,
		HIDE,
		FIND_ACT,
		NOTHING
	};

	Knight();
	Knight(std::string i_typeKnight, MapLayer& i_parentMapLayer);
	Knight(Knight& heroGraphiComponent);

	~Knight();

	void ActAttack();
	void ActRun();
	void ActWander();
	void ActHide();

	virtual void Update(ManagerComponent& i_manager);

private:
	bool		m_spear;
	StateKnight	m_state;
};

#endif