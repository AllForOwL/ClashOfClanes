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
#include "ManagerObjectAndFile.h"
#include "ResourcesFactory.h"

ManagerFactory::ManagerFactory()
{
	
}

ManagerFactory::ManagerFactory(ManagerFactory& i_ManagerFactory)
{
	m_positionBuildFactory = Point::ZERO;
}

void ManagerFactory::LaunchFillRegion(const Factory& i_factory, ManagerComponent& i_manager, int i_typeFactory)
{
	m_positionNewFactory	= i_factory.getPosition();
	m_sizeNewFactory		= i_factory.getBoundingBox().size;

	i_manager.m_mapLayer->FillRegionFromObject(i_manager, i_typeFactory, m_positionNewFactory, m_sizeNewFactory);
	i_manager.m_inputComponent->SetZeroLocation();
}


void ManagerFactory::CreateFactory(ManagerComponent& i_manager, int i_typeFactory)
{
	if (i_typeFactory == CNT_OBJECT_FACTORY_WARRIOR)
	{
		WarriorFactory* _warriorFactory = new WarriorFactory(m_positionBuildFactory, *i_manager.m_mapLayer);
		m_vecFactoryWarrior.push_back(_warriorFactory);
		LaunchFillRegion(*m_vecFactoryWarrior[m_vecFactoryWarrior.size() - 1], i_manager, CNT_OBJECT_FACTORY_WARRIOR);
		i_manager.m_managerObjectAndFile->WriteObjectInFile(CNT_OBJECT_FACTORY_WARRIOR, m_positionBuildFactory, (i_manager.m_mapLayer->getPosition() * -1));
	}
	else
	{
		MachineFactory* _machineFactory = new MachineFactory(m_positionBuildFactory, *i_manager.m_mapLayer);
		m_vecFactoryMachine.push_back(_machineFactory);
		LaunchFillRegion(*m_vecFactoryMachine[m_vecFactoryMachine.size() - 1], i_manager, CNT_OBJECT_FACTORY_MACHINE);
		i_manager.m_managerObjectAndFile->WriteObjectInFile(CNT_OBJECT_FACTORY_MACHINE, m_positionBuildFactory, (i_manager.m_mapLayer->getPosition() * -1));
	}
}

void ManagerFactory::CreateFactoryEnemy(ManagerComponent& i_manager, int i_typeFactory)
{
	if (i_typeFactory == CNT_OBJECT_FACTORY_ENEMY_WARRIOR)
	{
		EnemyWarriorFactory* _enemyWarriorFactory = new EnemyWarriorFactory(m_positionBuildFactory, *i_manager.m_mapLayer);
		m_vecFactoryEnemyWarrior.push_back(_enemyWarriorFactory);
		LaunchFillRegion(*m_vecFactoryEnemyWarrior[m_vecFactoryEnemyWarrior.size() - 1], i_manager, CNT_OBJECT_FACTORY_ENEMY_WARRIOR);
		i_manager.m_managerObjectAndFile->WriteObjectInFile(CNT_OBJECT_FACTORY_ENEMY_WARRIOR, m_positionBuildFactory, (i_manager.m_mapLayer->getPosition() * -1));
	}
	else
	{
		EnemyMachineFactory* _enemyMachineFactory = new EnemyMachineFactory(m_positionBuildFactory, *i_manager.m_mapLayer);
		m_vecFactoryEnemyMachine.push_back(_enemyMachineFactory);
		LaunchFillRegion(*m_vecFactoryEnemyMachine[m_vecFactoryEnemyMachine.size() - 1], i_manager, CNT_OBJECT_FACTORY_ENEMY_MACHINE);
		i_manager.m_managerObjectAndFile->WriteObjectInFile(CNT_OBJECT_FACTORY_ENEMY_MACHINE, m_positionBuildFactory, (i_manager.m_mapLayer->getPosition() * -1));
	}
}

