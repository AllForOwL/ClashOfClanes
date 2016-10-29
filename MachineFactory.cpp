#include "MachineFactory.h"
#include "ManagerComponent.h"
#include "ManagerFactory.h"
#include "HeroGraphicComponent.h"
#include "GameScene.h"
#include "GraphicComponent.h"
#include "ManagerMachine.h"
#include "constants.h"

const int CNT_TIME_FOR_COMPLETE_TANK = 40;
const int CNT_TIME_FOR_COMPLETE_CAR = 30;

MachineFactory::MachineFactory()
{

}

MachineFactory::MachineFactory(GameScene& i_parentGameScene)
{
	i_parentGameScene.addChild(this);
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Castle/FactoryMachine.png");
	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 6,
		GameScene::m_visibleSize.height / this->getContentSize().height / 6);
	this->setPosition(GameScene::m_visibleSize.width / 2, GameScene::m_visibleSize.height / 2);
	this->setZOrder(1);
}

MachineFactory::MachineFactory(MachineFactory& i_MachineFactory)
{

}

bool MachineFactory::isComplete() 
{
	if ((int)std::chrono::duration<double>(GraphicComponent::GetTime() - m_startSecond).count() == m_timeForCompleteMachine)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*virtual*/ void MachineFactory::Update(ManagerComponent& i_manager)
{
	switch (m_stateFactoryMachine)
	{
		case StateFactoryMachine::START_TANK:
		{
			if (i_manager.m_hero->CheckProductionTank())
			{
				m_timeForCompleteMachine	= CNT_TIME_FOR_COMPLETE_TANK;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateFactoryMachine		= StateFactoryMachine::WORKING;
				m_stateManagerMachine		= ManagerMachine::StateManagerMachine::ADD_TANK;
			}

			break;
		}
		case StateFactoryMachine::START_CAR:
		{
			if (i_manager.m_hero->CheckProductionCar())
			{
				m_timeForCompleteMachine	= CNT_TIME_FOR_COMPLETE_CAR;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateFactoryMachine		= StateFactoryMachine::WORKING;
				m_stateManagerMachine		= ManagerMachine::StateManagerMachine::ADD_CAR;
			}
												
			break;
		}
		case StateFactoryMachine::WORKING:
		{
			if (isComplete())
			{
				m_stateFactoryMachine = StateFactoryMachine::NOTHING;
				i_manager.m_managerMachine->SetState(m_stateManagerMachine);
			}
			break;
		}
		case StateFactoryMachine::NOTHING:
		{
			
			break;
		}
	default:
		break;
	}
}

MachineFactory::~MachineFactory()
{

}
