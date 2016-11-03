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
	MachineFactory(MapLayer& i_mapLayer);
	MachineFactory(MachineFactory& i_machineFactory);

	~MachineFactory();

	virtual void Update(ManagerComponent& i_manager);

	bool isComplete();

	StateFactoryMachine& GetState();
	void SetState(StateFactoryMachine& i_state);

	void LoadNameForSprites();
	void LoadSprites();
	
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
};

#endif