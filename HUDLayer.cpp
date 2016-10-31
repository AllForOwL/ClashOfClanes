#include "HUDLayer.h"
#include "GameScene.h"
#include "constants.h"
#include "ManagerComponent.h"
#include "HeroInputComponent.h"
#include "ManagerFactory.h"
#include "MachineFactory.h"
#include "WarriorFactory.h"

using STATE_TYPE_MENU = HUDLayer::StateTypeMenu;

STATE_TYPE_MENU HUDLayer::m_typeMenu = STATE_TYPE_MENU::NOTHING;

const int INDEX_TANK = 0;

const int INDEX_ARCHER			= 0;
const int INDEX_KNIGHT_BLACK	= 1;
const int INDEX_KNIGHT_BRONZE	= 2;
const int INDEX_KNIGHT_SILVER	= 3;

bool HUDLayer::init()
{
	if (!Layer::init())	
	{
		return false;
	}
	
	LoadNameForAllSprites();
	LoadSpritesForFactory();
	LoadSpritesForMenu();

	m_command = Command::NOTHING;

	return true;
}

void HUDLayer::LoadNameForAllSprites()
{
	m_vecNameFactoryMachine.push_back(CNT_PATH_TO_RESOURCES + "Machine/Tank_1.png");

	m_vecNameFactoryWarrior.push_back(CNT_PATH_TO_RESOURCES + "Warrior/black_knight/attack_1.png");
	m_vecNameFactoryWarrior.push_back(CNT_PATH_TO_RESOURCES + "Warrior/bronze_knight/attack_1.png");
	m_vecNameFactoryWarrior.push_back(CNT_PATH_TO_RESOURCES + "Warrior/silver_knight/attack_1.png");
}

void HUDLayer::LoadSpritesForFactory()
{
	int _positionY = GameScene::m_visibleSize.height / 2;
	Sprite* _sprite;
	Rect	_rect;
	for (int i = 0; i < m_vecNameFactoryMachine.size(); i++)
	{
		_sprite = Sprite::create(m_vecNameFactoryMachine[i]);
		_sprite->setScale(GameScene::m_visibleSize.width / _sprite->getContentSize().width / 8,
			GameScene::m_visibleSize.height / _sprite->getContentSize().height);
		_sprite->setPosition(GameScene::m_visibleSize.width - _sprite->getBoundingBox().size.width,
			_positionY);

		m_vecSpritesForFactoryMachine.push_back(_sprite);
		_positionY -= _sprite->getBoundingBox().size.height;
		_rect = _sprite->getBoundingBox();
		m_vecRectSpritesFactoryMachine.push_back(_rect);
	}

	_positionY = GameScene::m_visibleSize.height / 2;
	for (int i = 0; i < m_vecNameFactoryWarrior.size(); i++)
	{
		_sprite = Sprite::create(m_vecNameFactoryWarrior[i]);
		_sprite->setScale(GameScene::m_visibleSize.width / _sprite->getContentSize().width / 8,
			GameScene::m_visibleSize.height / _sprite->getContentSize().height);
		_sprite->setPosition(GameScene::m_visibleSize.width - _sprite->getBoundingBox().size.width,
			_positionY);

		m_vecSpritesForFactoryWarrior.push_back(_sprite);
		_positionY -= _sprite->getBoundingBox().size.height;
		_rect = _sprite->getBoundingBox();
		m_vecRectSpritesFactoryWarrior.push_back(_rect);
	}
}

void HUDLayer::LoadSpritesForMenu()
{

}

void HUDLayer::ShowMenuForFactoryMachine()
{
	for (int i = 0; i < m_vecSpritesForFactoryMachine.size(); i++)
	{
		this->addChild(m_vecSpritesForFactoryMachine[i]);
	}
}

void HUDLayer::ShowMenuForFactoryWarrior()
{
	for (int i = 0; i < m_vecSpritesForFactoryWarrior.size(); i++)
	{
		this->addChild(m_vecSpritesForFactoryWarrior[i]);
	}
}

