#include "EnemyMachine.h"
#include "GameScene.h"
#include "MapLayer.h"
#include "ManagerComponent.h"

const int CNT_SPEED_OCTOPEDE	= 2;
const int CNT_SPEED_BRAIN		= 3;

EnemyMachine::EnemyMachine()
{

}

EnemyMachine::EnemyMachine(std::string i_EnemyMachine, MapLayer& i_parentMapLayer) : Machine(i_parentMapLayer)
{			
	if (i_EnemyMachine == CNT_TYPE_OCTOPEDE)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Enemy/Machine/Octopede.png");
		m_speed			= CNT_SPEED_OCTOPEDE;
		m_typeObject	= CNT_OBJECT_ENEMY_OCTOPEDE;	
	}
	else if (i_EnemyMachine == CNT_TYPE_BRAIN)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Enemy/Machine/Brain.png");
		m_speed			= CNT_SPEED_BRAIN;
		m_typeObject	= CNT_OBJECT_ENEMY_BRAIN;
	}
	else if (i_EnemyMachine == CNT_TYPE_TURTLE)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Enemy/Machine/Turtle.png");
		m_typeObject	= CNT_OBJECT_ENEMY_TURTLE;
	}

	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 13,
		GameScene::m_visibleSize.height / this->getContentSize().height / 13);
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