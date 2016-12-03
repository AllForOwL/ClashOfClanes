#ifndef __MACHINE_H__
#define __MACHINE_H__

#include "cocos2d.h"
#include "Combatant.h"

USING_NS_CC;

class ManagerComponent;

class Machine : public Combatant
{
public:
	Machine(){};
	Machine(Point i_positionVisible, MapLayer& i_parentMapLayer, std::string i_fileMachine)
	{
		i_parentMapLayer.addChild(this);
		this->initWithFile(CNT_PATH_TO_RESOURCES + i_fileMachine);
		this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 13,
			GameScene::m_visibleSize.height / this->getContentSize().height / 13);
		LoadProperties(i_positionVisible, i_parentMapLayer.getPosition());

		m_state = StateCombatant::NOTHING;
	};
	~Machine(){};

	virtual void LoadProperties(Point i_positionVisible, Point i_positionOrigin)
	{
		m_positionVisible = i_positionVisible;
		m_positionOrigin = i_positionOrigin;

		if (m_positionOrigin.x < 0)
		{
			m_positionOrigin.x *= (-1);
		}
		if (m_positionOrigin.y < 0)
		{
			m_positionOrigin.y *= (-1);

		}

		m_locationTouch = Point::ZERO;

		Rect _box = this->getBoundingBox();

		// calculate RectOrigin(system coordinate all MapLayer)
		m_rectOrigin = Rect(this->getBoundingBox().getMinX() + m_positionOrigin.x, this->getBoundingBox().getMinY() + m_positionOrigin.y,
			this->getBoundingBox().size.width, this->getBoundingBox().size.height);
		// calculate RectVisible(system coordinate visible MapLayer)
		m_rectVisible = Rect(this->getBoundingBox().getMinX() + m_positionVisible.x, this->getBoundingBox().getMinY() + m_positionVisible.y,
			this->getBoundingBox().size.width, this->getBoundingBox().size.height);

		m_rectOriginWithVisible = Rect(this->getBoundingBox().getMinX() + m_positionOrigin.x + m_positionVisible.x,
			this->getBoundingBox().getMinY() + m_positionOrigin.y + m_positionVisible.y,
			this->getBoundingBox().size.width, this->getBoundingBox().size.height
			);

		m_numberComplete = 0;

		m_positionOriginWithVisible = m_positionOrigin + m_positionVisible;
		this->setPosition(m_positionVisible);
	}

	virtual void Update(ManagerComponent& i_manager) = 0;
};

#endif