void ManagerFactory::CreateFactoryResources(ManagerComponent& i_manager, int i_typeFactory)
{
	if (i_typeFactory == TYPE_GOLD)
	{
		ResourcesFactory* _resourcesFactory = new ResourcesFactory(m_positionBuildFactory, *i_manager.m_mapLayer, std::string("Factory/FactoryGold.png"));
		m_vecFactoryResources.push_back(_resourcesFactory);
		LaunchFillRegion(*m_vecFactoryResources[m_vecFactoryResources.size() - 1], i_manager, TYPE_GOLD);
		i_manager.m_managerObjectAndFile->WriteObjectInFile(TYPE_GOLD, m_positionBuildFactory, (i_manager.m_mapLayer->getPosition() * -1));
	}
	else if (i_typeFactory == TYPE_OIL)
	{
		ResourcesFactory* _resourcesFactory = new ResourcesFactory(m_positionBuildFactory, *i_manager.m_mapLayer, std::string("Factory/FactoryOil.png"));
		m_vecFactoryResources.push_back(_resourcesFactory);
		LaunchFillRegion(*m_vecFactoryResources[m_vecFactoryResources.size() - 1], i_manager, TYPE_OIL);
		i_manager.m_managerObjectAndFile->WriteObjectInFile(TYPE_OIL, m_positionBuildFactory, (i_manager.m_mapLayer->getPosition() * -1));
	}
}

void ManagerFactory::UpdateAllFactory(ManagerComponent& i_manager)
{
	for (int i = 0; i < m_vecFactoryWarrior.size(); i++)
	{
		m_vecFactoryWarrior[i]->Update(i_manager);
	}

	for (int i = 0; i < m_vecFactoryMachine.size(); i++)
	{
		m_vecFactoryMachine[i]->Update(i_manager);
	}
}

void ManagerFactory::Update(GameScene& i_gameScene, ManagerComponent& i_manager)
{
	switch (m_stateManagerFactory)
	{
		case ManagerFactory::ADD_FACTORY_WARRIOR:
		{
			if (i_manager.m_hero->CheckProductionFactoryWarrior())
			{
				CreateFactory(i_manager, CNT_OBJECT_FACTORY_WARRIOR);
			}
			m_stateManagerFactory = ManagerFactory::NOTHING;

			break;
		}
		case ManagerFactory::ADD_FACTORY_MACHINE:
		{
			if (i_manager.m_hero->CheckProductionFactoryMachine())
			{
				CreateFactory(i_manager, CNT_OBJECT_FACTORY_MACHINE);
			}
			m_stateManagerFactory = ManagerFactory::NOTHING;

			break;
		}
		case ManagerFactory::ADD_FACTORY_ENEMY_WARRIOR:
		{
			CreateFactoryEnemy(i_manager, CNT_OBJECT_FACTORY_ENEMY_WARRIOR);

			m_stateManagerFactory = ManagerFactory::NOTHING;

			break;
		}
		case ManagerFactory::ADD_FACTORY_ENEMY_MACHINE:
		{
			CreateFactoryEnemy(i_manager, CNT_OBJECT_FACTORY_ENEMY_MACHINE);

			m_stateManagerFactory = ManagerFactory::NOTHING;

			break;
		}
		case ManagerFactory::ADD_FACTORY_GOLD:
		{
			CreateFactoryResources(i_manager, TYPE_GOLD);
			
			m_stateManagerFactory = ManagerFactory::NOTHING;

			break;
		}
		case ManagerFactory::ADD_FACTORY_OIL:
		{
			CreateFactoryResources(i_manager, TYPE_OIL);

			m_stateManagerFactory = ManagerFactory::NOTHING;

			break;
		}
		case ManagerFactory::NOTHING:
		{
			UpdateAllFactory(i_manager);

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

/*	Tasks on 03:12:2016
	+ add load from file all classes;
	+ refactoring code;
*/