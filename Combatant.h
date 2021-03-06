#ifndef __COMBATANT_H__
#define __COMBATANT_H__

#include "cocos2d.h"
#include "constants.h"

#include "MapLayer.h"
#include "GraphicComponent.h"
#include "ManagerComponent.h"
#include "AI.h"
#include "AIDirection.h"

USING_NS_CC;

const int CNT_HEALTH_DEFAULT		= 100;
const int CNT_DEFAULT_SPEED			=  1;
const int CNT_QUENTITY_DIRECTION	= 4;
const double CNT_DEFAULT_DAMAGE		= 20.0;
const double CNT_DEFAULT_ARMOR		= 100.0;

class Combatant : public GraphicComponent
{
public:
	enum StateCombatant
	{
		GOES_TO_TARGET,
		GOES_BACK,
		VERIFY_STATUS_POSITION,
		FIND_GOLD,
		FIND_OIL,
		MOVE_FORWARD,
		MOVE_BACK,
		MOVE_RIGHT,
		MOVE_LEFT,
		FIND_ACT,
		ACT_ATTACK,
		ACT_RUN,
		ACT_HIDE,
		NOTHING,
		LISTEN
	};

	Combatant() 
	{
		m_health	= CNT_HEALTH_DEFAULT;
		m_speed		= CNT_DEFAULT_SPEED;
		m_damage	= CNT_DEFAULT_DAMAGE;
		m_armor		= CNT_DEFAULT_ARMOR;

		m_state = StateCombatant::FIND_ACT;

		m_direction.resize(CNT_QUENTITY_DIRECTION);
		std::fill(m_direction.begin(), m_direction.end(), false);
		m_indexDirection = INDEX_DIRECTION_EAST;
		m_direction[m_indexDirection] = true;
	}

	virtual ~Combatant()
	{
		CCLOG("COMBATANT DESTRUCTOR");
	};

	virtual void MoveForward()
	{
		this->setPosition(m_position.forward);
	}

	virtual void MoveBack()
	{
		this->setPosition(m_position.back);
	}

	virtual void MoveRight()
	{
		this->setPosition(m_position.right);
	}

	virtual void MoveLeft()
	{
		this->setPosition(m_position.left);
	}

	int GetActiveDirection()
	{
		for (int i = 0; i < m_direction.size(); i++)
		{
			if (m_direction[i])
			{
				return i;
			}
		}
	}

	void SetStatusPositionForCurrentDirection(ManagerComponent& i_manager)
	{
		if (m_direction[INDEX_DIRECTION_EAST])
		{
			m_position.forward = Point(this->getPositionX() + 1, this->getPositionY());
			m_position.back = Point(this->getPositionX() - 1, this->getPositionY());
			m_position.right = Point(this->getPositionX(), this->getPositionY() - 1);
			m_position.left = Point(this->getPositionX(), this->getPositionY() + 1);
		}
		else if (m_direction[INDEX_DIRECTION_SOUTH])
		{
			m_position.forward	= Point(this->getPositionX(), this->getPositionY() - 1);
			m_position.back		= Point(this->getPositionX(), this->getPositionY() + 1);
			m_position.right	= Point(this->getPositionX() - 1, this->getPositionY());
			m_position.left		= Point(this->getPositionX() + 1, this->getPositionY());
		}
		else if (m_direction[INDEX_DIRECTION_WEST])
		{
			m_position.forward	= Point(this->getPositionX() - 1, this->getPositionY());
			m_position.back		= Point(this->getPositionX() + 1, this->getPositionY());
			m_position.right	= Point(this->getPositionX(), this->getPositionY() + 1);
			m_position.left		= Point(this->getPositionX(), this->getPositionY() - 1);
		}
		else if (m_direction[INDEX_DIRECTION_NORTH])
		{
			m_position.forward	= Point(this->getPositionX(), this->getPositionY() + 1);
			m_position.back		= Point(this->getPositionX(), this->getPositionY() - 1);
			m_position.right	= Point(this->getPositionX() + 1, this->getPositionY());
			m_position.left		= Point(this->getPositionX() - 1, this->getPositionY());
		}

		m_statusPosition.forward	= i_manager.m_mapLayer->StatusCells(m_position.forward, m_typeObject);
		m_statusPosition.back		= i_manager.m_mapLayer->StatusCells(m_position.back, m_typeObject);
		m_statusPosition.right		= i_manager.m_mapLayer->StatusCells(m_position.right, m_typeObject);
		m_statusPosition.left		= i_manager.m_mapLayer->StatusCells(m_position.left, m_typeObject);
	}

	void UpdateDirection(ManagerComponent& i_manager)
	{
		m_actWander = i_manager.m_AIDirection->FindAct(m_statusPosition.forward, m_statusPosition.back,
			m_statusPosition.right, m_statusPosition.left);

		if (m_actWander == CNT_DIRECTION_RIGHT)
		{
			if (m_indexDirection != INDEX_DIRECTION_NORTH)
			{
				m_direction[m_indexDirection] = false;
				m_direction[++m_indexDirection] = true;
			}
			else
			{
				m_direction[m_indexDirection] = false;
				m_indexDirection = INDEX_DIRECTION_EAST;
				m_direction[m_indexDirection] = true;
			}
			m_state = StateCombatant::MOVE_RIGHT;
		}
		else if (m_actWander == CNT_DIRECTION_LEFT)
		{
			if (m_indexDirection != INDEX_DIRECTION_EAST)
			{
				m_direction[m_indexDirection] = false;
				m_direction[--m_indexDirection] = true;
			}
			else
			{
				m_direction[m_indexDirection] = false;
				m_indexDirection = INDEX_DIRECTION_NORTH;
				m_direction[m_indexDirection] = true;
			}
			m_state = StateCombatant::MOVE_LEFT;
		}
		else if (m_actWander == CNT_DIRECTION_BACK)
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

			m_state = StateCombatant::MOVE_BACK;
		}
		else
		{
			m_state = StateCombatant::MOVE_FORWARD;
		}
	}

	virtual void Update(ManagerComponent& i_manager) = 0;

protected:
	int		m_health;
	double	m_damage;
	double	m_armor;
	int		m_speed;

	// member for AI
	struct Position
	{
		Point forward;
		Point back;
		Point right;
		Point left;
	};

	struct StatusPosition
	{
		double forward;
		double back;
		double right;
		double left;
	};

	std::vector<bool>	m_direction;
	Position			m_position;
	StatusPosition		m_statusPosition;
	int					m_indexDirection;
	int					m_actWander;
	StateCombatant		m_state;
	int					m_typeObject;
};

#endif