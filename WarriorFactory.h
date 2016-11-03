#ifndef __WARRIOR_FACTORY_H__
#define __WARRIOR_FACTORY_H__

#include "cocos2d.h"
#include "Factory.h"
#include "ManagerArmy.h"

USING_NS_CC;

class MapLayer;

class WarriorFactory : public Factory
{
public:

	enum StateFactoryWarrior
	{
		START_KNIGHT_BLACK,
		START_KNIGHT_BRONZE,
		START_KNIGHT_SILVER,
		WORKING,
		LISTEN,
		NOTHING
	};

	WarriorFactory();
	WarriorFactory(MapLayer& i_mapLayer);
	WarriorFactory(WarriorFactory& i_warriorFactory);

	~WarriorFactory();

	virtual void Update(ManagerComponent& i_manager);

	bool isComplete();

	StateFactoryWarrior& GetStateWarrior();

	void SetState(StateFactoryWarrior& i_stateWarrior);

	void LoadSprites();
	void LoadNameForSprites();
	void ShowMenu();
	void HideMenu();
	
	bool DetermineCommand();
private:
	std::chrono::time_point<std::chrono::system_clock> m_startSecond;
	int					m_timeForCompleteWarrior;
	StateFactoryWarrior m_stateWarrior;
	ManagerArmy::StateManagerArmy m_stateTypeAddWarrior;
	Vec2				m_locationTouch;
	Rect				m_rectFactory;

	std::vector<std::string>	m_vecNameForSprites;
	std::vector<Sprite*>		m_vecSpritesForFactoryWarrior;
	std::vector<Rect>			m_rectForSpritesWarrior;
};

#endif