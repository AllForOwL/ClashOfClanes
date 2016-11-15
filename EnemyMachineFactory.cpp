#include "EnemyMachineFactory.h"
#include "ManagerComponent.h"
#include "GraphicComponent.h"
#include "ManagerMachine.h"
#include "MapLayer.h"
#include "HeroGraphicComponent.h"
#include "HeroInputComponent.h"

const int CNT_TIME_FOR_COMPLETE_OCTOPEDE	= 5;
const int CNT_TIME_FOR_COMPLETE_BRAIN		= 5;
const int CNT_TIME_FOR_COMPLETE_TURTLE		= 5;

const int INDEX_OCTOPEDE	= 0;
const int INDEX_BRAIN		= 1;
const int INDEX_TURTLE		= 2;

EnemyMachineFactory::EnemyMachineFactory()
{

}

EnemyMachineFactory::EnemyMachineFactory(Point i_positionVisible, MapLayer& i_mapLayer) : Factory(i_positionVisible, i_mapLayer, "Home/home2.png")
{
	m_stateMachine	= StateFactoryMachine::NOTHING;
}

EnemyMachineFactory::EnemyMachineFactory(EnemyMachineFactory& i_EnemyMachineFactory)
{

}

void EnemyMachineFactory::SetState(EnemyMachineFactory::StateFactoryMachine& i_state)
{
	m_stateMachine = i_state;
}

void EnemyMachineFactory::LoadNameForSprites()
{
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Enemy/Machine/Octopede.png");
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Enemy/Machine/Brain.png");
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Enemy/Machine/Turtle.png");
}

/*virtual*/ void EnemyMachineFactory::Update(ManagerComponent& i_manager)
{
	switch (m_stateMachine)
	{
		case StateFactoryMachine::START_OCTOPEDE:
		{
			if (i_manager.m_hero->CheckProductionTank())
			{
				m_timeForComplete			= CNT_TIME_FOR_COMPLETE_OCTOPEDE;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateMachine				= StateFactoryMachine::WORKING;
				m_stateManagerMachine		= ManagerMachine::StateManagerMachine::ADD_ENEMY_OCTOPEDE;
			}
			break;
		}
		case StateFactoryMachine::START_BRAIN:
		{
			if (i_manager.m_hero->CheckProductionCar())
			{
				m_timeForComplete			= CNT_TIME_FOR_COMPLETE_BRAIN;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateMachine				= StateFactoryMachine::WORKING;
				m_stateManagerMachine		= ManagerMachine::StateManagerMachine::ADD_ENEMY_BRAIN;
			}												
			break;
		}
		case StateFactoryMachine::START_TURTLE:
		{
			if (i_manager.m_hero->CheckProductionCar())
			{
				m_timeForComplete			= CNT_TIME_FOR_COMPLETE_TURTLE;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateMachine				= StateFactoryMachine::WORKING;
				m_stateManagerMachine		= ManagerMachine::StateManagerMachine::ADD_ENEMY_TURTLE;
			}												
			break;
		}
		case StateFactoryMachine::WORKING:
		{
			if (isComplete())
			{
				m_stateMachine = StateFactoryMachine::NOTHING;
				i_manager.m_managerMachine->SetState(m_stateManagerMachine);
				i_manager.m_managerMachine->SetPositionForMachine(m_vecPosition[m_numberComplete]);
				++m_numberComplete;
			}
			break;
		}
		case StateFactoryMachine::NOTHING:
		{
			m_locationTouch	= i_manager.m_inputComponent->GetLocationTouch();
			ConvertToOrigin();
			if (m_rectOriginWithVisible.containsPoint(m_locationTouch))
			{
				if (m_vecNameForSprites.empty())
				{
					LoadNameForSprites();
					LoadSprites();
				}

				ShowMenu();
				LoadPosition();
				m_stateMachine	= StateFactoryMachine::LISTEN;
				i_manager.m_inputComponent->SetZeroLocation();
			}
			break;
		}
		case StateFactoryMachine::LISTEN:
		{
			m_locationTouch = i_manager.m_inputComponent->GetLocationTouch();
			ConvertToOrigin();
			if (DetermineCommand())
			{
				i_manager.m_inputComponent->SetZeroLocation();
			}

			break;
		}
	default:
		break;
	}
}

bool EnemyMachineFactory::DetermineCommand()
{
	if (m_rectForSprites[INDEX_OCTOPEDE].containsPoint(m_locationTouch))
	{
		m_stateMachine = StateFactoryMachine::START_OCTOPEDE;
		return true;
	}
	else if (m_rectForSprites[INDEX_BRAIN].containsPoint(m_locationTouch))
	{
		m_stateMachine = StateFactoryMachine::START_BRAIN;
		return true;
	}
	else if (m_rectForSprites[INDEX_TURTLE].containsPoint(m_locationTouch))
	{
		m_stateMachine = StateFactoryMachine::START_TURTLE;
		return true;
	}
	return false;
}

EnemyMachineFactory::StateFactoryMachine& EnemyMachineFactory::GetState()
{
	return m_stateMachine;
}

EnemyMachineFactory::~EnemyMachineFactory()
{

}


/*
 Hero has goes on map
*/