#include "HUDLayer.h"
#include "GameScene.h"
#include "ManagerComponent.h"
#include "HeroInputComponent.h"
#include "ManagerFactory.h"
#include "MachineFactory.h"
#include "WarriorFactory.h"
#include "MessagingScene.h"

const int INDEX_FACTORY_ENEMY_MACHINE	= 0;
const int INDEX_FACTORY_MACHINE			= 1;
const int INDEX_FACTORY_WARRIOR			= 2;
const int INDEX_FACTORY_ENEMY_WARRIOR	= 3;
const int INDEX_MESSAGES				= 4;

const int QUENTITY_COMBATANT_IN_BAR = 4;
const int QUENTITY_ELEMENT_CONTEXT_MENU = 4;

bool HUDLayer::init()
{
	if (!Layer::init())	
	{
		return false;
	}
	
	m_command			= Command::NOTHING;
	m_stateContextMenu	= StateContextMenu::NOT_ACTIVE;

	LoadSpritesCombatantBar();
	
	m_sprMessage = Sprite::create(CNT_PATH_TO_RESOURCES + "Item/Message/Message.png");
	m_sprMessage->setScale(GameScene::m_visibleSize.width / m_sprMessage->getContentSize().width / 15,
		GameScene::m_visibleSize.height / m_sprMessage->getContentSize().height / 15);
	m_sprMessage->setPosition(GameScene::m_visibleSize.width - m_sprMessage->getBoundingBox().size.width / 2,
		GameScene::m_visibleSize.height - m_sprMessage->getBoundingBox().size.height / 2);
	m_rectMessage = m_sprMessage->getBoundingBox();
	this->addChild(m_sprMessage);

	return true;
}

void HUDLayer::LoadSpritesCombatantBar()
{
	std::vector<float> _positionX;
	_positionX.push_back(50.0);
	_positionX.push_back(100.0);
	_positionX.push_back(150.0);
	_positionX.push_back(200.0);

	std::vector<std::string> _vecCombtants;
	_vecCombtants.push_back(CNT_PATH_TO_RESOURCES + "Warrior/black_knight/attack_1.png");
	_vecCombtants.push_back(CNT_PATH_TO_RESOURCES + "Warrior/bronze_knight/attack_1.png");
	_vecCombtants.push_back(CNT_PATH_TO_RESOURCES + "Warrior/silver_knight/attack_1.png");
	_vecCombtants.push_back(CNT_PATH_TO_RESOURCES + "Machine/Tank_1.png");

	for (int i = 0; i < _vecCombtants.size(); i++)
	{
		Sprite* _combatant = Sprite::create(_vecCombtants[i]);
		_combatant->setScale(GameScene::m_visibleSize.width / _combatant->getContentSize().width / 20,
			GameScene::m_visibleSize.height / _combatant->getContentSize().height / 20);
		_combatant->setPosition(_positionX[i], GameScene::m_visibleSize.height - _combatant->getBoundingBox().size.height / 2);
		this->addChild(_combatant);

		m_vecLabelCombatant.push_back(Label::create("0", "Herbana", 10));
		m_vecLabelCombatant[i]->setPosition(_combatant->getPositionX() + _combatant->getBoundingBox().size.width + m_vecLabelCombatant[i]->getContentSize().width / 2,
			GameScene::m_visibleSize.height - _combatant->getBoundingBox().size.height / 2);
		this->addChild(m_vecLabelCombatant[i]);
	}
}

void HUDLayer::LoadSpritesForMenu(Point i_locationMenu)
{
	float _locationY = i_locationMenu.y;

	std::vector<std::string> _filename;
	_filename.push_back(CNT_PATH_TO_RESOURCES + "HUDLayer/Factory/EnemyFactoryMachine.png");
	_filename.push_back(CNT_PATH_TO_RESOURCES + "HUDLayer/Factory/FactoryMachine.png");
	_filename.push_back(CNT_PATH_TO_RESOURCES + "HUDLayer/Factory/FactoryWarrior.png");
	_filename.push_back(CNT_PATH_TO_RESOURCES + "HUDLayer/Factory/EnemyFactoryWarrior.png");
	
	for (int i = 0; i < QUENTITY_ELEMENT_CONTEXT_MENU; i++)
	{
		Sprite* _factory = Sprite::create(_filename[i]);
		_factory->setScale(GameScene::m_visibleSize.width / _factory->getContentSize().width / 20,
			GameScene::m_visibleSize.height / _factory->getContentSize().height / 20);
		_locationY += _factory->getBoundingBox().size.height;
		_factory->setPosition(i_locationMenu.x, _locationY);
		m_vecSpriteMachine.push_back(_factory);
		m_vecRectMachine.push_back(_factory->getBoundingBox());
		this->addChild(_factory);
	}
}

