#include "Knight.h"
#include "GameScene.h"
#include "constants.h"
#include "MapLayer.h"
#include "ManagerComponent.h"
#include "AI.h"

Knight::Knight()
{

} 

Knight::Knight(std::string i_knight, MapLayer& i_parentMapLayer) : Warrior(i_parentMapLayer)
{			
	if (i_knight == CNT_TYPE_KNIGHT_BLACK)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Warrior/black_knight/attack_1.png");
	}
	else if (i_knight == CNT_TYPE_KNIGHT_BRONZE)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Warrior/bronze_knight/attack_1.png");
	}
	else if (i_knight == CNT_TYPE_KNIGHT_SILVER)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Warrior/silver_knight/attack_1.png");
	}

	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 10,
		GameScene::m_visibleSize.height / this->getContentSize().height / 10);

	m_spear		= true;
	m_state		= StateKnight::FIND_ACT;
}

Knight::Knight(Knight& Knight)
{
	
}

/*virtual*/ void Knight::Update(ManagerComponent& i_manager)
{
	switch (m_state)
	{
		case StateKnight::ATTACK:
		{
			ActAttack();			
			m_state = StateKnight::FIND_ACT;

			break;
		}
		case StateKnight::RUN:
		{
			ActRun();
			m_state = StateKnight::FIND_ACT;

			break;
		}
		case StateKnight::WANDER:
		{
			ActWander();
			m_state = StateKnight::FIND_ACT;

			break;
		}
		case StateKnight::HIDE:
		{
			ActHide();
			m_state = StateKnight::FIND_ACT;

			break;
		}
		case StateKnight::FIND_ACT:
		{
			int _quentityEnemy = i_manager.m_mapLayer->GetQuentityEnemy(this->getPosition());
			
			if (_quentityEnemy)
			{
				int b;
				b = 10;
			}

			double _spear = 0.0;
			if (m_spear)
			{
				_spear = 1.0;
			}

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
				m_state = StateKnight::ATTACK;
			}
			else if (_numberAct == 1)
			{
				m_state = StateKnight::RUN;
			}
			else if (_numberAct == 2)
			{
				m_state = StateKnight::WANDER;
			}
			else
			{
				m_state = StateKnight::HIDE;
			}

			break;
		}
		case StateKnight::NOTHING:
		{

			break;
		}
	default:
		break;
	}
}

void Knight::ActAttack()
{
	MoveUp();
}

void Knight::ActRun()
{
	// here need add verify direction
	MoveLeft();
}

void Knight::ActWander()
{
	// here need add verify direction
	MoveRight();
}

void Knight::ActHide()
{
	MoveDown();
}

Knight::~Knight()
{
	CCLOG("destructor Knight");
}

/*  GraphicComponent	- тільки малює спрайти 
	PhysicsComponent	- виявлє зіткнення героя
	InputComponent		- приймає діна з клавіатури
	ManagerComponent	- контейнер для цих компонентів
*/