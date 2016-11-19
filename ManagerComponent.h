#ifndef __MANAGER_COMPONENT_H__
#define __MANAGER_COMPONENT_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene;
class MapLayer;
class HeroGraphicComponent;
class FamilyHouse;
class ManagerArmy;
class ManagerFactory;
class ManagerMachine;
class HeroInputComponent;
class AIAct;
class AIDirection;

class ManagerComponent
{
public:
	ManagerComponent(GameScene& i_gameScene);
	~ManagerComponent();

	void Update(GameScene& i_gameScene);

	void AddObjectFromFile(GameScene& i_gameScene);

public:
	MapLayer*				m_mapLayer;
	HeroGraphicComponent*	m_hero;
	FamilyHouse*			m_houseFamily;
	ManagerArmy*			m_managerArmy;
	ManagerFactory*			m_managerFactory;
	ManagerMachine*			m_managerMachine;
	HeroInputComponent*		m_inputComponent;
	AIAct*					m_AIAct;
	AIDirection*			m_AIDirection;
};

#endif