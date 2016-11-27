#include "ManagerMachine.h"
#include "GameScene.h"
#include "ManagerComponent.h"
#include "MapLayer.h"
#include "EnemyMachine.h"
#include "HeroMachine.h"
#include "HeroInputComponent.h"

ManagerMachine::ManagerMachine()
{
	
}

ManagerMachine::ManagerMachine(ManagerMachine& i_managerMachine)
{

}

void ManagerMachine::LaunchFillRegion(const Machine& i_machine, ManagerComponent& i_manager, int i_typeMachine)
{
	m_positionNewMachine	= i_machine.getPosition();
	m_sizeNewMachine		= i_machine.getBoundingBox().size;

	i_manager.m_mapLayer->FillRegionFromObject(i_manager, i_typeMachine, m_positionNewMachine, m_sizeNewMachine);
	i_manager.m_inputComponent->SetZeroLocation();
}

void ManagerMachine::Update(GameScene& i_gameScene, ManagerComponent& i_manager)
{
	switch (m_stateManagerMachine)
	{
		case ManagerMachine::ADD_TANK:
		{
			Machine* _newMachine = new HeroMachine(CNT_TYPE_TANK, *i_manager.m_mapLayer);
			_newMachine->setPosition(m_pointBuildMachine);
			m_vecMachineTank.push_back(_newMachine);
			LaunchFillRegion(*_newMachine, i_manager, CNT_OBJECT_TANK);

			m_stateManagerMachine = StateManagerMachine::NOTHING;

			break;
		}
		case ManagerMachine::ADD_ENEMY_OCTOPEDE:
		{
			Machine* _newOctopede = new EnemyMachine(CNT_TYPE_OCTOPEDE, *i_manager.m_mapLayer);
			_newOctopede->setPosition(m_pointBuildMachine);
			m_vecEnemyMachine.push_back(_newOctopede);
			LaunchFillRegion(*_newOctopede, i_manager, CNT_OBJECT_ENEMY_OCTOPEDE);

			m_stateManagerMachine = StateManagerMachine::NOTHING;

			break;
		}
		case ManagerMachine::ADD_ENEMY_BRAIN:
		{
			Machine* _newBrain = new EnemyMachine(CNT_TYPE_BRAIN, *i_manager.m_mapLayer);
			_newBrain->setPosition(m_pointBuildMachine);
			m_vecEnemyMachine.push_back(_newBrain);
			LaunchFillRegion(*_newBrain, i_manager, CNT_OBJECT_ENEMY_BRAIN);

			m_stateManagerMachine = StateManagerMachine::NOTHING;

		   break;
		}
		case ManagerMachine::ADD_ENEMY_TURTLE:
		{
			Machine* _newTurtle = new EnemyMachine(CNT_TYPE_TURTLE, *i_manager.m_mapLayer);
			_newTurtle->setPosition(m_pointBuildMachine);
			m_vecEnemyMachine.push_back(_newTurtle);
			LaunchFillRegion(*_newTurtle, i_manager, CNT_OBJECT_ENEMY_TURTLE);

			m_stateManagerMachine = StateManagerMachine::NOTHING;

			break;
		}
		case ManagerMachine::NOTHING:
		{
			if (m_vecMachineTank.size())
			{
				for (int i = 0; i < m_vecMachineTank.size(); i++)
				{
					m_vecMachineTank[i]->Update(i_manager);
				}
			}

			if (m_vecEnemyMachine.size())
			{
				for (int i = 0; i < m_vecEnemyMachine.size(); i++)
				{
					m_vecEnemyMachine[i]->Update(i_manager);
				}
			}

			break;
		}
	default:
		break;
	}
}

void ManagerMachine::SetState(StateManagerMachine& i_state)
{
	m_stateManagerMachine = i_state;
}

void ManagerMachine::SetPositionForMachine(Point i_pointBuildMachine)
{
	m_pointBuildMachine = i_pointBuildMachine;
}

ManagerMachine::~ManagerMachine()
{

}