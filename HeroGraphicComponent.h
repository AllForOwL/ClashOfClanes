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
		SEARCH_WAY_TO_RESOURCES,
		GO_TO_RESOURCES,
		COME_AGAIN,
		NOTHING,
		LISTEN
	};

	HeroGraphicComponent();
	HeroGraphicComponent(MapLayer& i_parentMapLayer);
	HeroGraphicComponent(HeroGraphicComponent& heroGraphiComponent);

	~HeroGraphicComponent();

	virtual void Update(ManagerComponent& i_manager);

	virtual void ShowMenu();

	int GetCoin() const;
	int GetOil() const;

	bool RunSearchWay(ManagerComponent& i_manager);

	bool TouchOnHero(ManagerComponent& i_manager);

	bool GoToTouchMouse(ManagerComponent& i_manager);
	void NeedShowMenu(ManagerComponent& i_manager);
	void LoadNameSprites();

	Point GetPositionBuildFactory() const;

	Point GetPositionGold() const;
	Point GetPositionOil() const;

	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();

	void IncreaseCoin(int i_value);
	void IncreaseOil(int i_value);

	void ReloadPosition();

	bool DetermineCommand();

	bool CheckProductionFactoryGold();
	bool CheckProductionFactoryOil();

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
	int			m_oil;
	StateHero	m_stateHero;
	Rect		m_rectHero;
	Vec2		m_positionTarget;

	std::vector<Point>	m_vecWayWalkHero;
	int					m_iterInWayWalk;

	bool				m_loadProperties;

	std::string m_textMessage;
};

#endif