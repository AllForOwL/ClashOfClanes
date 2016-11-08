#ifndef __MACHINE_FACTORY_H__
#define __MACHINE_FACTORY_H__

#include "cocos2d.h"
#include "Factory.h"
#include "ManagerMachine.h"

USING_NS_CC;

class MapLayer;

class MachineFactory : public Factory
{
public:

	enum StateFactoryMachine
	{
		START_TANK,
		START_CAR,
		WORKING,
		LISTEN,
		NOTHING
	};

	MachineFactory();
	MachineFactory(Point i_positionVisible, MapLayer& i_mapLayer);
	MachineFactory(MachineFactory& i_machineFactory);

	~MachineFactory();

	virtual void Update(ManagerComponent& i_manager);

	bool isComplete();

	StateFactoryMachine& GetState();
	void SetState(StateFactoryMachine& i_state);

	void LoadNameForSprites();
	void LoadSprites();
	void LoadPositionMachine();

	bool DetermineCommand();

	void ShowMenu();
	void HideMenu();

private:
	ManagerMachine::StateManagerMachine m_stateManagerMachine;
	StateFactoryMachine					m_stateMachine;
	int									m_timeForCompleteMachine;
	std::chrono::time_point<std::chrono::system_clock> m_startSecond;

	Vec2	m_locationTouch;
	Rect	m_rectFactory;

	std::vector<std::string>	m_vecNameForSprites;
	std::vector<Sprite*>		m_vecSpritesForFactoryMachine;
	std::vector<Rect>			m_rectForSpritesMachine;
	
	std::vector<Point>	m_vecPositionMachine;
	int					m_numberMachineComplete;
	Point				m_positionOrigin;
	Point				m_positionVisible;
	Point				m_positionOriginWithVisible;

	Rect	m_rectFactoryOrigin;
	Rect	m_rectFactoryVisible;
	Rect	m_rectFactoryOriginWithVisible;

};

#endif