#include "ManagerFactory.h"
#include "GameScene.h"
#include "ManagerComponent.h"
#include "WarriorFactory.h"
#include "MachineFactory.h"

ManagerFactory::ManagerFactory()
{
	
}

ManagerFactory::ManagerFactory(ManagerFactory& i_ManagerFactory)
{

}

void ManagerFactory::Update(GameScene& i_gameScene, ManagerComponent& i_manager)
{
	switch (m_stateManagerFactory)
	{
		case ManagerFactory::ADD_FACTORY_WARRIOR:
		{
			MachineFactory* _machineFactory = new MachineFactory(i_gameScene);
			m_vecFactoryMachine.push_back(_machineFactory);

			break;
		}
		case ManagerFactory::ADD_FACTORY_MACHINE:
		{
			WarriorFactory* _warriorFactory = new WarriorFactory(i_gameScene);
			m_vecFactoryWarrior.push_back(_warriorFactory);

			break;
		}
		case ManagerFactory::NOTHING:
		{
			for (int i = 0; i < m_vecFactoryMachine.size(); i++)
			{
				m_vecFactoryMachine[i]->Update(i_manager);
			}

			for (int i = 0; i < m_vecFactoryWarrior.size(); i++)
			{
				m_vecFactoryWarrior[i]->Update(i_manager);
			}

			break;
		}
	default:
		break;
	}
}

void ManagerFactory::SetState(StateManagerFactory& i_state)
{
	m_stateManagerFactory = i_state;
}

ManagerFactory::~ManagerFactory()
{

}