void HUDLayer::UpdateQuentityCombatant(ManagerComponent& i_manager)
{
	if (m_vecQuentityCombatant.empty())
	{
		m_vecQuentityCombatant.push_back(i_manager.m_managerArmy->GetQuentityKnightBlack());
		m_vecQuentityCombatant.push_back(i_manager.m_managerArmy->GetQuentityKnightBronze());
		m_vecQuentityCombatant.push_back(i_manager.m_managerArmy->GetQuentityKnightSilver());
		m_vecQuentityCombatant.push_back(i_manager.m_managerMachine->GetQuentityTank());
	}
	else
	{
		m_vecQuentityCombatant[0] = i_manager.m_managerArmy->GetQuentityKnightBlack();
		m_vecQuentityCombatant[1] = i_manager.m_managerArmy->GetQuentityKnightBronze();
		m_vecQuentityCombatant[2] = i_manager.m_managerArmy->GetQuentityKnightSilver();
		m_vecQuentityCombatant[3] = i_manager.m_managerMachine->GetQuentityTank();
	}

	for (int i = 0; i < QUENTITY_COMBATANT_IN_BAR; i++)
	{
		m_vecLabelCombatant[i]->setString(std::to_string(m_vecQuentityCombatant[i]));
	}
}

void HUDLayer::VerifyOpenMessage(ManagerComponent& i_manager)
{
	if (m_rectMessage.containsPoint(i_manager.m_inputComponent->GetLocationTouch()))
	{
		m_command = Command::OPEN_MESSAGES;
		ExecuteCommandForManagerFactory(i_manager);
		i_manager.m_inputComponent->SetZeroLocation();
	}
}

void HUDLayer::Update(ManagerComponent& i_manager)
{
	UpdateQuentityCombatant(i_manager);
	VerifyOpenMessage(i_manager);

	switch (m_stateContextMenu)
	{
		case StateContextMenu::ACTIVE:
		{
			if ((m_locationTouch = i_manager.m_inputComponent->GetLocationTouch()) != Point::ZERO)
			{
				if (DetermineCommandForManagerFactory())
				{
					ExecuteCommandForManagerFactory(i_manager);
					i_manager.m_inputComponent->SetZeroLocation();
					HideContextMenu();
					m_stateContextMenu = StateContextMenu::NOT_ACTIVE;
				}
			}

			break;
		}
		case StateContextMenu::NOT_ACTIVE:
		{	
			if ((m_locationTouch = i_manager.m_inputComponent->GetLocationTouch()) != Point::ZERO)
			{
				if (ShowContextMenu(i_manager))
				{
					i_manager.m_inputComponent->SetZeroLocation();
					m_stateContextMenu = StateContextMenu::ACTIVE;
				}
			}

			break;
		}
	}
}

void HUDLayer::HideContextMenu()
{
	for (int i = 0; i < m_vecSpriteMachine.size(); i++)
	{
		m_vecSpriteMachine[i]->setVisible(false);
	}
}

bool HUDLayer::ShowContextMenu(ManagerComponent& i_manager)
{
	Point _prevLocationTouch = i_manager.m_inputComponent->GetPreviousLocationTouch();
	Point _currLocationTouch = i_manager.m_inputComponent->GetLocationTouch();

	if (((_prevLocationTouch.x - _currLocationTouch.x <= 10 && _prevLocationTouch.x - _currLocationTouch.x >= 0) || (_currLocationTouch.x - _prevLocationTouch.x <= 10 && _currLocationTouch.x - _prevLocationTouch.x >= 0)) &&
		((_prevLocationTouch.y - _currLocationTouch.y <= 10 && _prevLocationTouch.y - _currLocationTouch.y >= 0) || (_currLocationTouch.y - _prevLocationTouch.y <= 10 && _currLocationTouch.y - _prevLocationTouch.y >= 0))
		)
	{
		if (m_vecSpriteMachine.empty())
		{
			LoadSpritesForMenu(_currLocationTouch);
		}
		else
		{
			float _locationY = _currLocationTouch.y;
			m_vecRectMachine.clear();
			for (int i = 0; i < m_vecSpriteMachine.size(); i++)
			{
				_locationY += m_vecSpriteMachine[i]->getBoundingBox().size.height;
				m_vecSpriteMachine[i]->setPosition(_currLocationTouch.x, _locationY);
				m_vecSpriteMachine[i]->setVisible(true);
				m_vecRectMachine.push_back(m_vecSpriteMachine[i]->getBoundingBox());
			}
		}
		
		return true;
	}
	else
	{
		return false;
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

void HUDLayer::OpenMessages()
{
	auto _messagingScene = MessagingScene::createScene();

	srand(time(NULL));
	auto reScene = TransitionFade::create(2.0f, _messagingScene, Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));
	Director::getInstance()->pushScene(_messagingScene);
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
		case Command::OPEN_MESSAGES:
		{
			OpenMessages();

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