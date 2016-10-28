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

	virtual void Update(ManagerComponent& i_manager);

	bool CheckProductionArcher();
	bool CheckProductionTank();
	bool CheckProductionCar();

private:

	int m_coin;
};

#endif