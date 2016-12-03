#include "HUDLayer.h"
#include "GameScene.h"
#include "ManagerComponent.h"
#include "HeroInputComponent.h"
#include "ManagerFactory.h"
#include "MachineFactory.h"
#include "WarriorFactory.h"

const int INDEX_FACTORY_ENEMY_MACHINE	= 0;
const int INDEX_FACTORY_MACHINE			= 1;
const int INDEX_FACTORY_WARRIOR			= 2;
const int INDEX_FACTORY_ENEMY_WARRIOR	= 3;

bool HUDLayer::init()
{
	if (!Layer::init())	
	{
		return false;
	}
	
	m_command = Command::NOTHING;

	LoadSpritesForMenu();

	return true;
}

void HUDLayer::LoadSpritesForMenu()
{
	std::vector<int> _positionY;
	_positionY.push_back(0);
	_positionY.push_back(50);
	_positionY.push_back(100);
	_positionY.push_back(150);
	
	std::vector<std::string> _filename;
	_filename.push_back(CNT_PATH_TO_RESOURCES + "HUDLayer/Jelly.png");
	_filename.push_back(CNT_PATH_TO_RESOURCES + "HUDLayer/Coal.png");
	_filename.push_back(CNT_PATH_TO_RESOURCES + "HUDLayer/Ruby.png");
	_filename.push_back(CNT_PATH_TO_RESOURCES + "HUDLayer/Ore.png");

	for (int i = 0; i < 4; i++)
	{
		Sprite* _spriteFactory = Sprite::create(_filename[i]);
		_spriteFactory->setScale(GameScene::m_visibleSize.width / _spriteFactory->getContentSize().width / 8,
			GameScene::m_visibleSize.height / _spriteFactory->getContentSize().height / 8);
		_spriteFactory->setPosition(GameScene::m_visibleSize.width - _spriteFactory->getBoundingBox().size.width, 
			GameScene::m_visibleSize.height / 2 - _positionY[i]);
		m_vecRectMachine.push_back(_spriteFactory->getBoundingBox());
		this->addChild(_spriteFactory);
	}
}

void HUDLayer::Update(ManagerComponent& i_manager)
{
	if ((m_locationTouch = i_manager.m_inputComponent->GetLocationTouch()) != Point::ZERO)
	{
		if (DetermineCommandForManagerFactory())
		{
			ExecuteCommandForManagerFactory(i_manager);
			i_manager.m_inputComponent->SetZeroLocation();
		}
	}
}

bool HUDLayer::DetermineCommandForManagerFactory()
{
	if (m_vecRectMachine[INDEX_FACTORY_MACHINE].containsPoint(m_locationTouch))
	{
		m_command = Command::CREATE_FACTORY_MACHINE;
		return true;
	}
	else if (m_vecRectMachine[INDEX_FACTORY_WARRIOR].containsPoint(m_locationTouch))
	{
		m_command = Command::CREATE_FACTORY_WARRIOR;
		return true;
	}
	else if (m_vecRectMachine[INDEX_FACTORY_ENEMY_WARRIOR].containsPoint(m_locationTouch))
	{
		m_command = Command::CREATE_FACTORY_ENEMY_WARRIOR;
		return true;
	}
	else if (m_vecRectMachine[INDEX_FACTORY_ENEMY_MACHINE].containsPoint(m_locationTouch))
	{
		m_command = Command::CREATE_FACTORY_ENEMY_MACHINE;
		return true;
	}
	return false;
}

void HUDLayer::ExecuteCommandForManagerFactory(ManagerComponent& i_manager)
{
	switch (m_command)
	{
		case Command::CREATE_FACTORY_MACHINE:
		{
			ManagerFactory::StateManagerFactory _state = ManagerFactory::StateManagerFactory::ADD_FACTORY_MACHINE;
			i_manager.m_managerFactory->SetState(_state);
			i_manager.m_managerFactory->SetPositionBuildFactory(i_manager.m_inputComponent->GetPreviousLocationTouch());

			m_command = Command::NOTHING;

			break;
		}
		case Command::CREATE_FACTORY_WARRIOR:
		{
			ManagerFactory::StateManagerFactory _state = ManagerFactory::StateManagerFactory::ADD_FACTORY_WARRIOR;
			i_manager.m_managerFactory->SetState(_state);
			i_manager.m_managerFactory->SetPositionBuildFactory(i_manager.m_inputComponent->GetPreviousLocationTouch());

			m_command = Command::NOTHING;

			break;
		}
		case Command::CREATE_FACTORY_ENEMY_WARRIOR:
		{
			ManagerFactory::StateManagerFactory _state = ManagerFactory::StateManagerFactory::ADD_FACTORY_ENEMY_WARRIOR;
			i_manager.m_managerFactory->SetState(_state);
			i_manager.m_managerFactory->SetPositionBuildFactory(i_manager.m_inputComponent->GetPreviousLocationTouch());

			m_command = Command::NOTHING;
			
			break;
		}
		case Command::CREATE_FACTORY_ENEMY_MACHINE:
		{
			ManagerFactory::StateManagerFactory _state = ManagerFactory::StateManagerFactory::ADD_FACTORY_ENEMY_MACHINE;
			i_manager.m_managerFactory->SetState(_state);
			i_manager.m_managerFactory->SetPositionBuildFactory(i_manager.m_inputComponent->GetPreviousLocationTouch());

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

/*
	Tasks on today(01:11:2016)
	+ Hide menu;
	+ automap;
*/