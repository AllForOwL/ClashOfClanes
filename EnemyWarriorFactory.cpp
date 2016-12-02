#include "EnemyWarriorFactory.h"
#include "ManagerComponent.h"
#include "GraphicComponent.h"
#include "ManagerArmy.h"
#include "MapLayer.h"
#include "HeroInputComponent.h"

const int CNT_TIME_FOR_COMPLETE_BOWMAN			= 5;
const int CNT_TIME_FOR_COMPLETE_ENEMY_KNIGHT	= 5;
const int CNT_TIME_FOR_COMPLETE_WIZARD			= 5;
const int CNT_TIME_FOR_COMPLETE_PALADIN			= 5;

const int CNT_INDEX_BOWMAN			= 0;
const int CNT_INDEX_ENEMY_KNIGHT	= 1;
const int CNT_INDEX_WIZARD			= 2;
const int CNT_INDEX_PALADIN			= 3;

EnemyWarriorFactory::EnemyWarriorFactory()
{

}

EnemyWarriorFactory::EnemyWarriorFactory(Point i_positionVisible, MapLayer& i_mapLayer) : Factory(	i_positionVisible,
																									i_mapLayer,
																									"Home/render6.png"
																								 )
{
	m_stateWarrior	= StateFactoryWarrior::NOTHING;
}

EnemyWarriorFactory::EnemyWarriorFactory(EnemyWarriorFactory& i_EnemyWarriorFactory)
{

}

void EnemyWarriorFactory::LoadNameForSprites()
{
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Enemy/Bowman.png");
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Enemy/EnemyKnight.png");
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Enemy/Wizard.png");
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Enemy/Paladin.png");
}

/*virtual*/ void EnemyWarriorFactory::Update(ManagerComponent& i_manager)
{
	switch (m_stateWarrior)
	{
		case StateFactoryWarrior::START_BOWMAN:
		{
				m_timeForComplete			= CNT_TIME_FOR_COMPLETE_BOWMAN;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateWarrior				= StateFactoryWarrior::WORKING;
				m_stateTypeAddWarrior		= ManagerArmy::StateManagerArmy::ADD_ENEMY_BOWMAN;
		
			break;
		}
		case StateFactoryWarrior::START_ENEMY_KNIGHT:
		{
				m_timeForComplete			= CNT_TIME_FOR_COMPLETE_ENEMY_KNIGHT;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateWarrior				= StateFactoryWarrior::WORKING;
				m_stateTypeAddWarrior		= ManagerArmy::StateManagerArmy::ADD_ENEMY_KNIGHT;

			break;
		}
		case StateFactoryWarrior::START_WIZARD:
		{
				m_timeForComplete			= CNT_TIME_FOR_COMPLETE_WIZARD;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateWarrior				= StateFactoryWarrior::WORKING;
				m_stateTypeAddWarrior		= ManagerArmy::StateManagerArmy::ADD_ENEMY_WIZARD;

			break;
		}
		case StateFactoryWarrior::START_PALADIN:
		{
				m_timeForComplete			= CNT_TIME_FOR_COMPLETE_PALADIN;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateWarrior				= StateFactoryWarrior::WORKING;
				m_stateTypeAddWarrior		= ManagerArmy::StateManagerArmy::ADD_ENEMY_PALADIN;

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

bool EnemyWarriorFactory::DetermineCommand()
{
	if (m_rectForSprites[CNT_INDEX_BOWMAN].containsPoint(m_locationTouch))
	{
		m_stateWarrior = StateFactoryWarrior::START_BOWMAN;
		return true;
	}
	else if (m_rectForSprites[CNT_INDEX_ENEMY_KNIGHT].containsPoint(m_locationTouch))
	{
		m_stateWarrior = StateFactoryWarrior::START_ENEMY_KNIGHT;
		return true;
	}
	else if (m_rectForSprites[CNT_INDEX_WIZARD].containsPoint(m_locationTouch))
	{
		m_stateWarrior = StateFactoryWarrior::START_WIZARD;
		return true;
	}
	else if (m_rectForSprites[CNT_INDEX_PALADIN].containsPoint(m_locationTouch))
	{
		m_stateWarrior = StateFactoryWarrior::START_PALADIN;
		return true;
	}

	return false;
}

using STATE_FACTORY = EnemyWarriorFactory::StateFactoryWarrior;
void EnemyWarriorFactory::SetState(STATE_FACTORY& i_stateWarrior)
{
	m_stateWarrior = i_stateWarrior;
}

EnemyWarriorFactory::StateFactoryWarrior& EnemyWarriorFactory::GetStateWarrior()
{
	return m_stateWarrior;
}

EnemyWarriorFactory::~EnemyWarriorFactory()
{

}