void HUDLayer::Update(ManagerComponent& i_manager)
{
	switch (m_typeMenu)
	{
		case StateTypeMenu::FACTORY_MACHINE:
		{	
			ShowMenuForFactoryMachine();
			m_typeMenu	= StateTypeMenu::NOTHING;
			m_command	= Command::CREATE_MACHINE;

			break;
		}
		case StateTypeMenu::FACTORY_WARRIOR:
		{
			ShowMenuForFactoryWarrior();
			m_typeMenu	= StateTypeMenu::NOTHING;
			m_command	= Command::CREATE_WARRIOR;

			break;
		}
	default:
		break;
	}

	if ((m_locationTouch = i_manager.m_inputComponent->GetLocationTouch()) != Point::ZERO)
	{
		switch (m_command)
		{
			case Command::CREATE_MACHINE:
			{
				if (DetermineCommandForFactoryMachine())
				{
					ExecuteCommandForFactoryMachine(i_manager);
					i_manager.m_inputComponent->SetZeroLocation();
				}

				break;
			}
			case Command::CREATE_WARRIOR:
			{
				if (DetermineCommandForFactoryWarrior())
				{
					ExecuteCommandForFactoryWarrior(i_manager);
					i_manager.m_inputComponent->SetZeroLocation();
				}
				break;
			}
			case Command::NOTHING:
			{
				if (DetermineCommandForManagerFactory())
				{
					ExecuteCommandForManagerFactory(i_manager);
					i_manager.m_inputComponent->SetZeroLocation();
				}
				break;
			}
		}
	}
}

bool HUDLayer::DetermineCommandForManagerFactory()
{
	if (m_rectFactoryMachine.containsPoint(m_locationTouch))
	{
		m_command = Command::CREATE_FACTORY_MACHINE;
		return true;
	}
	else if (m_rectFactoryWarrior.containsPoint(m_locationTouch))
	{
		m_command = Command::CREATE_FACTORY_WARRIOR;
		return true;
	}
	return false;
}

bool HUDLayer::DetermineCommandForFactoryMachine()
{
	if (m_vecRectSpritesFactoryMachine[INDEX_TANK].containsPoint(m_locationTouch))
	{
		m_commandMachine = CommandMachine::CREATE_TANK;
		return true;
	}
}

bool HUDLayer::DetermineCommandForFactoryWarrior()
{
	if (m_vecRectSpritesFactoryWarrior[INDEX_ARCHER].containsPoint(m_locationTouch))
	{
		m_commandWarrior = CommandWarrior::CREATE_KNIGHT_BLACK;
		return true;
	}
	else if (m_vecRectSpritesFactoryWarrior[INDEX_KNIGHT_BLACK].containsPoint(m_locationTouch))
	{
		m_commandWarrior = CommandWarrior::CREATE_KNIGHT_BRONZE;
		return true;
	}
	else if (m_vecRectSpritesFactoryWarrior[INDEX_KNIGHT_SILVER].containsPoint(m_locationTouch))
	{
		m_commandWarrior = CommandWarrior::CREATE_KNIGHT_SILVER;
		return true;
	}
}

void HUDLayer::ExecuteCommandForManagerFactory(ManagerComponent& i_manager)
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

using STATE_MACHINE = MachineFactory::StateFactoryMachine;
void HUDLayer::ExecuteCommandForFactoryMachine(ManagerComponent& i_manager)
{
	switch (m_commandMachine)
	{
		case CommandMachine::CREATE_TANK:
		{
			STATE_MACHINE _state = STATE_MACHINE::START_TANK;
			i_manager.m_managerFactory->GetListenFactoryMachine().SetState(_state);

			m_commandMachine = CommandMachine::NOTHING;

			break;
		}
	default:
		break;
	}

}

using STATE_WARRIOR = WarriorFactory::StateFactoryWarrior;
void HUDLayer::ExecuteCommandForFactoryWarrior(ManagerComponent& i_manager)
{
	switch (m_commandWarrior)
	{
		case HUDLayer::CREATE_KNIGHT_BLACK:
		{
			STATE_WARRIOR _state = STATE_WARRIOR::START_KNIGHT_BLACK;
			i_manager.m_managerFactory->GetListenFactoryWarrior().SetState(_state);
			
			m_commandWarrior = HUDLayer::CommandWarrior::NOTHING;

			break;
		}
		case HUDLayer::CREATE_KNIGHT_BRONZE:
		{
			STATE_WARRIOR _state = STATE_WARRIOR::START_KNIGHT_BRONZE;
			i_manager.m_managerFactory->GetListenFactoryWarrior().SetState(_state);

			m_commandWarrior = HUDLayer::CommandWarrior::NOTHING;

			break;
		}
		case HUDLayer::CREATE_KNIGHT_SILVER:
		{
			STATE_WARRIOR _state = STATE_WARRIOR::START_KNIGHT_SILVER;
			i_manager.m_managerFactory->GetListenFactoryWarrior().SetState(_state);

			m_commandWarrior = HUDLayer::CommandWarrior::NOTHING;

			break;
		}
		default:
			break;
	}
}

HUDLayer::~HUDLayer()
{

}