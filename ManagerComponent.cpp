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
#include "ManagerFactoryResources.h"
#include "constants.h"

ManagerComponent::ManagerComponent(GameScene& i_gameScene)
{
	m_mapLayer				= new MapLayer(i_gameScene);
	m_managerObjectAndFile	= new ManagerObjectAndFile();
	m_hero					= new HeroGraphicComponent(*m_mapLayer);

	m_inputComponent		= new HeroInputComponent();
	m_managerArmy			= new ManagerArmy();
	m_managerMachine		= new ManagerMachine();
	m_managerFactory		= new ManagerFactory();
	m_AIAct					= new AIAct();
	m_AIDirection			= new AIDirection();
	
	m_inputComponent = new HeroInputComponent();

	m_messagingSystem	= new MessagingSystem(*m_mapLayer);
	m_managerArmy		= new ManagerArmy();
	m_managerMachine	= new ManagerMachine();
	m_managerFactory	= new ManagerFactory();
	m_managerFactoryResources = new ManagerFactoryResources();
	m_AIAct				= new AIAct();
	m_AIDirection		= new AIDirection();

	m_managerObjectAndFile->AddObjectOnMap(i_gameScene, *this);
	m_mapLayer->SetZoneForFactory(*this);
}

void ManagerComponent::Update(GameScene& i_gameScene)
{
	m_hero->Update			(*this);
	m_inputComponent->Update(*this);
	m_mapLayer->Update		(*this);

	m_managerFactoryResources->Update(*this);
	m_managerArmy->Update	(i_gameScene, *this);
	m_managerMachine->Update(i_gameScene, *this);
	m_managerFactory->Update(i_gameScene, *this);
}

ManagerComponent::~ManagerComponent()
{
	delete m_mapLayer;
	delete m_hero;
	delete m_houseFamily;
	delete m_managerArmy;
	delete m_managerFactory;
	delete m_managerMachine;
	delete m_inputComponent;
	delete m_AIAct;
	delete m_AIDirection;
	delete m_managerObjectAndFile;
	delete m_messagingSystem;
	delete m_managerFactoryResources;

	CCLOG("DESTRUCTOR managercomponent");
}