#include "ManagerFactory.h"
#include "GameScene.h"
#include "ManagerComponent.h"
#include "WarriorFactory.h"
#include "MachineFactory.h"
#include "HeroGraphicComponent.h"
#include "MapLayer.h"
#include "HeroInputComponent.h"

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
				MachineFactory* _machineFactory = new MachineFactory(*i_manager.m_mapLayer);
				Point _positionMap = i_manager.m_mapLayer->getPosition();
				_positionMap.x *= -1;
				_positionMap.y *= -1;
				_positionMap.x += m_positionBuildFactory.x;
				_positionMap.y += m_positionBuildFactory.y;
				Point _positionMachine = Point(_positionMap);
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