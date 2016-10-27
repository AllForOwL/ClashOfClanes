#ifndef __MANAGER_COMPONENT_H__
#define __MANAGER_COMPONENT_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene;
class MapLayer;
class HeroGraphicComponent;
class FamilyHouse;

class ManagerComponent
{
public:
	ManagerComponent(GameScene& i_gameScene);
	~ManagerComponent();

	void Update(GameScene& i_gameScene);

private:
	MapLayer*				m_mapLayer;
	HeroGraphicComponent*	m_hero;
	FamilyHouse*			m_houseFamily;
};

#endif