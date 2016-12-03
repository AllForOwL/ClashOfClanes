#include "EnemyMachine.h"
#include "GameScene.h"
#include "MapLayer.h"
#include "ManagerComponent.h"

const int CNT_SPEED_OCTOPEDE	= 2;
const int CNT_SPEED_BRAIN		= 3;

EnemyMachine::EnemyMachine()
{

}

EnemyMachine::EnemyMachine(Point i_positionVisible, MapLayer& i_parentMapLayer, std::string i_fileMachine) : Machine(i_positionVisible,
																													 i_parentMapLayer,
																													 i_fileMachine)
{			

}

EnemyMachine::EnemyMachine(EnemyMachine& EnemyMachine)
{
	
}

/*virtual*/ void EnemyMachine::Update(ManagerComponent& i_manager)
{
	switch (m_state)
	{
		case StateCombatant::MOVE_FORWARD:
		{
			MoveForward();
			m_state	= StateCombatant::FIND_ACT;

			break;
		}
		case StateCombatant::MOVE_BACK:
		{
			MoveBack();
			m_state = StateCombatant::FIND_ACT;

			break;
		}
		case StateCombatant::MOVE_RIGHT:
		{
			MoveRight();
			m_state = StateCombatant::FIND_ACT;

			break;
		}
		case StateCombatant::MOVE_LEFT:
		{
			MoveLeft();
			m_state = StateCombatant::FIND_ACT;

			break;
		}
		case StateCombatant::FIND_ACT:
		{
			SetStatusPositionForCurrentDirection(i_manager);
			UpdateDirection(i_manager);

			break;
		}
		case StateCombatant::NOTHING:
		{

			break;
		}
	default:
		break;
	}
}

EnemyMachine::~EnemyMachine()
{
	CCLOG("destructor EnemyMachine");
}

/*  GraphicComponent	- тільки малює спрайти 
	PhysicsComponent	- виявлє зіткнення героя
	InputComponent		- приймає діна з клавіатури
	ManagerComponent	- контейнер для цих компонентів
*/