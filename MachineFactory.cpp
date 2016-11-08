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
#include "MapLayer.h"

const int CNT_TIME_FOR_COMPLETE_TANK = 40;
const int CNT_TIME_FOR_COMPLETE_CAR = 30;

const int CNT_INDEX_TANK = 0;

MachineFactory::MachineFactory()
{

}

MachineFactory::MachineFactory(Point i_positionVisible, MapLayer& i_mapLayer)
{
	i_mapLayer.addChild(this);

	m_positionVisible = i_positionVisible;

	m_positionOrigin = this->getParent()->getPosition();
	m_positionOrigin.x *= (-1);
	m_positionOrigin.y *= (-1);

	this->initWithFile(CNT_PATH_TO_RESOURCES + "Castle/FactoryMachine.png");
	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 6,
		GameScene::m_visibleSize.height / this->getContentSize().height / 6);

	m_stateMachine	= StateFactoryMachine::NOTHING;
	
	// calculate RectOrigin(system coordinate all MapLayer)
	m_rectFactoryOrigin = Rect(this->getBoundingBox().getMinX() + m_positionOrigin.x, this->getBoundingBox().getMinY() + m_positionOrigin.y,
		this->getBoundingBox().size.width, this->getBoundingBox().size.height);
	// calculate RectVisible(system coordinate visible MapLayer)
	m_rectFactoryVisible = Rect(this->getBoundingBox().getMinX() + m_positionVisible.x, this->getBoundingBox().getMinY() + m_positionVisible.y,
		this->getBoundingBox().size.width, this->getBoundingBox().size.height);

	m_rectFactoryOriginWithVisible = Rect(this->getBoundingBox().getMinX() + m_positionOrigin.x + m_positionVisible.x,
		this->getBoundingBox().getMinY() + m_positionOrigin.y + m_positionVisible.y,
		this->getBoundingBox().size.width, this->getBoundingBox().size.height
		);

	m_numberMachineComplete = 0;

	m_positionOriginWithVisible = m_positionOrigin + m_positionVisible;
	this->setPosition(m_positionOriginWithVisible);

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
		m_vecSpritesForFactoryMachine[i]->setScale(GameScene::m_visibleSize.width / m_vecSpritesForFactoryMachine[i]->getContentSize().width / 15,
			GameScene::m_visibleSize.height / m_vecSpritesForFactoryMachine[i]->getContentSize().height / 15);
		m_vecSpritesForFactoryMachine[i]->setVisible(false);
		this->getParent()->addChild(m_vecSpritesForFactoryMachine[i]);
	}
}

// position for spawn warrior
void MachineFactory::LoadPositionMachine()
{
	Point _positionWarrior = Point(m_positionOriginWithVisible.x, m_positionOriginWithVisible.y - (m_rectFactoryVisible.size.height / 2));
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			m_vecPositionMachine.push_back(_positionWarrior);
			_positionWarrior.x += m_vecSpritesForFactoryMachine[0]->getBoundingBox().size.width;
		}
		_positionWarrior.y += m_vecSpritesForFactoryMachine[0]->getBoundingBox().size.height;
	}
}

void MachineFactory::ShowMenu()
{
	Point _positionMachineMenu = Point(m_positionOriginWithVisible.x + (m_rectFactoryVisible.size.width / 2),
		m_positionOriginWithVisible.y);

	for (int i = 0; i < m_vecSpritesForFactoryMachine.size(); i++)
	{
		m_vecSpritesForFactoryMachine[i]->setPosition(_positionMachineMenu);
		m_vecSpritesForFactoryMachine[i]->setVisible(true);
		_positionMachineMenu.y -= m_vecSpritesForFactoryMachine[i]->getBoundingBox().size.height / 2;
		m_rectForSpritesMachine.push_back(m_vecSpritesForFactoryMachine[i]->getBoundingBox());
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
				i_manager.m_managerMachine->SetPositionForMachine(m_vecPositionMachine[m_numberMachineComplete]);
				++m_numberMachineComplete;
			}
			break;
		}
		case StateFactoryMachine::NOTHING:
		{
			Point m_positionMap = this->getParent()->getPosition();
			m_locationTouch		= i_manager.m_inputComponent->GetLocationTouch();
			Point _positionOrigin = this->getParent()->getPosition();
			_positionOrigin.x *= (-1);
			_positionOrigin.y *= (-1);
			m_locationTouch += _positionOrigin;
			if (m_rectFactoryOriginWithVisible.containsPoint(m_locationTouch))
			{
				ShowMenu();
				LoadPositionMachine();
				m_stateMachine	= StateFactoryMachine::LISTEN;
				i_manager.m_inputComponent->SetZeroLocation();
			}
			break;
		}
		case StateFactoryMachine::LISTEN:
		{
			m_locationTouch = i_manager.m_inputComponent->GetLocationTouch();
			Point _positionOrigin = this->getParent()->getPosition();
			_positionOrigin.x *= (-1);
			_positionOrigin.y *= (-1);
			m_locationTouch += _positionOrigin;
			if (DetermineCommand())
			{
				i_manager.m_inputComponent->SetZeroLocation();
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