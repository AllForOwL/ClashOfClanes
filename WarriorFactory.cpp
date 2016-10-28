#include "WarriorFactory.h"
#include "ManagerComponent.h"
#include "HeroGraphicComponent.h"
#include "GameScene.h"
#include "GraphicComponent.h"
#include "ManagerArmy.h"

const int CNT_COIN_FOR_START_ARCHER = 50;
const int CNT_TIME_FOR_COMPLETE_ARCHER = 20;

WarriorFactory::WarriorFactory()
{

}

WarriorFactory::WarriorFactory(GameScene& i_parentGameScene)
{
	i_parentGameScene.addChild(this);
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
	switch (m_stateFactory)
	{
		case StateFactoryWarrior::START_ARCHER:
		{
			if (i_manager.m_hero->CheckProductionArcher())
			{
				m_timeForCompleteWarrior = CNT_TIME_FOR_COMPLETE_ARCHER;
				m_startSecond = GraphicComponent::GetTime();
				m_stateFactory = StateFactoryWarrior::WORKING;
				m_stateTypeAddWarrior = ManagerArmy::StateManagerArmy::ADD_ARCHER;
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
			
			break;
		}
	default:
		break;
	}
}

WarriorFactory::~WarriorFactory()
{

}
