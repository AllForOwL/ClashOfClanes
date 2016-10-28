#include "ManagerMachine.h"
#include "GameScene.h"
#include "ManagerComponent.h"
#include "WarriorFactory.h"
#include "Car.h"
#include "Tank.h"

ManagerMachine::ManagerMachine()
{
	
}

ManagerMachine::ManagerMachine(ManagerMachine& i_managerMachine)
{

}

void ManagerMachine::Update(GameScene& i_gameScene, ManagerComponent& i_manager)
{
	switch (m_stateManagerMachine)
	{
		case ManagerMachine::ADD_TANK:
		{
			Tank* _tank = new Tank(i_gameScene);
			m_vecMachineTank.push_back(_tank);
			
			m_stateManagerMachine = StateManagerMachine::NOTHING;

			break;
		}
		case ManagerMachine::ADD_CAR:
		{
			Car* _car = new Car(i_gameScene);
			m_vecMachineCar.push_back(_car);
			
			m_stateManagerMachine = StateManagerMachine::NOTHING;

			break;
		}
		case ManagerMachine::NOTHING:
		{
			

			break;
		}
	default:
		break;
	}
}

void ManagerMachine::SetState(StateManagerMachine& i_state)
{
	m_stateManagerMachine = i_state;
}

ManagerMachine::~ManagerMachine()
{

}