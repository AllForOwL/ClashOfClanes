#ifndef __HERO_GRAPHIC_COMPONENT_H__
#define __HERO_GRAPHIC_COMPONENT_H__

#include "cocos2d.h"
#include "GraphicComponent.h"

USING_NS_CC;

class GameScene;

class HeroGraphicComponent : public GraphicComponent
{
public:

	enum StateHero
	{
		WALK,
		NOTHING
	};

	HeroGraphicComponent();
	HeroGraphicComponent(GameScene& i_parentGameScene);
	HeroGraphicComponent(HeroGraphicComponent& heroGraphiComponent);

	~HeroGraphicComponent();

	virtual void Update(ManagerComponent& i_manager);

	bool CheckProductionArcher();
	bool CheckProductionTank();
	bool CheckProductionCar();
	bool CheckProductionFactoryMachine();
	bool CheckProductionFactoryWarrior();

	bool CheckToGoTarget(ManagerComponent& i_manager);

private:

	int			m_coin;
	StateHero	m_stateHero;
	Rect		m_rectHero;
	Vec2		m_positionTarget;

	std::vector<Point> m_vecWayWalkHero;
};

#endif