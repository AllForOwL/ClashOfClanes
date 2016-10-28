#ifndef __HERO_GRAPHIC_COMPONENT_H__
#define __HERO_GRAPHIC_COMPONENT_H__

#include "cocos2d.h"
#include "GraphicComponent.h"

USING_NS_CC;

class GameScene;

class HeroGraphicComponent : public GraphicComponent
{
public:
	HeroGraphicComponent();
	HeroGraphicComponent(GameScene& i_parentGameScene);
	HeroGraphicComponent(HeroGraphicComponent& heroGraphiComponent);

	~HeroGraphicComponent();

	virtual void Update(GameScene& i_gameScene);

	int GetCoin() const;

private:

	int m_coin;
};

#endif