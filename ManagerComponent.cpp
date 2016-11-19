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
#include "AIDirection.h"
#include "constants.h"

ManagerComponent::ManagerComponent(GameScene& i_gameScene)
{
	m_mapLayer		= new MapLayer(i_gameScene);
	m_hero			= new HeroGraphicComponent(*m_mapLayer);
	
	m_inputComponent = new HeroInputComponent();

	m_managerArmy		= new ManagerArmy();
	m_managerMachine	= new ManagerMachine();
	m_managerFactory	= new ManagerFactory();
	m_AIAct				= new AIAct();
	m_AIDirection		= new AIDirection();

	m_addObjectFromFile = true;
	AddObjectFromFile(i_gameScene);
}


void ManagerComponent::AddObjectFromFile(GameScene& i_gameScene)
{
	using StateArmy		= ManagerArmy::StateManagerArmy;
	using StateMachine	= ManagerMachine::StateManagerMachine;
	using StateFactory	= ManagerFactory::StateManagerFactory;

	StateArmy _stateArmy		= StateArmy::NOTHING;
	StateMachine _stateMachine	= StateMachine::NOTHING;
	StateFactory _stateFactory	= StateFactory::NOTHING;
	
	std::vector<MapLayer::ObjectInFile> _vecObject(m_mapLayer->GetVectorObject());

	for (int i = 0; i < _vecObject.size(); i++)
	{
		_stateArmy		= StateArmy::NOTHING;
		_stateMachine	= StateMachine::NOTHING;
		_stateFactory	= StateFactory::NOTHING;
		switch (_vecObject[i].typeObject)
		{
			case CNT_OBJECT_FACTORY_WARRIOR:
			{
				_stateFactory = StateFactory::ADD_FACTORY_WARRIOR;
				break;
			}
			case CNT_OBJECT_FACTORY_MACHINE:
			{
				_stateFactory = StateFactory::ADD_FACTORY_MACHINE;
				break;
			}
			case CNT_OBJECT_FACTORY_ENEMY_WARRIOR:
			{
				_stateFactory = StateFactory::ADD_FACTORY_ENEMY_WARRIOR;
				break;
			}
			case CNT_OBJECT_FACTORY_ENEMY_MACHINE:
			{
				_stateFactory = StateFactory::ADD_FACTORY_ENEMY_MACHINE;
				break;
			}
			case CNT_OBJECT_KNIGHT_BLACK:
			{
				_stateArmy = StateArmy::ADD_KNIGHT_BLACK;
				break;
			}
			case CNT_OBJECT_KNIGHT_BRONZE:
			{
				_stateArmy = StateArmy::ADD_KNIGHT_BRONZE;
				break;
			}
			case CNT_OBJECT_KNIGHT_SILVER:
			{
				_stateArmy = StateArmy::ADD_KNIGHT_SILVER;
				break;
			}
			case CNT_OBJECT_ENEMY_BOWMAN:
			{
				_stateArmy = StateArmy::ADD_ENEMY_BOWMAN;
				break;
			}
			case CNT_OBJECT_ENEMY_KNIGHT:
			{
				_stateArmy = StateArmy::ADD_ENEMY_KNIGHT;
				break;
			}
			case CNT_OBJECT_ENEMY_WIZARD:
			{
				_stateArmy = StateArmy::ADD_ENEMY_WIZARD;
				break;
			}
			case CNT_OBJECT_ENEMY_PALADIN:
			{
				_stateArmy = StateArmy::ADD_ENEMY_PALADIN;
				break;
			}
			case CNT_OBJECT_ENEMY_OCTOPEDE:
			{
				_stateMachine = StateMachine::ADD_ENEMY_OCTOPEDE;
				break;
			}
			case CNT_OBJECT_ENEMY_BRAIN:
			{
				_stateMachine = StateMachine::ADD_ENEMY_BRAIN;
				break;
			}
			case CNT_OBJECT_ENEMY_TURTLE:
			{
				_stateMachine = StateMachine::ADD_ENEMY_TURTLE;
				break;
			}
		}

		if (_stateArmy != StateArmy::NOTHING)
		{
			m_managerArmy->SetState(_stateArmy);
			m_managerArmy->SetPositionForWarrior(_vecObject[i].positionVisible);
			m_managerArmy->Update(i_gameScene, *this);
		}
		else if (_stateFactory != StateFactory::NOTHING)
		{
			m_managerFactory->SetState(_stateFactory);
			m_managerFactory->SetPositionBuildFactory(_vecObject[i].positionVisible);
			m_managerFactory->SetPositionOrigin(_vecObject[i].positionOrigin);
			m_managerFactory->Update(i_gameScene, *this);
		}
		else if (_stateMachine != StateMachine::NOTHING)
		{
			m_managerMachine->SetState(_stateMachine);
			m_managerMachine->SetPositionForMachine(_vecObject[i].positionVisible);
			m_managerMachine->Update(i_gameScene, *this);
		}
	}

	m_addObjectFromFile = false;
}

void ManagerComponent::Update(GameScene& i_gameScene)
{
	if (!m_addObjectFromFile)
	{
		m_hero->Update(*this);
		m_inputComponent->Update(*this);
		m_mapLayer->Update(*this);

		m_managerArmy->Update(i_gameScene, *this);
		m_managerMachine->Update(i_gameScene, *this);
		m_managerFactory->Update(i_gameScene, *this);
	}
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