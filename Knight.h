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
	Knight(Point i_positionVisible, MapLayer& i_parentMapLayer, std::string i_fileWarrior);
	Knight(Knight& heroGraphiComponent);

	~Knight();

	void LoadNameForSprites();
	bool DetermineCommand();

	virtual void Update(ManagerComponent& i_manager);

private:
	bool	m_spear;
};

#endif