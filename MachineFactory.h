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
		WORKING,
		LISTEN,
		NOTHING
	};

	MachineFactory();
	MachineFactory(Point i_positionVisible, Point i_positionOrigin, MapLayer& i_mapLayer);
	MachineFactory(MachineFactory& i_machineFactory);

	~MachineFactory();

	virtual void Update(ManagerComponent& i_manager);

	StateFactoryMachine& GetState();
	void SetState(StateFactoryMachine& i_state);

	void LoadNameForSprites();

	bool DetermineCommand();

private:
	ManagerMachine::StateManagerMachine m_stateManagerMachine;
	StateFactoryMachine					m_stateMachine;
};

#endif