#include "HUDLayer.h"
#include "GameScene.h"
#include "constants.h"
#include "ManagerComponent.h"
#include "HeroInputComponent.h"
#include "ManagerFactory.h"

bool HUDLayer::init()
{
	if (!Layer::init())	
	{
		return false;
	}
	
	m_factoryMachine = Sprite::create(CNT_PATH_TO_RESOURCES + "HUDLayer/Coal.png");
	m_factoryMachine->setScale(GameScene::m_visibleSize.width / m_factoryMachine->getContentSize().width / 8,
		GameScene::m_visibleSize.height / m_factoryMachine->getContentSize().height / 8);
	m_factoryMachine->setPosition(GameScene::m_visibleSize.width / 2 + m_factoryMachine->getBoundingBox().size.width,
		m_factoryMachine->getBoundingBox().size.height);
	m_rectFactoryMachine = m_factoryMachine->getBoundingBox();
	this->addChild(m_factoryMachine);

	m_factoryWarrior = Sprite::create(CNT_PATH_TO_RESOURCES  + "HUDLayer/Coal.png");
	m_factoryWarrior->setScale(GameScene::m_visibleSize.width / m_factoryWarrior->getContentSize().width / 8,
		GameScene::m_visibleSize.height / m_factoryWarrior->getContentSize().height / 8);
	m_factoryWarrior->setPosition(GameScene::m_visibleSize.width / 2 - m_factoryWarrior->getBoundingBox().size.width,
		m_factoryWarrior->getBoundingBox().size.height);
	m_rectFactoryWarrior = m_factoryWarrior->getBoundingBox();
	this->addChild(m_factoryWarrior);

	return true;
}

void HUDLayer::Update(ManagerComponent& i_manager)
{
	if ((m_locationTouch = i_manager.m_inputComponent->GetLocationTouch()) != Point::ZERO)
	{
		i_manager.m_inputComponent->SetZeroLocation();
		DetermineCommand();
		ExecuteCommand(i_manager);
	}
}

void HUDLayer::DetermineCommand()
{
	if (m_rectFactoryMachine.containsPoint(m_locationTouch))
	{
		m_command = Command::CREATE_FACTORY_MACHINE;
	}
	else if (m_rectFactoryWarrior.containsPoint(m_locationTouch))
	{
		m_command = Command::CREATE_FACTORY_WARRIOR;
	}
}

void HUDLayer::ExecuteCommand(ManagerComponent& i_manager)
{
	switch (m_command)
	{
		case Command::CREATE_FACTORY_MACHINE:
		{
			ManagerFactory::StateManagerFactory _state = ManagerFactory::StateManagerFactory::ADD_FACTORY_MACHINE;
			i_manager.m_managerFactory->SetState(_state);

			m_command = Command::NOTHING;

			break;
		}
		case Command::CREATE_FACTORY_WARRIOR:
		{
			ManagerFactory::StateManagerFactory _state = ManagerFactory::StateManagerFactory::ADD_FACTORY_WARRIOR;
			i_manager.m_managerFactory->SetState(_state);

			m_command = Command::NOTHING;

			break;
		}
	default:
		break;
	}
}

HUDLayer::~HUDLayer()
{

}