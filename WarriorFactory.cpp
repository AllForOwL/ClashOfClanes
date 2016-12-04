#include "WarriorFactory.h"
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

WarriorFactory::WarriorFactory()
{

}

WarriorFactory::WarriorFactory(Point i_positionVisible, MapLayer& i_mapLayer) : Factory(i_positionVisible, 
																						i_mapLayer, 
																						"Home/render4.png")
{
	m_stateWarrior	= StateFactoryWarrior::NOTHING;
}
WarriorFactory::WarriorFactory(WarriorFactory& i_warriorFactory)
{

}

void WarriorFactory::LoadNameForSprites()
{
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Warrior/black_knight/attack_1.png");
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Warrior/bronze_knight/attack_1.png");
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Warrior/silver_knight/attack_1.png");
}

void WarriorFactory::StartProduction(int i_timeForComplete, ManagerArmy::StateManagerArmy i_state)
{
	m_timeForComplete			= i_timeForComplete;
	m_startSecond				= GraphicComponent::GetTime();
	m_stateTypeAddWarrior		= i_state;

	m_stateWarrior				= StateFactoryWarrior::WORKING;
}

void WarriorFactory::FinishProduction(ManagerComponent& i_manager)
{
	m_stateWarrior = StateFactoryWarrior::LISTEN;
	i_manager.m_managerArmy->SetState(m_stateTypeAddWarrior);
	i_manager.m_managerArmy->SetPositionForWarrior(m_vecPosition[m_numberComplete]);
	++m_numberComplete;
}

void WarriorFactory::LoadProperties(ManagerComponent& i_manager)
{
	if (m_vecNameForSprites.empty())
	{
		LoadNameForSprites();
		LoadSprites();
	}

	LoadPosition();
	ShowMenu();
	m_stateWarrior = StateFactoryWarrior::LISTEN;
	i_manager.m_inputComponent->SetZeroLocation();
}

/*virtual*/ void WarriorFactory::Update(ManagerComponent& i_manager)
{
	switch (m_stateWarrior)
	{
		case StateFactoryWarrior::START_KNIGHT_BLACK:
		{
			if (i_manager.m_hero->CheckProductionKnightBlack())
			{
				StartProduction(CNT_TIME_FOR_COMPLETE_KNIGHT_BLACK, ManagerArmy::StateManagerArmy::ADD_KNIGHT_BLACK);
			}

			break;
		}
		case StateFactoryWarrior::START_KNIGHT_BRONZE:
		{
			if (i_manager.m_hero->CheckProductionKnightBronze())
			{
				StartProduction(CNT_TIME_FOR_COMPLETE_KNIGHT_BRONZE, ManagerArmy::StateManagerArmy::ADD_KNIGHT_BRONZE);
			}

			break;
		}
		case StateFactoryWarrior::START_KNIGHT_SILVER:
		{
			if (i_manager.m_hero->CheckProductionKnightSilver())
			{
				StartProduction(CNT_TIME_FOR_COMPLETE_KNIGHT_SILVER, ManagerArmy::StateManagerArmy::ADD_KNIGHT_SILVER);
			}
			break;
		}
		case StateFactoryWarrior::WORKING:
		{
			if (isComplete())
			{
				FinishProduction(i_manager);
			}
			break;
		}
		case StateFactoryWarrior::LISTEN:
		{
			m_locationTouch = i_manager.m_inputComponent->GetLocationTouch();
			ConvertToOrigin(m_locationTouch);
			if (DetermineCommand())
			{
				i_manager.m_inputComponent->SetZeroLocation();
			}
			break;
		}
		case StateFactoryWarrior::NOTHING:
		{
			m_locationTouch		= i_manager.m_inputComponent->GetLocationTouch();
			ConvertToOrigin(m_locationTouch);
			if (m_rectOriginWithVisible.containsPoint(m_locationTouch) && m_locationTouch != Point::ZERO)
			{
				LoadProperties(i_manager);
			}	
			break;
		}
	default:
		break;
	}
}

bool WarriorFactory::DetermineCommand()
{
	if (m_rectForSprites[INDEX_KNIGHT_BLACK].containsPoint(m_locationTouch))
	{
		m_stateWarrior = StateFactoryWarrior::START_KNIGHT_BLACK;
		return true;
	}
	else if (m_rectForSprites[INDEX_KNIGHT_BRONZE].containsPoint(m_locationTouch))
	{
		m_stateWarrior = StateFactoryWarrior::START_KNIGHT_BRONZE;
		return true;
	}
	else if (m_rectForSprites[INDEX_KNIGHT_SILVER].containsPoint(m_locationTouch))
	{
		m_stateWarrior = StateFactoryWarrior::START_KNIGHT_SILVER;
		return true;
	}
	return false;
}

using STATE_FACTORY = WarriorFactory::StateFactoryWarrior;
void WarriorFactory::SetState(STATE_FACTORY& i_stateWarrior)
{
	m_stateWarrior = i_stateWarrior;
}

WarriorFactory::StateFactoryWarrior& WarriorFactory::GetStateWarrior()
{
	return m_stateWarrior;
}

WarriorFactory::~WarriorFactory()
{

}