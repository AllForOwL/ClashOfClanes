#include "ManagerMachine.h"
#include "GameScene.h"
#include "ManagerComponent.h"
#include "MapLayer.h"
#include "EnemyMachine.h"

ManagerMachine::ManagerMachine()
{
	
}

ManagerMachine::ManagerMachine(ManagerMachine& i_managerMachine)
{

}

void ManagerMachine::Update(GameScene& i_gameScene, ManagerComponent& i_manager)
{
	switch (m_stateManagerMachine)
	{
		case ManagerMachine::ADD_TANK:
		{
			
			m_stateManagerMachine = StateManagerMachine::NOTHING;

			break;
		}
		case ManagerMachine::ADD_CAR:
		{
					
			m_stateManagerMachine = StateManagerMachine::NOTHING;

			break;
		}
		case ManagerMachine::ADD_ENEMY_OCTOPEDE:
		{
			EnemyMachine* _newOctopede = new EnemyMachine(CNT_TYPE_OCTOPEDE, *i_manager.m_mapLayer);
			_newOctopede->setPosition(m_pointBuildMachine);
			m_vecEnemyMachine.push_back(_newOctopede);

			m_stateManagerMachine = StateManagerMachine::NOTHING;

			break;
		}
		case ManagerMachine::ADD_ENEMY_BRAIN:
		{
			EnemyMachine* _newOctopede = new EnemyMachine(CNT_TYPE_BRAIN, *i_manager.m_mapLayer);
			_newOctopede->setPosition(m_pointBuildMachine);
			m_vecEnemyMachine.push_back(_newOctopede);

			m_stateManagerMachine = StateManagerMachine::NOTHING;

		   break;
		}
		case ManagerMachine::ADD_ENEMY_TURTLE:
		{
			EnemyMachine* _newOctopede = new EnemyMachine(CNT_TYPE_TURTLE, *i_manager.m_mapLayer);
			_newOctopede->setPosition(m_pointBuildMachine);
			m_vecEnemyMachine.push_back(_newOctopede);

			m_stateManagerMachine = StateManagerMachine::NOTHING;

			break;
		}
		case ManagerMachine::NOTHING:
		{
			if (m_vecMachineCar.size())
			{
				for (int i = 0; i < m_vecMachineCar.size(); i++)
				{
					m_vecMachineCar[i]->Update(i_manager);
				}
			}
			
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