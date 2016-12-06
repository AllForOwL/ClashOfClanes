#include "ManagerComponent.h"
#include "MapLayer.h"
#include "HeroGraphicComponent.h"
#include "FamilyHouse.h"
#include "GameScene.h"
#include "ManagerArmy.h"
#include "ManagerFactory.h"
#include "ManagerMachine.h"
#include "HeroInputComponent.h"
#include "AIAct.h"
#include "ManagerObjectAndFile.h"
#include "MessagingSystem.h"
#include "AIDirection.h"
#include "constants.h"

ManagerComponent::ManagerComponent(GameScene& i_gameScene)
{
	m_mapLayer				= new MapLayer(i_gameScene);
	m_managerObjectAndFile	= new ManagerObjectAndFile();
	m_hero					= new HeroGraphicComponent(*m_mapLayer);
<<<<<<< HEAD
	m_inputComponent		= new HeroInputComponent();
	m_managerArmy			= new ManagerArmy();
	m_managerMachine		= new ManagerMachine();
	m_managerFactory		= new ManagerFactory();
	m_AIAct					= new AIAct();
	m_AIDirection			= new AIDirection();
=======
	
	m_inputComponent = new HeroInputComponent();

	m_messagingSystem	= new MessagingSystem();
	m_managerArmy		= new ManagerArmy();
	m_managerMachine	= new ManagerMachine();
	m_managerFactory	= new ManagerFactory();
	m_AIAct				= new AIAct();
	m_AIDirection		= new AIDirection();
>>>>>>> refactoring

	m_managerObjectAndFile->AddObjectOnMap(i_gameScene, *this);
}

void ManagerComponent::Update(GameScene& i_gameScene)
{
	m_hero->Update			(*this);
	m_inputComponent->Update(*this);
	m_mapLayer->Update		(*this);

	m_managerArmy->Update	(i_gameScene, *this);
	m_managerMachine->Update(i_gameScene, *this);
	m_managerFactory->Update(i_gameScene, *this);

}

ManagerComponent::~ManagerComponent()
{
	delete m_hero;
	delete m_inputComponent;
	delete m_mapLayer;
	delete m_managerMachine;
	delete m_managerFactory;
	delete m_AIAct;

	CCLOG("DESTRUCTOR managercomponent");
}