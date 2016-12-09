#include "ResourcesFactory.h"
#include "ManagerComponent.h"
#include "HeroGraphicComponent.h"
#include "GameScene.h"
#include "ManagerArmy.h"
#include "HeroInputComponent.h"
#include "MapLayer.h"

const int CNT_TIME_FOR_COMPLETE_KNIGHT_BLACK	= 10;
const int CNT_TIME_FOR_COMPLETE_KNIGHT_BRONZE	= 15;
const int CNT_TIME_FOR_COMPLETE_KNIGHT_SILVER	= 20;

const int INDEX_KNIGHT_BLACK	= 0;
const int INDEX_KNIGHT_BRONZE	= 1;
const int INDEX_KNIGHT_SILVER	= 2;

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
void ResourcesFactory::StartProduction(int i_timeForComplete, ManagerArmy::StateManagerArmy i_state)
{

}

void ResourcesFactory::FinishProduction(ManagerComponent& i_manager)
{

}

void ResourcesFactory::LoadProperties(ManagerComponent& i_manager)
{

}

/*virtual*/ void ResourcesFactory::Update(ManagerComponent& i_manager)
{
	switch (m_stateResources)
	{
		case StateFactoryResources::START_GOLD:
		{
			m_stateResources = StateFactoryResources::WORKING_GOLD;

			break;
		}
		case StateFactoryResources::START_OIL:
		{
			m_stateResources = StateFactoryResources::WORKING_OIL;

			break;
		}
		case StateFactoryResources::WORKING_GOLD:
		{
		
			break;
		}
		case StateFactoryResources::WORKING_OIL:
		{
			
			break;
		}
		case StateFactoryResources::LISTEN:
		{
		
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