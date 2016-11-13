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
		MOVE_FORWARD,
		MOVE_BACK,
		MOVE_RIGHT, 
		MOVE_LEFT,
		FIND_ACT,
		NOTHING
	};

	Knight();
	Knight(std::string i_typeKnight, MapLayer& i_parentMapLayer);
	Knight(Knight& heroGraphiComponent);

	~Knight();

	void MoveForward();
	void MoveBack();
	void MoveRight();
	void MoveLeft();

	virtual void Update(ManagerComponent& i_manager);

	void SetStatusPositionForCurrentDirection(ManagerComponent& i_manager);
	void UpdateDirection(ManagerComponent& i_manager);

private:

	struct Direction
	{
		bool m_west;
		bool m_east;
		bool m_north;
		bool m_south;

		Direction() :	m_west(false),
						m_east(true),
						m_north(false),
						m_south(false)
		{

		}
	};

	struct StatusPosition
	{
		double forward;
		double back;
		double right;
		double left;
	};

	struct Position
	{
		Point forward;
		Point back;
		Point right;
		Point left;
	};

	struct ActWander
	{
		int current;
		int previous;

		ActWander() :	current(-1),
						previous(-1)
		{

		}
	};

	bool				m_spear;
	StateKnight			m_state;
	std::vector<bool>	m_direction;
	int					m_indexDirection;
	StatusPosition		m_statusPosition;
	Position			m_position;
	ActWander			m_actWander;

};

#endif