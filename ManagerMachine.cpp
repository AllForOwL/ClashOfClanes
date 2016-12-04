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

void ManagerMachine::CreateMachine(ManagerComponent& i_manager)
{
	Machine* _newMachine = new HeroMachine(m_pointBuildMachine, *i_manager.m_mapLayer, std::string("Machine/Tank_1.png"));
	m_vecMachineTank.push_back(_newMachine);
	LaunchFillRegion(*_newMachine, i_manager, CNT_OBJECT_TANK);
	i_manager.m_managerObjectAndFile->WriteObjectInFile(CNT_OBJECT_TANK, m_pointBuildMachine, (i_manager.m_mapLayer->getPosition() * -1));
}

void ManagerMachine::CreateMachineEnemy(ManagerComponent& i_manager, int i_typeObject, std::string i_nameFile)
{
	Machine* _newOctopede = new EnemyMachine(m_pointBuildMachine, *i_manager.m_mapLayer, i_nameFile);
	m_vecEnemyMachine.push_back(_newOctopede);
	LaunchFillRegion(*_newOctopede, i_manager, i_typeObject);
	i_manager.m_managerObjectAndFile->WriteObjectInFile(i_typeObject, m_pointBuildMachine, (i_manager.m_mapLayer->getPosition() * -1));
}

void ManagerMachine::UpdateAllMachine(ManagerComponent& i_manager)
{
	for (int i = 0; i < m_vecEnemyMachine.size(); i++)
	{
		m_vecEnemyMachine[i]->Update(i_manager);
	}

	for (int i = 0; i < m_vecMachineTank.size(); i++)
	{
		m_vecMachineTank[i]->Update(i_manager);
	}
}

void ManagerMachine::Update(GameScene& i_gameScene, ManagerComponent& i_manager)
{
	switch (m_stateManagerMachine)
	{
		case ManagerMachine::ADD_TANK:
		{
			CreateMachine(i_manager);

			m_stateManagerMachine = StateManagerMachine::NOTHING;

			break;
		}
		case ManagerMachine::ADD_ENEMY_OCTOPEDE:
		{
			CreateMachineEnemy(i_manager, CNT_OBJECT_ENEMY_OCTOPEDE, CNT_PATH_TO_RESOURCES + "Enemy/Machine/Octopede.png");

			m_stateManagerMachine = StateManagerMachine::NOTHING;

			break;
		}
		case ManagerMachine::ADD_ENEMY_BRAIN:
		{
			CreateMachineEnemy(i_manager, CNT_OBJECT_ENEMY_BRAIN, CNT_PATH_TO_RESOURCES + "Enemy/Machine/Brain.png");

			m_stateManagerMachine = StateManagerMachine::NOTHING;

		   break;
		}
		case ManagerMachine::ADD_ENEMY_TURTLE:
		{
			CreateMachineEnemy(i_manager, CNT_OBJECT_ENEMY_TURTLE, CNT_PATH_TO_RESOURCES + "Enemy/Machine/Turtle.png");

			m_stateManagerMachine = StateManagerMachine::NOTHING;

			break;
		}
		case ManagerMachine::NOTHING:
		{
			UpdateAllMachine(i_manager);

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