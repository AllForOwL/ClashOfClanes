#include "Knight.h"
#include "GameScene.h"
#include "constants.h"
#include "MapLayer.h"
#include "ManagerComponent.h"
#include "AI.h"

const int CNT_DIRECTION_FORWARD = 0;
const int CNT_DIRECTION_BACK	= 1;
const int CNT_DIRECTION_RIGHT	= 2;
const int CNT_DIRECTION_LEFT	= 3;

const int INDEX_DIRECTION_EAST	= 0;
const int INDEX_DIRECTION_SOUTH	= 1;
const int INDEX_DIRECTION_WEST	= 2;
const int INDEX_DIRECTION_NORTH	= 3;

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
	
	m_direction.resize(4);	// 4 - quentity directions
	std::fill(m_direction.begin(), m_direction.end(), false);
	m_indexDirection				= INDEX_DIRECTION_EAST;
	m_direction[m_indexDirection]	= true;
}

Knight::Knight(Knight& Knight)
{
	
}

void Knight::SetStatusPositionForCurrentDirection(ManagerComponent& i_manager)
{
	if (m_direction[INDEX_DIRECTION_EAST])
	{
		m_position.forward	= Point(this->getPositionX() + 1,	this->getPositionY());
		m_position.back		= Point(this->getPositionX() - 1,	this->getPositionY());
		m_position.right	= Point(this->getPositionX(),		this->getPositionY() - 1);
		m_position.left		= Point(this->getPositionX(),		this->getPositionY() + 1);
	}
	else if (m_direction[INDEX_DIRECTION_SOUTH])
	{
		m_position.forward	= Point(this->getPositionX(),		this->getPositionY() - 1);
		m_position.back		= Point(this->getPositionX(),		this->getPositionY() + 1);
		m_position.right	= Point(this->getPositionX() - 1,	this->getPositionY());
		m_position.left		= Point(this->getPositionX() + 1,	this->getPositionY());
	}
	else if (m_direction[INDEX_DIRECTION_WEST])
	{
		m_position.forward	= Point(this->getPositionX() - 1,	this->getPositionY());
		m_position.back		= Point(this->getPositionX() + 1,	this->getPositionY());
		m_position.right	= Point(this->getPositionX(),		this->getPositionY() + 1);
		m_position.left		= Point(this->getPositionX(),		this->getPositionY() - 1);
	}
	else if (m_direction[INDEX_DIRECTION_NORTH])
	{
		m_position.forward	= Point(this->getPositionX(),		this->getPositionY() + 1);
		m_position.back		= Point(this->getPositionX(),		this->getPositionY() - 1);
		m_position.right	= Point(this->getPositionX() + 1,	this->getPositionY());
		m_position.left		= Point(this->getPositionX() - 1,	this->getPositionY());
	}

	m_statusPosition.forward	= i_manager.m_mapLayer->StatusCells(m_position.forward);
	m_statusPosition.back		= i_manager.m_mapLayer->StatusCells(m_position.back);
	m_statusPosition.right		= i_manager.m_mapLayer->StatusCells(m_position.right);
	m_statusPosition.left		= i_manager.m_mapLayer->StatusCells(m_position.left);
}

void Knight::UpdateDirection(ManagerComponent& i_manager)
{
	m_actWander.previous = m_actWander.current;
	m_actWander.current = i_manager.m_AI->FindActWander(m_statusPosition.forward, m_statusPosition.back,
		m_statusPosition.right, m_statusPosition.left);
	

	if (m_actWander.current == CNT_DIRECTION_RIGHT)
	{
		if (m_indexDirection != INDEX_DIRECTION_NORTH)
		{
			m_direction[m_indexDirection]	= false;
			m_direction[++m_indexDirection] = true;
		}
		else
		{
			m_direction[m_indexDirection]	= false;
			m_indexDirection				= INDEX_DIRECTION_EAST;
			m_direction[m_indexDirection]	= true;
		}
		m_state = StateKnight::MOVE_RIGHT;
	}
	else if (m_actWander.current == CNT_DIRECTION_LEFT)
	{
		if (m_indexDirection != INDEX_DIRECTION_EAST)
		{
			m_direction[m_indexDirection]	= false;
			m_direction[--m_indexDirection] = true;
		}
		else
		{
			m_direction[m_indexDirection]	= false;
			m_indexDirection				= INDEX_DIRECTION_NORTH;
			m_direction[m_indexDirection]	= true;
		}
		m_state = StateKnight::MOVE_LEFT;
	}
	else if (m_actWander.current == CNT_DIRECTION_BACK)
	{
		m_direction[m_indexDirection] = false;
		if (m_indexDirection >= 2)
		{
			m_indexDirection -= 2;
		}
		else
		{
			m_indexDirection += 2;
		}
		m_direction[m_indexDirection] = true;

		m_state = StateKnight::MOVE_BACK;
	}
	else
	{
		m_state = StateKnight::MOVE_FORWARD;
	}
}

/*virtual*/ void Knight::Update(ManagerComponent& i_manager)
{
	switch (m_state)
	{
		case StateKnight::MOVE_FORWARD:
		{
			MoveForward();
			m_state = StateKnight::FIND_ACT;
			break;
		}
		case StateKnight::MOVE_BACK:
		{
			MoveBack();
			m_state = StateKnight::FIND_ACT;
			break;
		}
		case StateKnight::MOVE_RIGHT:
		{
			MoveRight();
			m_state = StateKnight::FIND_ACT;
			break;
		}
		case StateKnight::MOVE_LEFT:
		{
			MoveLeft();
			m_state = StateKnight::FIND_ACT;
			break;
		}
		case StateKnight::FIND_ACT:
		{
			SetStatusPositionForCurrentDirection(i_manager);
			UpdateDirection(i_manager);

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

void Knight::MoveForward()
{
	this->setPosition(m_position.forward);
}

void Knight::MoveBack()
{
	this->setPosition(m_position.back);
}

void Knight::MoveRight()
{
	this->setPosition(m_position.right);
}

void Knight::MoveLeft()
{
	this->setPosition(m_position.left);
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