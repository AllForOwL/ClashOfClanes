#include "Knight.h"
#include "GameScene.h"
#include "constants.h"
#include "MapLayer.h"
#include "ManagerComponent.h"
#include "AI.h"

const int CNT_HEALTH_DEFAULT = 100;

Knight::Knight()
{
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Hero/Walk_1.png");
	this->setPosition(GameScene::m_visibleSize.width / 2 - 50, GameScene::m_visibleSize.height / 2);
	this->setZOrder(1);
}

Knight::Knight(std::string i_knight, MapLayer& i_parentMapLayer)
{			
	i_parentMapLayer.addChild(this);

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
	
	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 8,
		GameScene::m_visibleSize.height / this->getContentSize().height / 8);

	m_spear		= true;
	m_health	= CNT_HEALTH_DEFAULT; 
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

			break;
		}
		case StateKnight::RUN:
		{

			break;
		}
		case StateKnight::WANDER:
		{

			break;
		}
		case StateKnight::HIDE:
		{

			break;
		}
		case StateKnight::FIND_ACT:
		{
			int _quentityEnemy = i_manager.m_mapLayer->GetQuentityEnemy(this->getPosition());
			
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

Knight::~Knight()
{
	CCLOG("destructor Knight");
}

/*  GraphicComponent	- тільки малює спрайти 
	PhysicsComponent	- виявлє зіткнення героя
	InputComponent		- приймає діна з клавіатури
	ManagerComponent	- контейнер для цих компонентів
*/