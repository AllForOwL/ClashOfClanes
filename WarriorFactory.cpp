#include "WarriorFactory.h"
#include "ManagerComponent.h"
#include "HeroGraphicComponent.h"
#include "GameScene.h"
#include "GraphicComponent.h"
#include "ManagerArmy.h"
#include "constants.h"
#include "HeroInputComponent.h"
#include "HUDLayer.h"

const int CNT_TIME_FOR_COMPLETE_KNIGHT_BLACK	= 10;
const int CNT_TIME_FOR_COMPLETE_KNIGHT_BRONZE	= 15;
const int CNT_TIME_FOR_COMPLETE_KNIGHT_SILVER	= 20;

WarriorFactory::WarriorFactory()
{

}

WarriorFactory::WarriorFactory(GameScene& i_parentGameScene)
{
	i_parentGameScene.addChild(this);
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Home/render4.png");
	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 6,
		GameScene::m_visibleSize.height / this->getContentSize().height / 6);
	this->setPosition(GameScene::m_visibleSize.width / 2 + 50, GameScene::m_visibleSize.height / 2);
	this->setZOrder(1);

	m_stateWarrior	= StateFactoryWarrior::NOTHING;
	m_locationTouch = Point::ZERO;
	m_rectFactory	= this->getBoundingBox();
}

WarriorFactory::WarriorFactory(WarriorFactory& i_warriorFactory)
{

}

bool WarriorFactory::isComplete() 
{
	if ((int)std::chrono::duration<double>(GraphicComponent::GetTime() - m_startSecond).count() == m_timeForCompleteWarrior)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*virtual*/ void WarriorFactory::Update(ManagerComponent& i_manager)
{
	switch (m_stateWarrior)
	{
		case StateFactoryWarrior::START_KNIGHT_BLACK:
		{
			if (i_manager.m_hero->CheckProductionKnightBlack())
			{
				m_timeForCompleteWarrior	= CNT_TIME_FOR_COMPLETE_KNIGHT_BLACK;
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
				m_timeForCompleteWarrior	= CNT_TIME_FOR_COMPLETE_KNIGHT_BRONZE;
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
				m_timeForCompleteWarrior	= CNT_TIME_FOR_COMPLETE_KNIGHT_SILVER;
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
				m_stateFactory = StateFactoryWarrior::NOTHING;
				i_manager.m_managerArmy->SetState(m_stateTypeAddWarrior);
			}
			break;
		}
		case StateFactoryWarrior::NOTHING:
		{
			m_locationTouch = i_manager.m_inputComponent->GetLocationTouch();
			
			if (m_rectFactory.containsPoint(m_locationTouch))
			{
				HUDLayer::m_typeMenu = HUDLayer::StateTypeMenu::FACTORY_WARRIOR;
				m_stateFactory = StateFactoryWarrior::LISTEN;
			}
			break;
		}
	default:
		break;
	}
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
