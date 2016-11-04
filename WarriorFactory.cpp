#include "WarriorFactory.h"
#include "ManagerComponent.h"
#include "HeroGraphicComponent.h"
#include "GameScene.h"
#include "GraphicComponent.h"
#include "ManagerArmy.h"
#include "constants.h"
#include "HeroInputComponent.h"
#include "HUDLayer.h"
#include "MapLayer.h"

const int CNT_TIME_FOR_COMPLETE_KNIGHT_BLACK	= 10;
const int CNT_TIME_FOR_COMPLETE_KNIGHT_BRONZE	= 15;
const int CNT_TIME_FOR_COMPLETE_KNIGHT_SILVER	= 20;

const int INDEX_KNIGHT_BLACK	= 0;
const int INDEX_KNIGHT_BRONZE	= 1;
const int INDEX_KNIGHT_SILVER	= 2;

WarriorFactory::WarriorFactory()
{

}

WarriorFactory::WarriorFactory(MapLayer& i_mapLayer)
{
	i_mapLayer.addChild(this);
	
	Point _positionParent = this->getParent()->getPosition();
	
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Home/render4.png");
	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 6,
		GameScene::m_visibleSize.height / this->getContentSize().height / 6);

	m_stateWarrior	= StateFactoryWarrior::NOTHING;
	m_locationTouch = Point::ZERO;
	//m_rectFactory.setRect(this->getBoundingBox().getMinX() + _positionMap.x, this->getBoundingBox().getMinY() + _positionMap.y,
	//	this->getBoundingBox().getMaxX() + _positionMap.x, this->getBoundingBox().getMaxY() + _positionMap.y);
	m_rectFactory			= this->getBoundingBox();
	//m_rectFactory.setRect()
	m_numberWarriorComplete = 0;

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
		m_vecSpritesForFactoryWarrior[i]->setVisible(false);
		this->getParent()->addChild(m_vecSpritesForFactoryWarrior[i]);
	}
}

void WarriorFactory::ShowMenu()
{
	Point _positionMap = this->getParent()->getPosition();
	if (_positionMap.x < 0)
	{
		_positionMap.x *= -1;
	}
	if (_positionMap.y < 0)
	{
		_positionMap.y *= -1;
	}

	float _positionY = GameScene::m_visibleSize.height / 2;
	for (int i = 0; i < m_vecSpritesForFactoryWarrior.size(); i++)
	{
		Point _position = Point(GameScene::m_visibleSize.width - m_vecSpritesForFactoryWarrior[i]->getBoundingBox().size.width + _positionMap.x,
			_positionY + _positionMap.y);

		m_vecSpritesForFactoryWarrior[i]->setPosition(_position);
		m_vecSpritesForFactoryWarrior[i]->setVisible(true);
		_positionY -= 30;
		_positionMap.x *= -1;
		_positionMap.y *= -1;
		Rect _temp = Rect(	m_vecSpritesForFactoryWarrior[i]->getBoundingBox().getMinX() + _positionMap.x, 
							m_vecSpritesForFactoryWarrior[i]->getBoundingBox().getMinY() + _positionMap.y,
							m_vecSpritesForFactoryWarrior[i]->getBoundingBox().getMaxX() + _positionMap.x,
							m_vecSpritesForFactoryWarrior[i]->getBoundingBox().getMaxY() + _positionMap.y
						);
		m_rectForSpritesWarrior.push_back(_temp);
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

void WarriorFactory::LoadPositionWarrior()
{
	Point _positionMap = this->getParent()->getPosition();
	_positionMap.x *= -1;
	_positionMap.y *= -1;

	Point _positionFactory = Point(m_rectFactory.getMinX() + _positionMap.x, m_rectFactory.getMinY() + _positionMap.y);
	_positionFactory.y -= 10;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			m_vecPositionWarrior.push_back(Point(_positionFactory));
			_positionFactory.x += 40;
		}
		_positionFactory.y += 40;
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
				m_stateWarrior = StateFactoryWarrior::LISTEN;
				i_manager.m_managerArmy->SetState(m_stateTypeAddWarrior);
				i_manager.m_managerArmy->SetPositionForWarrior(m_vecPositionWarrior[m_numberWarriorComplete]);
				++m_numberWarriorComplete;
			}
			break;
		}
		case StateFactoryWarrior::NOTHING:
		{
			Point _positionMap = this->getParent()->getPosition();
			m_rectFactory.setRect(this->getBoundingBox().getMinX() + _positionMap.x, this->getBoundingBox().getMinY() + _positionMap.y,
				this->getBoundingBox().getMaxX() + _positionMap.x, this->getBoundingBox().getMaxY() + _positionMap.y);
			m_locationTouch = i_manager.m_inputComponent->GetLocationTouch();
			if (m_rectFactory.containsPoint(m_locationTouch) && m_locationTouch != Point::ZERO)
			{
				LoadPositionWarrior();
				ShowMenu();
				m_stateWarrior = StateFactoryWarrior::LISTEN;
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
			//else if (m_locationTouch != Point::ZERO)
			//{
				//HideMenu();
			//	m_stateWarrior = StateFactoryWarrior::NOTHING;
			//}
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
