#ifndef __MACHINE_FACTORY_H__
#define __MACHINE_FACTORY_H__

#include "cocos2d.h"
#include "Factory.h"
#include "ManagerMachine.h"

USING_NS_CC;

class MachineFactory : public Factory
{
public:

	enum StateFactoryMachine
	{
		START_TANK,
		START_CAR,
		WORKING,
		NOTHING
	};

	MachineFactory();
	MachineFactory(GameScene& i_parentGameScene);
	MachineFactory(MachineFactory& i_machineFactory);

	~MachineFactory();

	virtual void Update(ManagerComponent& i_manager);

	bool isComplete();

private:
	ManagerMachine::StateManagerMachine m_stateManagerMachine;
	StateFactoryMachine					m_stateMachine;
	int									m_timeForCompleteMachine;
	std::chrono::time_point<std::chrono::system_clock> m_startSecond;

	Vec2	m_locationTouch;
	Rect	m_rectFactory;

};

#endif