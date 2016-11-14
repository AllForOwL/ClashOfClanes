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

	Knight();
	Knight(std::string i_typeKnight, MapLayer& i_parentMapLayer);
	Knight(Knight& heroGraphiComponent);

	~Knight();

	virtual void Update(ManagerComponent& i_manager);

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

	bool	m_spear;
};

#endif