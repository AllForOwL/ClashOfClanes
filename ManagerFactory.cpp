#include "ManagerFactory.h"
#include "GameScene.h"
#include "ManagerComponent.h"
#include "WarriorFactory.h"
#include "MachineFactory.h"
#include "HeroGraphicComponent.h"
#include "MapLayer.h"
#include "HeroInputComponent.h"
#include "EnemyWarriorFactory.h"
#include "EnemyMachineFactory.h"

ManagerFactory::ManagerFactory()
{
	
}

ManagerFactory::ManagerFactory(ManagerFactory& i_ManagerFactory)
{
	m_positionBuildFactory = Point::ZERO;
}

void ManagerFactory::Update(GameScene& i_gameScene, ManagerComponent& i_manager)
{
	switch (m_stateManagerFactory)
	{
		case ManagerFactory::ADD_FACTORY_WARRIOR:
		{
			if (i_manager.m_hero->CheckProductionFactoryWarrior())
			{
				WarriorFactory* _warriorFactory = new WarriorFactory(m_positionBuildFactory, *i_manager.m_mapLayer);
				m_vecFactoryWarrior.push_back(_warriorFactory);

				i_manager.m_inputComponent->SetZeroLocation();
			}
			m_stateManagerFactory = ManagerFactory::NOTHING;

			break;
		}
		case ManagerFactory::ADD_FACTORY_MACHINE:
		{
			if (i_manager.m_hero->CheckProductionFactoryMachine())
			{
				MachineFactory* _machineFactory = new MachineFactory(m_positionBuildFactory, *i_manager.m_mapLayer);
				m_vecFactoryMachine.push_back(_machineFactory);

				i_manager.m_inputComponent->SetZeroLocation();
			}
			m_stateManagerFactory = ManagerFactory::NOTHING;

			break;
		}
		case ManagerFactory::ADD_FACTORY_ENEMY_WARRIOR:
		{
			EnemyWarriorFactory* _enemyWarriorFactory = new EnemyWarriorFactory(m_positionBuildFactory, *i_manager.m_mapLayer);
			m_vecFactoryEnemyWarrior.push_back(_enemyWarriorFactory);

			i_manager.m_inputComponent->SetZeroLocation();

			m_stateManagerFactory = ManagerFactory::NOTHING;

			break;
		}
		case ManagerFactory::ADD_FACTORY_ENEMY_MACHINE:
		{
			EnemyMachineFactory* _enemyMachineFactory = new EnemyMachineFactory(m_positionBuildFactory, *i_manager.m_mapLayer);
			m_vecFactoryEnemyMachine.push_back(_enemyMachineFactory);

			i_manager.m_inputComponent->SetZeroLocation();

			m_stateManagerFactory = ManagerFactory::NOTHING;

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

			for (int i = 0; i < m_vecFactoryEnemyWarrior.size(); i++)
			{
				m_vecFactoryEnemyWarrior[i]->Update(i_manager);
			}

			for (int i = 0; i < m_vecFactoryEnemyMachine.size(); i++)
			{
				m_vecFactoryEnemyMachine[i]->Update(i_manager);
			}

			break;
		}
	default:
		break;
	}
}

Point ManagerFactory::GetPositionBuildFactory() const
{
	return m_positionBuildFactory;
}

void ManagerFactory::SetPositionBuildFactory(Point i_point)
{
	m_positionBuildFactory = i_point;
}

void ManagerFactory::SetState(StateManagerFactory& i_state)
{
	m_stateManagerFactory = i_state;
}

ManagerFactory::~ManagerFactory()
{

}