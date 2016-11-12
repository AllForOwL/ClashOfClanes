#ifndef __WARRIOR_H__
#define __WARRIOR_H__

#include "cocos2d.h"
#include "GraphicComponent.h"
#include "MapLayer.h"
#include "GameScene.h"

class ManagerComponent;

const int CNT_HEALTH_DEFAULT	= 100;
const int CNT_DEFAULT_SPEED		=  1;
const double CNT_DEFAULT_DAMAGE = 20.0;
const double CNT_DEFAULT_ARMOR	= 100.0;

class Warrior : public GraphicComponent
{
public:
	Warrior(){};
	Warrior(MapLayer& i_parentMapLayer)
	{
		i_parentMapLayer.addChild(this);

		m_health	= CNT_HEALTH_DEFAULT;
		m_speed		= CNT_DEFAULT_SPEED;
		m_damage	= CNT_DEFAULT_DAMAGE;
		m_armor		= CNT_DEFAULT_ARMOR;
	}
	~Warrior(){};

	virtual void MoveRight()
	{
		this->setPositionX(this->getPositionX() + m_speed);
	}
	virtual void MoveLeft()
	{
		this->setPositionX(this->getPositionX() - m_speed);
	}
	virtual void MoveUp()
	{
		this->setPositionY(this->getPositionY() + m_speed);
	}
	virtual void MoveDown()
	{
		this->setPositionY(this->getPositionY() - m_speed);
	}

	virtual void Update(ManagerComponent& i_manager) = 0;

protected:
	int		m_health;
	double	m_damage;
	double	m_armor;
	int		m_speed;
};

#endif