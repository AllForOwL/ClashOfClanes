#include "ResourcesFactory.h"
#include "ManagerComponent.h"
#include "HeroGraphicComponent.h"
#include "GameScene.h"
#include "ManagerArmy.h"
#include "HeroInputComponent.h"
#include "MapLayer.h"

const int CNT_TIME_FOR_COMPLETE_GOLD	= 800;
const int CNT_TIME_FOR_COMPLETE_OIL		= 1000;

const int COIN_PRODUCTION_FACTORY = 100;
const int OIL_PRODUCTION_FACTORY  = 70;

ResourcesFactory::ResourcesFactory()
{

}

ResourcesFactory::ResourcesFactory(Point i_positionVisible, MapLayer& i_mapLayer, std::string i_filename) : Factory(i_positionVisible, 
																													i_mapLayer, 
																													i_filename)
{
	m_stateResources	= StateFactoryResources::NOTHING;
}
ResourcesFactory::ResourcesFactory(ResourcesFactory& i_ResourcesFactory)
{

}

void ResourcesFactory::SetTypeResources(int i_type)
{
	if (i_type == TYPE_GOLD)
	{
		m_stockGold = rand() % 1000 + 500;
		m_stockOil = 0;
		m_stateResources = StateFactoryResources::START_GOLD;
	}
	else if (i_type == TYPE_OIL)
	{
		m_stockOil = rand() % 1000 + 500;
		m_stockGold = 0;
		m_stateResources = StateFactoryResources::START_OIL;
	}
}

/*virtual*/ void ResourcesFactory::Update(ManagerComponent& i_manager)
{
	switch (m_stateResources)
	{
		case StateFactoryResources::START_GOLD:
		{
			if (m_stockGold > COIN_PRODUCTION_FACTORY)
			{
				m_stateResources = StateFactoryResources::WORKING_GOLD;
				m_timeForComplete = CNT_TIME_FOR_COMPLETE_GOLD;
			}
			else
			{
				m_stateResources = StateFactoryResources::NOTHING;
			}

			break;
		}
		case StateFactoryResources::START_OIL:
		{
			if (m_stockOil > OIL_PRODUCTION_FACTORY)
			{
				m_stateResources = StateFactoryResources::WORKING_OIL;
				m_timeForComplete = CNT_TIME_FOR_COMPLETE_OIL;
			}
			else
			{
				m_stateResources = StateFactoryResources::NOTHING;
			}
			
			break;
		}
		case StateFactoryResources::WORKING_GOLD:
		{
			if (isComplete())
			{
				i_manager.m_hero->IncreaseCoin(COIN_PRODUCTION_FACTORY);
				m_stockGold -= COIN_PRODUCTION_FACTORY;
				m_stateResources = StateFactoryResources::START_GOLD;
			}

			break;
		}
		case StateFactoryResources::WORKING_OIL:
		{
			if (isComplete())
			{
				i_manager.m_hero->IncreaseOil(OIL_PRODUCTION_FACTORY);
				m_stockOil -= OIL_PRODUCTION_FACTORY;
				m_stateResources = StateFactoryResources::START_OIL;
			}

			break;
		}
		case StateFactoryResources::NOTHING:
		{
		
			break;
		}
	default:
		break;
	}
}

ResourcesFactory::~ResourcesFactory()
{

}