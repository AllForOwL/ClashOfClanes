#include "ManagerComponent.h"
#include "MapLayer.h"
#include "HeroGraphicComponent.h"
#include "FamilyHouse.h"
#include "GameScene.h"
#include "ManagerArmy.h"

ManagerComponent::ManagerComponent(GameScene& i_gameScene)
{
	m_mapLayer		= new MapLayer(i_gameScene);
	m_hero			= new HeroGraphicComponent(i_gameScene);
	m_houseFamily	= new FamilyHouse(i_gameScene);
	m_managerArmy	= new ManagerArmy();
}

void ManagerComponent::Update(GameScene& i_gameScene)
{

}

ManagerComponent::~ManagerComponent()
{

}


/*
	Create manager for factory
	Add to factory production other warrior
*/