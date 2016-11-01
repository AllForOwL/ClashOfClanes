#include "MachineFactory.h"
#include "ManagerComponent.h"
#include "ManagerFactory.h"
#include "HeroGraphicComponent.h"
#include "GameScene.h"
#include "GraphicComponent.h"
#include "ManagerMachine.h"
#include "constants.h"
#include "HeroInputComponent.h"
#include "HUDLayer.h"

const int CNT_TIME_FOR_COMPLETE_TANK = 40;
const int CNT_TIME_FOR_COMPLETE_CAR = 30;

const int CNT_INDEX_TANK = 0;

MachineFactory::MachineFactory()
{

}

MachineFactory::MachineFactory(GameScene& i_parentGameScene)
{
	i_parentGameScene.addChild(this);
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Castle/FactoryMachine.png");
	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 6,
		GameScene::m_visibleSize.height / this->getContentSize().height / 6);
	this->setPosition(GameScene::m_visibleSize.width / 2 - 50, GameScene::m_visibleSize.height / 2);
	this->setZOrder(1);

	m_stateMachine	= StateFactoryMachine::NOTHING;
	m_rectFactory	= this->getBoundingBox();

	LoadNameForSprites();
	LoadSprites();
}

MachineFactory::MachineFactory(MachineFactory& i_MachineFactory)
{

}

void MachineFactory::SetState(MachineFactory::StateFactoryMachine& i_state)
{
	m_stateMachine = i_state;
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

void MachineFactory::LoadNameForSprites()
{
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Machine/Tank_1.png");
}

void MachineFactory::LoadSprites()
{
	float _positionY = GameScene::m_visibleSize.height / 2;
	for (int i = 0; i < m_vecNameForSprites.size(); i++)
	{
		m_vecSpritesForFactoryMachine.push_back(Sprite::create(m_vecNameForSprites[i]));
		m_vecSpritesForFactoryMachine[i]->setScale(GameScene::m_visibleSize.width / m_vecSpritesForFactoryMachine[i]->getContentSize().width / 8,
			GameScene::m_visibleSize.height / m_vecSpritesForFactoryMachine[i]->getContentSize().height / 8);
		m_vecSpritesForFactoryMachine[i]->setPosition(GameScene::m_visibleSize.width - m_vecSpritesForFactoryMachine[i]->getBoundingBox().size.width,
			_positionY);
		m_vecSpritesForFactoryMachine[i]->setVisible(false);
		this->getParent()->addChild(m_vecSpritesForFactoryMachine[i]);

		_positionY -= m_vecSpritesForFactoryMachine[i]->getBoundingBox().size.height;
		m_rectForSpritesMachine.push_back(m_vecSpritesForFactoryMachine[i]->getBoundingBox());
	}
}

void MachineFactory::ShowMenu()
{
	for (int i = 0; i < m_vecSpritesForFactoryMachine.size(); i++)
	{
		m_vecSpritesForFactoryMachine[i]->setVisible(true);
	}
}

void MachineFactory::HideMenu()
{
	for (int i = 0; i < m_vecSpritesForFactoryMachine.size(); i++)
	{
		m_vecSpritesForFactoryMachine[i]->setVisible(false);
	}
}

/*virtual*/ void MachineFactory::Update(ManagerComponent& i_manager)
{
	switch (m_stateMachine)
	{
		case StateFactoryMachine::START_TANK:
		{
			if (i_manager.m_hero->CheckProductionTank())
			{
				m_timeForCompleteMachine	= CNT_TIME_FOR_COMPLETE_TANK;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateMachine				= StateFactoryMachine::WORKING;
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
				m_stateMachine				= StateFactoryMachine::WORKING;
				m_stateManagerMachine		= ManagerMachine::StateManagerMachine::ADD_CAR;
			}												
			break;
		}
		case StateFactoryMachine::WORKING:
		{
			if (isComplete())
			{
				m_stateMachine = StateFactoryMachine::NOTHING;
				i_manager.m_managerMachine->SetState(m_stateManagerMachine);
			}
			break;
		}
		case StateFactoryMachine::NOTHING:
		{
			m_locationTouch = i_manager.m_inputComponent->GetLocationTouch();
			if (m_rectFactory.containsPoint(m_locationTouch))
			{
				ShowMenu();
				m_stateMachine	= StateFactoryMachine::LISTEN;
				i_manager.m_inputComponent->SetZeroLocation();
			}
			break;
		}
		case StateFactoryMachine::LISTEN:
		{
			m_locationTouch = i_manager.m_inputComponent->GetLocationTouch();
			if (DetermineCommand())
			{
				i_manager.m_inputComponent->SetZeroLocation();
			}
			else if (m_locationTouch != Point::ZERO)
			{
				HideMenu();
				m_stateMachine = StateFactoryMachine::NOTHING;
			}
			break;
		}
	default:
		break;
	}
}

bool MachineFactory::DetermineCommand()
{
	if (m_rectForSpritesMachine[CNT_INDEX_TANK].containsPoint(m_locationTouch))
	{
		m_stateMachine = StateFactoryMachine::START_TANK;
		return true;
	}
	return false;
}

MachineFactory::StateFactoryMachine& MachineFactory::GetState()
{
	return m_stateMachine;
}

MachineFactory::~MachineFactory()
{

}


/*
 Hero has goes on map
*/