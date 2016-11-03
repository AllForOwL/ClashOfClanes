#include "ManagerFactory.h"
#include "GameScene.h"
#include "ManagerComponent.h"
#include "WarriorFactory.h"
#include "MachineFactory.h"
#include "HeroGraphicComponent.h"
#include "MapLayer.h"

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
			if (i_manager.m_hero->CheckProductionFactoryWarrior())
			{
				WarriorFactory* _warriorFactory = new WarriorFactory(*i_manager.m_mapLayer);
				Point _positionMap = i_manager.m_mapLayer->getPosition();
				_positionMap.x *= -1;
				_positionMap.y *= -1;
				Point _positionWarrior = Point(GameScene::m_visibleSize.width / 2 + _positionMap.x - 50, GameScene::m_visibleSize.height / 2 + _positionMap.y);
				_warriorFactory->setPosition(_positionWarrior);
				m_vecFactoryWarrior.push_back(_warriorFactory);
			}
			m_stateManagerFactory = ManagerFactory::NOTHING;

			break;
		}
		case ManagerFactory::ADD_FACTORY_MACHINE:
		{
			if (i_manager.m_hero->CheckProductionFactoryMachine())
			{
				MachineFactory* _machineFactory = new MachineFactory(*i_manager.m_mapLayer);
				Point _positionMap = i_manager.m_mapLayer->getPosition();
				_positionMap.x *= -1;
				_positionMap.y *= -1;
				Point _positionMachine = Point(GameScene::m_visibleSize.width / 2 + _positionMap.x - 100, GameScene::m_visibleSize.height / 2 + _positionMap.y);
				_machineFactory->setPosition(_positionMachine);
				m_vecFactoryMachine.push_back(_machineFactory);
			}
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