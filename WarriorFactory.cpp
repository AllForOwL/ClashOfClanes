#include "WarriorFactory.h"
#include "ManagerComponent.h"
#include "HeroGraphicComponent.h"
#include "GameScene.h"
#include "GraphicComponent.h"
#include "ManagerArmy.h"
#include "constants.h"
#include "HeroInputComponent.h"
#include "HUDLayer.h"

const int CNT_TIME_FOR_COMPLETE_KNIGHT_BLACK	= 10;
const int CNT_TIME_FOR_COMPLETE_KNIGHT_BRONZE	= 15;
const int CNT_TIME_FOR_COMPLETE_KNIGHT_SILVER	= 20;

const int INDEX_KNIGHT_BLACK	= 0;
const int INDEX_KNIGHT_BRONZE	= 1;
const int INDEX_KNIGHT_SILVER	= 2;

WarriorFactory::WarriorFactory()
{

}

WarriorFactory::WarriorFactory(GameScene& i_parentGameScene)
{
	i_parentGameScene.addChild(this);
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Home/render4.png");
	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 6,
		GameScene::m_visibleSize.height / this->getContentSize().height / 6);
	this->setPosition(GameScene::m_visibleSize.width / 2 + 50, GameScene::m_visibleSize.height / 2);
	this->setZOrder(1);

	m_stateWarrior	= StateFactoryWarrior::NOTHING;
	m_locationTouch = Point::ZERO;
	m_rectFactory	= this->getBoundingBox();

	LoadNameForSprites();
	LoadSprites();
}

WarriorFactory::WarriorFactory(WarriorFactory& i_warriorFactory)
{

}

void WarriorFactory::LoadNameForSprites()
{
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Warrior/black_knight/attack_1.png");
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Warrior/bronze_knight/attack_1.png");
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Warrior/silver_knight/attack_1.png");
}

void WarriorFactory::LoadSprites()
{
	float _positionY = GameScene::m_visibleSize.height / 2;
	for (int i = 0; i < m_vecNameForSprites.size(); i++)
	{
		m_vecSpritesForFactoryWarrior.push_back(Sprite::create(m_vecNameForSprites[i]));
		m_vecSpritesForFactoryWarrior[i]->setScale(GameScene::m_visibleSize.width / m_vecSpritesForFactoryWarrior[i]->getContentSize().width / 8,
			GameScene::m_visibleSize.height / m_vecSpritesForFactoryWarrior[i]->getContentSize().height / 8);
		m_vecSpritesForFactoryWarrior[i]->setPosition(GameScene::m_visibleSize.width - m_vecSpritesForFactoryWarrior[i]->getBoundingBox().size.width,
			_positionY);
		m_vecSpritesForFactoryWarrior[i]->setVisible(false);
		this->getParent()->addChild(m_vecSpritesForFactoryWarrior[i]);

		_positionY -= m_vecSpritesForFactoryWarrior[i]->getBoundingBox().size.height;
		m_rectForSpritesWarrior.push_back(m_vecSpritesForFactoryWarrior[i]->getBoundingBox());
	}
}

void WarriorFactory::ShowMenu()
{
	for (int i = 0; i < m_vecSpritesForFactoryWarrior.size(); i++)
	{
		m_vecSpritesForFactoryWarrior[i]->setVisible(true);
	}
}

void WarriorFactory::HideMenu()
{
	for (int i = 0; i < m_vecSpritesForFactoryWarrior.size(); i++)
	{
		m_vecSpritesForFactoryWarrior[i]->setVisible(false);
	}
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
	switch (m_stateWarrior)
	{
		case StateFactoryWarrior::START_KNIGHT_BLACK:
		{
			if (i_manager.m_hero->CheckProductionKnightBlack())
			{
				m_timeForCompleteWarrior	= CNT_TIME_FOR_COMPLETE_KNIGHT_BLACK;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateWarrior				= StateFactoryWarrior::WORKING;
				m_stateTypeAddWarrior		= ManagerArmy::StateManagerArmy::ADD_KNIGHT_BLACK;
			}

			break;
		}
		case StateFactoryWarrior::START_KNIGHT_BRONZE:
		{
			if (i_manager.m_hero->CheckProductionKnightBronze())
			{
				m_timeForCompleteWarrior	= CNT_TIME_FOR_COMPLETE_KNIGHT_BRONZE;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateWarrior				= StateFactoryWarrior::WORKING;
				m_stateTypeAddWarrior		= ManagerArmy::StateManagerArmy::ADD_KNIGHT_BRONZE;
			}

			break;
		}
		case StateFactoryWarrior::START_KNIGHT_SILVER:
		{
			if (i_manager.m_hero->CheckProductionKnightSilver())
			{
				m_timeForCompleteWarrior	= CNT_TIME_FOR_COMPLETE_KNIGHT_SILVER;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateWarrior				= StateFactoryWarrior::WORKING;
				m_stateTypeAddWarrior		= ManagerArmy::StateManagerArmy::ADD_KNIGHT_SILVER;
			}

			break;
		}
		case StateFactoryWarrior::WORKING:
		{
			if (isComplete())
			{
				m_stateWarrior = StateFactoryWarrior::NOTHING;
				i_manager.m_managerArmy->SetState(m_stateTypeAddWarrior);
			}
			break;
		}
		case StateFactoryWarrior::NOTHING:
		{
			m_locationTouch = i_manager.m_inputComponent->GetLocationTouch();
			if (m_rectFactory.containsPoint(m_locationTouch))
			{
				ShowMenu();
				m_stateWarrior	= StateFactoryWarrior::LISTEN;
				i_manager.m_inputComponent->SetZeroLocation();
			}
			break;
		}
		case StateFactoryWarrior::LISTEN:
		{
			m_locationTouch = i_manager.m_inputComponent->GetLocationTouch();
			if (DetermineCommand())
			{
				i_manager.m_inputComponent->SetZeroLocation();
			}
			else if (m_locationTouch != Point::ZERO)
			{
				HideMenu();
				m_stateWarrior = StateFactoryWarrior::NOTHING;
			}
			break;
		}
	default:
		break;
	}
}

bool WarriorFactory::DetermineCommand()
{
	if (m_rectForSpritesWarrior[INDEX_KNIGHT_BLACK].containsPoint(m_locationTouch))
	{
		m_stateWarrior = StateFactoryWarrior::START_KNIGHT_BLACK;
		return true;
	}
	else if (m_rectForSpritesWarrior[INDEX_KNIGHT_BRONZE].containsPoint(m_locationTouch))
	{
		m_stateWarrior = StateFactoryWarrior::START_KNIGHT_BRONZE;
		return true;
	}
	else if (m_rectForSpritesWarrior[INDEX_KNIGHT_SILVER].containsPoint(m_locationTouch))
	{
		m_stateWarrior = StateFactoryWarrior::START_KNIGHT_SILVER;
		return true;
	}
	return false;
}

using STATE_FACTORY = WarriorFactory::StateFactoryWarrior;
void WarriorFactory::SetState(STATE_FACTORY& i_stateWarrior)
{
	m_stateWarrior = i_stateWarrior;
}

WarriorFactory::StateFactoryWarrior& WarriorFactory::GetStateWarrior()
{
	return m_stateWarrior;
}

WarriorFactory::~WarriorFactory()
{

}
