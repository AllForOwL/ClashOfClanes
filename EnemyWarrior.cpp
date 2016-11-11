#include "EnemyWarrior.h"
#include "GameScene.h"
#include "constants.h"
#include "MapLayer.h"
#include "ManagerComponent.h"
#include "AI.h"

const int CNT_SPEED_BOWMAN			= 2;
const int CNT_SPEED_ENEMY_KNIGHT	= 3;

EnemyWarrior::EnemyWarrior()
{

}

EnemyWarrior::EnemyWarrior(std::string i_EnemyWarrior, MapLayer& i_parentMapLayer) : Warrior(i_parentMapLayer)
{			
	if (i_EnemyWarrior == CNT_TYPE_BOWMAN)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Enemy/Bowman.png");
		m_speed = CNT_SPEED_BOWMAN;
	}
	else if (i_EnemyWarrior == CNT_TYPE_ENEMY_KNIGHT)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Enemy/EnemyKnight.png");
		m_speed = CNT_SPEED_ENEMY_KNIGHT;
	}
	else if (i_EnemyWarrior == CNT_TYPE_WIZARD)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Enemy/Wizard.png");
	}
	else if (i_EnemyWarrior == CNT_TYPE_PALADIN)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Enemy/Paladin.png");
	}

	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 8,
		GameScene::m_visibleSize.height / this->getContentSize().height / 8);

	m_state		= StateEnemyWarrior::NOTHING;
}

EnemyWarrior::EnemyWarrior(EnemyWarrior& EnemyWarrior)
{
	
}

/*virtual*/ void EnemyWarrior::Update(ManagerComponent& i_manager)
{
	switch (m_state)
	{
		case StateEnemyWarrior::ATTACK:
		{
			ActAttack();			

			break;
		}
		case StateEnemyWarrior::RUN:
		{
			ActRun();

			break;
		}
		case StateEnemyWarrior::WANDER:
		{
			ActWander();

			break;
		}
		case StateEnemyWarrior::HIDE:
		{
			ActHide();

			break;
		}
		case StateEnemyWarrior::FIND_ACT:
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
				m_state = StateEnemyWarrior::ATTACK;
			}
			else if (_numberAct == 1)
			{
				m_state = StateEnemyWarrior::RUN;
			}
			else if (_numberAct == 2)
			{
				m_state = StateEnemyWarrior::WANDER;
			}
			else
			{
				m_state = StateEnemyWarrior::HIDE;
			}

			break;
		}
		case StateEnemyWarrior::NOTHING:
		{

			break;
		}
	default:
		break;
	}
}

void EnemyWarrior::ActAttack()
{
	
}

void EnemyWarrior::ActRun()
{
	// here need add verify direction
	MoveRight();
}

void EnemyWarrior::ActWander()
{
	// here need add verify direction
	MoveLeft();
}

void EnemyWarrior::ActHide()
{

}

EnemyWarrior::~EnemyWarrior()
{
	CCLOG("destructor EnemyWarrior");
}

/*  GraphicComponent	- тільки малює спрайти 
	PhysicsComponent	- виявлє зіткнення героя
	InputComponent		- приймає діна з клавіатури
	ManagerComponent	- контейнер для цих компонентів
*/