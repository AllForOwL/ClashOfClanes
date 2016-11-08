#include "ManagerMachine.h"
#include "GameScene.h"
#include "ManagerComponent.h"
#include "WarriorFactory.h"
#include "Car.h"
#include "Tank.h"
#include "MapLayer.h"

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
			Tank* _tank = new Tank(*i_manager.m_mapLayer);
			_tank->setPosition(m_pointBuildMachine);
			m_vecMachineTank.push_back(_tank);
			
			m_stateManagerMachine = StateManagerMachine::NOTHING;

			break;
		}
		case ManagerMachine::ADD_CAR:
		{
			Car* _car = new Car(i_gameScene);
			_car->setPosition(m_pointBuildMachine);
			m_vecMachineCar.push_back(_car);
			
			m_stateManagerMachine = StateManagerMachine::NOTHING;

			break;
		}
		case ManagerMachine::NOTHING:
		{
			if (m_vecMachineCar.size())
			{
				for (int i = 0; i < m_vecMachineCar.size(); i++)
				{
					m_vecMachineCar[i]->Update(i_manager);
				}
			}
			
			if (m_vecMachineTank.size())
			{
				for (int i = 0; i < m_vecMachineTank.size(); i++)
				{
					m_vecMachineTank[i]->Update(i_manager);
				}
			}

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

void ManagerMachine::SetPositionForMachine(Point i_pointBuildMachine)
{
	m_pointBuildMachine = i_pointBuildMachine;
}

ManagerMachine::~ManagerMachine()
{

}