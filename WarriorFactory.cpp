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

WarriorFactory::WarriorFactory(Point i_positionVisible, Point i_positionOrigin, MapLayer& i_mapLayer) : Factory(i_positionVisible, 
																												i_positionOrigin, 
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

/*virtual*/ void WarriorFactory::Update(ManagerComponent& i_manager)
{
	switch (m_stateWarrior)
	{
		case StateFactoryWarrior::START_KNIGHT_BLACK:
		{
			if (i_manager.m_hero->CheckProductionKnightBlack())
			{
				m_timeForComplete			= CNT_TIME_FOR_COMPLETE_KNIGHT_BLACK;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateWarrior				= StateFactoryWarrior::WORKING;
				m_stateTypeAddWarrior		= ManagerArmy::StateManagerArmy::ADD_KNIGHT_BLACK;
			}

			break;
		}
		case StateFactoryWarrior::START_KNIGHT_BRONZE:
		{
			if (i_manager.m_hero->CheckProductionKnightBronze())
			{
				m_timeForComplete			= CNT_TIME_FOR_COMPLETE_KNIGHT_BRONZE;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateWarrior				= StateFactoryWarrior::WORKING;
				m_stateTypeAddWarrior		= ManagerArmy::StateManagerArmy::ADD_KNIGHT_BRONZE;
			}

			break;
		}
		case StateFactoryWarrior::START_KNIGHT_SILVER:
		{
			if (i_manager.m_hero->CheckProductionKnightSilver())
			{
				m_timeForComplete			= CNT_TIME_FOR_COMPLETE_KNIGHT_SILVER;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateWarrior				= StateFactoryWarrior::WORKING;
				m_stateTypeAddWarrior		= ManagerArmy::StateManagerArmy::ADD_KNIGHT_SILVER;
			}
			break;
		}
		case StateFactoryWarrior::WORKING:
		{
			if (isComplete())
			{
				m_stateWarrior = StateFactoryWarrior::LISTEN;
				i_manager.m_managerArmy->SetState(m_stateTypeAddWarrior);
				i_manager.m_managerArmy->SetPositionForWarrior(m_vecPosition[m_numberComplete]);
				++m_numberComplete;
			}
			break;
		}
		case StateFactoryWarrior::LISTEN:
		{
			m_locationTouch = i_manager.m_inputComponent->GetLocationTouch();
			ConvertToOrigin();
			if (DetermineCommand())
			{
				i_manager.m_inputComponent->SetZeroLocation();
			}
			break;
		}
		case StateFactoryWarrior::NOTHING:
		{
			m_locationTouch		= i_manager.m_inputComponent->GetLocationTouch();
			ConvertToOrigin();
			if (m_rectOriginWithVisible.containsPoint(m_locationTouch) && m_locationTouch != Point::ZERO)
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