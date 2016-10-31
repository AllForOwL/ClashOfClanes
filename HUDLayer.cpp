#include "HUDLayer.h"
#include "GameScene.h"
#include "constants.h"
#include "ManagerComponent.h"
#include "HeroInputComponent.h"
#include "ManagerFactory.h"
#include "MachineFactory.h"
#include "WarriorFactory.h"

using STATE_TYPE_MENU = HUDLayer::StateTypeMenu;

STATE_TYPE_MENU HUDLayer::m_typeMenu = STATE_TYPE_MENU::NOTHING_MENU;

const int INDEX_TANK = 0;

const int INDEX_KNIGHT_BLACK	= 0;
const int INDEX_KNIGHT_BRONZE	= 1;
const int INDEX_KNIGHT_SILVER	= 2;

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

	for (int i = 0; i < m_vecNameFactoryMachine.size(); i++)
	{
		m_vecSpritesForFactoryMachine.push_back(Sprite::create(m_vecNameFactoryMachine[i]));
		m_vecSpritesForFactoryMachine[i]->setScale(GameScene::m_visibleSize.width / m_vecSpritesForFactoryMachine[i]->getContentSize().width / 8,
			GameScene::m_visibleSize.height / m_vecSpritesForFactoryMachine[i]->getContentSize().height / 8);
		m_vecSpritesForFactoryMachine[i]->setPosition(GameScene::m_visibleSize.width - m_vecSpritesForFactoryMachine[i]->getBoundingBox().size.width,
			_positionY);
		m_vecSpritesForFactoryMachine[i]->setVisible(false);
		this->addChild(m_vecSpritesForFactoryMachine[i]);

		_positionY -= m_vecSpritesForFactoryMachine[i]->getBoundingBox().size.height;
		m_vecRectSpritesFactoryMachine.push_back(m_vecSpritesForFactoryMachine[i]->getBoundingBox());
	}

	_positionY = GameScene::m_visibleSize.height / 2;
	for (int i = 0; i < m_vecNameFactoryWarrior.size(); i++)
	{
		m_vecSpritesForFactoryWarrior.push_back(Sprite::create(m_vecNameFactoryWarrior[i]));
		m_vecSpritesForFactoryWarrior[i]->setScale(GameScene::m_visibleSize.width / m_vecSpritesForFactoryWarrior[i]->getContentSize().width / 8,
			GameScene::m_visibleSize.height / m_vecSpritesForFactoryWarrior[i]->getContentSize().height / 8);
		m_vecSpritesForFactoryWarrior[i]->setPosition(GameScene::m_visibleSize.width - m_vecSpritesForFactoryWarrior[i]->getBoundingBox().size.width,
			_positionY);
		m_vecSpritesForFactoryWarrior[i]->setVisible(false);
		this->addChild(m_vecSpritesForFactoryWarrior[i]);

		_positionY -= m_vecSpritesForFactoryWarrior[i]->getBoundingBox().size.height;
		m_vecRectSpritesFactoryWarrior.push_back(m_vecSpritesForFactoryWarrior[i]->getBoundingBox());
	}
}

void HUDLayer::LoadSpritesForMenu()
{
	Sprite* _spriteFactoryMachine = Sprite::create(CNT_PATH_TO_RESOURCES + "HUDLayer/Coal.png");
	_spriteFactoryMachine->setScale(GameScene::m_visibleSize.width / _spriteFactoryMachine->getContentSize().width / 8,
		GameScene::m_visibleSize.height / _spriteFactoryMachine->getContentSize().height / 8);
	_spriteFactoryMachine->setPosition(GameScene::m_visibleSize.width - _spriteFactoryMachine->getBoundingBox().size.width,
		GameScene::m_visibleSize.height / 2 - 50);
	m_rectFactoryMachine = _spriteFactoryMachine->getBoundingBox();
	this->addChild(_spriteFactoryMachine);

	Sprite* _spriteFactoryWarrior = Sprite::create(CNT_PATH_TO_RESOURCES + "HUDLayer/Ruby.png");
	_spriteFactoryWarrior->setScale(GameScene::m_visibleSize.width / _spriteFactoryWarrior->getContentSize().width / 20,
		GameScene::m_visibleSize.height / _spriteFactoryWarrior->getContentSize().height / 20);
	_spriteFactoryWarrior->setPosition(GameScene::m_visibleSize.width - _spriteFactoryWarrior->getBoundingBox().size.width,
		GameScene::m_visibleSize.height / 2 - 100);
	m_rectFactoryWarrior = _spriteFactoryWarrior->getBoundingBox();
	this->addChild(_spriteFactoryWarrior);
}

void HUDLayer::ShowMenuForFactoryMachine()
{
	for (int i = 0; i < m_vecSpritesForFactoryWarrior.size(); i++)
	{
		m_vecSpritesForFactoryWarrior[i]->setVisible(false);
	}

	for (int i = 0; i < m_vecSpritesForFactoryMachine.size(); i++)
	{
		m_vecSpritesForFactoryMachine[i]->setVisible(true);
	}
}

void HUDLayer::ShowMenuForFactoryWarrior()
{
	for (int i = 0; i < m_vecSpritesForFactoryMachine.size(); i++)
	{
		m_vecSpritesForFactoryMachine[i]->setVisible(false);
	}

	for (int i = 0; i < m_vecSpritesForFactoryWarrior.size(); i++)
	{
		m_vecSpritesForFactoryWarrior[i]->setVisible(true);
	}
}

void HUDLayer::Update(ManagerComponent& i_manager)
{
	switch (m_typeMenu)
	{
		case StateTypeMenu::FACTORY_MACHINE:
		{	
			ShowMenuForFactoryMachine();
			m_typeMenu	= StateTypeMenu::NOTHING_MENU;
			m_command	= Command::CREATE_MACHINE;
			
			return;
		}
		case StateTypeMenu::FACTORY_WARRIOR:
		{
			ShowMenuForFactoryWarrior();
			m_typeMenu	= StateTypeMenu::NOTHING_MENU;
			m_command	= Command::CREATE_WARRIOR;
			
			return;
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
	if (m_vecRectSpritesFactoryWarrior[INDEX_KNIGHT_BLACK].containsPoint(m_locationTouch))
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

			m_commandMachine = CommandMachine::NOTHING_MACHINE;

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
			
			m_commandWarrior = HUDLayer::CommandWarrior::NOTHING_WARRIOR;

			break;
		}
		case HUDLayer::CREATE_KNIGHT_BRONZE:
		{
			STATE_WARRIOR _state = STATE_WARRIOR::START_KNIGHT_BRONZE;
			i_manager.m_managerFactory->GetListenFactoryWarrior().SetState(_state);

			m_commandWarrior = HUDLayer::CommandWarrior::NOTHING_WARRIOR;

			break;
		}
		case HUDLayer::CREATE_KNIGHT_SILVER:
		{
			STATE_WARRIOR _state = STATE_WARRIOR::START_KNIGHT_SILVER;
			i_manager.m_managerFactory->GetListenFactoryWarrior().SetState(_state);

			m_commandWarrior = HUDLayer::CommandWarrior::NOTHING_WARRIOR;

			break;
		}
		default:
			break;
	}
}

HUDLayer::~HUDLayer()
{

}