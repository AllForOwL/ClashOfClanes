#include "ManagerMachine.h"
#include "GameScene.h"
#include "ManagerComponent.h"
#include "MapLayer.h"
#include "EnemyMachine.h"
#include "HeroMachine.h"
#include "HeroInputComponent.h"
#include "ManagerObjectAndFile.h"

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
			Machine* _newMachine = new HeroMachine(m_pointBuildMachine, *i_manager.m_mapLayer, std::string("Machine/Tank_1.png"));
			m_vecMachineTank.push_back(_newMachine);
			LaunchFillRegion(*_newMachine, i_manager, CNT_OBJECT_TANK);
			i_manager.m_managerObjectAndFile->WriteObjectInFile(CNT_OBJECT_TANK, m_pointBuildMachine, (i_manager.m_mapLayer->getPosition() * -1));

			m_stateManagerMachine = StateManagerMachine::NOTHING;

			break;
		}
		case ManagerMachine::ADD_ENEMY_OCTOPEDE:
		{
			Machine* _newOctopede = new EnemyMachine(m_pointBuildMachine, *i_manager.m_mapLayer, std::string("Enemy/Machine/Octopede.png"));
			m_vecEnemyMachine.push_back(_newOctopede);
			LaunchFillRegion(*_newOctopede, i_manager, CNT_OBJECT_ENEMY_OCTOPEDE);
			i_manager.m_managerObjectAndFile->WriteObjectInFile(CNT_OBJECT_ENEMY_OCTOPEDE, m_pointBuildMachine, (i_manager.m_mapLayer->getPosition() * -1));

			m_stateManagerMachine = StateManagerMachine::NOTHING;

			break;
		}
		case ManagerMachine::ADD_ENEMY_BRAIN:
		{
			Machine* _newBrain = new EnemyMachine(m_pointBuildMachine, *i_manager.m_mapLayer, std::string("Ememy/Machine/Brain.png"));
			m_vecEnemyMachine.push_back(_newBrain);
			LaunchFillRegion(*_newBrain, i_manager, CNT_OBJECT_ENEMY_BRAIN);
			i_manager.m_managerObjectAndFile->WriteObjectInFile(CNT_OBJECT_ENEMY_BRAIN, m_pointBuildMachine, (i_manager.m_mapLayer->getPosition() * -1));

			m_stateManagerMachine = StateManagerMachine::NOTHING;

		   break;
		}
		case ManagerMachine::ADD_ENEMY_TURTLE:
		{
			Machine* _newTurtle = new EnemyMachine(m_pointBuildMachine, *i_manager.m_mapLayer, std::string("Enemy/Machine/Turtle.png"));
			m_vecEnemyMachine.push_back(_newTurtle);
			LaunchFillRegion(*_newTurtle, i_manager, CNT_OBJECT_ENEMY_TURTLE);
			i_manager.m_managerObjectAndFile->WriteObjectInFile(CNT_OBJECT_ENEMY_TURTLE, m_pointBuildMachine, (i_manager.m_mapLayer->getPosition() * -1));

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