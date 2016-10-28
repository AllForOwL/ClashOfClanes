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
	if ((int)std::chrono::duration<double>(GraphicComponent::GetTime() - m_startSecond).count() == CNT_TIME_FOR_COMPLETE_ARCHER)
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
		case StateFactory::START:
		{
			if (i_manager.m_hero->GetCoin() >= CNT_COIN_FOR_START_ARCHER)
			{
				m_startSecond = GraphicComponent::GetTime();
				m_stateFactory = StateFactory::WORKING;
			}

			break;
		}
		case StateFactory::WORKING:
		{
			if (isComplete())
			{
				m_stateFactory = StateFactory::NOTHING;
				ManagerArmy::StateManagerArmy _stateArmy = ManagerArmy::StateManagerArmy::ADD_ARCHER;
				i_manager.m_managerArmy->SetState(_stateArmy);
			}
			break;
		}
		case StateFactory::NOTHING:
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
