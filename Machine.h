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

	virtual void Update(ManagerComponent& i_manager) = 0;
};

#endif