#include "EnemyMachine.h"
#include "GameScene.h"
#include "constants.h"
#include "MapLayer.h"
#include "ManagerComponent.h"
#include "AI.h"

const int CNT_SPEED_OCTOPEDE	= 2;
const int CNT_SPEED_BRAIN		= 3;

EnemyMachine::EnemyMachine()
{

}

EnemyMachine::EnemyMachine(std::string i_EnemyMachine, MapLayer& i_parentMapLayer) : Warrior(i_parentMapLayer)
{			
	if (i_EnemyMachine == CNT_TYPE_OCTOPEDE)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Enemy/Machine/Octopede.png");
		m_speed = CNT_SPEED_OCTOPEDE;
	}
	else if (i_EnemyMachine == CNT_TYPE_BRAIN)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Enemy/Machine/Brain.png");
		m_speed = CNT_SPEED_BRAIN;
	}
	else if (i_EnemyMachine == CNT_TYPE_TURTLE)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Enemy/Machine/Turtle.png");
	}

	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 13,
		GameScene::m_visibleSize.height / this->getContentSize().height / 13);

	m_state	= StateEnemyMachine::NOTHING;
}

EnemyMachine::EnemyMachine(EnemyMachine& EnemyMachine)
{
	
}

/*virtual*/ void EnemyMachine::Update(ManagerComponent& i_manager)
{
	switch (m_state)
	{
		case StateEnemyMachine::ATTACK:
		{
			ActAttack();			

			break;
		}
		case StateEnemyMachine::RUN:
		{
			ActRun();

			break;
		}
		case StateEnemyMachine::WANDER:
		{
			ActWander();

			break;
		}
		case StateEnemyMachine::HIDE:
		{
			ActHide();

			break;
		}
		case StateEnemyMachine::FIND_ACT:
		{
			int _quentityEnemy = i_manager.m_mapLayer->GetQuentityEnemy(this->getPosition());
			
			double _spear = 0.0;
			/*if (m_spear)
			{
				_spear = 1.0;
			}*/

			double _health = 0.0;
			if (m_health >= 75)
			{
				_health = 2.0;
			}
			else if (m_health >= 35)
			{
				_health = 1.0;
			}
			else
			{
				_health = 0.0;
			}

			int _numberAct =  i_manager.m_AI->FindAct(_health, _spear, _quentityEnemy);
			if (_numberAct == 0)
			{
				m_state = StateEnemyMachine::ATTACK;
			}
			else if (_numberAct == 1)
			{
				m_state = StateEnemyMachine::RUN;
			}
			else if (_numberAct == 2)
			{
				m_state = StateEnemyMachine::WANDER;
			}
			else
			{
				m_state = StateEnemyMachine::HIDE;
			}

			break;
		}
		case StateEnemyMachine::NOTHING:
		{

			break;
		}
	default:
		break;
	}
}

void EnemyMachine::ActAttack()
{
	
}

void EnemyMachine::ActRun()
{
	// here need add verify direction
	MoveRight();
}

void EnemyMachine::ActWander()
{
	// here need add verify direction
	MoveLeft();
}

void EnemyMachine::ActHide()
{

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