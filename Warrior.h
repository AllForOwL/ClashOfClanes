#ifndef __WARRIOR_H__
#define __WARRIOR_H__

#include "cocos2d.h"

#include "Combatant.h"

USING_NS_CC;

class Warrior : public Combatant
{
public:
	Warrior(){};
	Warrior(Point i_positionVisible, MapLayer& i_parentMapLayer, std::string i_fileWarrior)
	{
		i_parentMapLayer.addChild(this);
		this->initWithFile(CNT_PATH_TO_RESOURCES + i_fileWarrior);
		this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 10,
			GameScene::m_visibleSize.height / this->getContentSize().height / 10);

		LoadProperties(i_positionVisible);

		m_state = StateCombatant::NOTHING;
	}
	~Warrior(){};

	void SetTypeObject(int i_typeObject)
	{
		m_typeObject	= i_typeObject;
	}

private:

};

#endif