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
		SEARCH_WAY,
		WALK,
		NOTHING,
		LISTEN
	};

	HeroGraphicComponent();
	HeroGraphicComponent(MapLayer& i_parentMapLayer);
	HeroGraphicComponent(HeroGraphicComponent& heroGraphiComponent);

	~HeroGraphicComponent();

	virtual void Update(ManagerComponent& i_manager);

	bool TouchOnHero(ManagerComponent& i_manager);

	bool GoToTouchMouse(ManagerComponent& i_manager);
	void NeedShowMenu(ManagerComponent& i_manager);
	void LoadNameSprites();


	bool CheckProductionKnightBlack();
	bool CheckProductionKnightBronze();
	bool CheckProductionKnightSilver();
	bool CheckProductionTank();
	bool CheckProductionCar();
	bool CheckProductionFactoryMachine();
	bool CheckProductionFactoryWarrior();
	bool CheckToGoTarget(ManagerComponent& i_manager);

private:
	std::vector<std::vector<int>> m_mapCoordinate;

	int			m_coin;
	StateHero	m_stateHero;
	Rect		m_rectHero;
	Vec2		m_positionTarget;

	std::vector<Point>	m_vecWayWalkHero;
	int					m_iterInWayWalk;

	bool				m_loadProperties;
};

#endif