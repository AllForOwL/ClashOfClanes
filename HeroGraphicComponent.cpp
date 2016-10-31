#include "HeroGraphicComponent.h"
#include "GameScene.h"
#include "constants.h"
#include "ManagerComponent.h"
#include "HeroInputComponent.h"
#include "AlgorithmLi.h"
#include "MapLayer.h"

const int CNT_COIN_FOR_START_KNIGHT_BLACK	= 50;
const int CNT_COIN_FOR_START_KNIGHT_BRONZE	= 50;
const int CNT_COIN_FOR_START_KNIGHT_SILVER	= 50;
const int CNT_COIN_FOR_START_TANK	= 90;
const int CNT_COIN_FOR_START_CAR	= 70;
const int CNT_COIN_FOR_START_FACTORY_MACHINE	= 300;
const int CNT_COIN_FOR_START_FACTORY_WARRIOR	= 250;

const int CNT_COINT_IN_BEGIN = 1000;

const int CNT_LENGTH_HERO_FROM_ORDER = 100;

HeroGraphicComponent::HeroGraphicComponent()
{
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Hero/Walk_1.png");
	this->setPosition(GameScene::m_visibleSize.width / 2 - 50, GameScene::m_visibleSize.height / 2);
	this->setZOrder(1);
	
	m_coin				= CNT_COINT_IN_BEGIN;
	m_positionTarget	= Point::ZERO;
	m_stateHero			= StateHero::NOTHING;
	m_rectHero			= this->getBoundingBox();
}

HeroGraphicComponent::HeroGraphicComponent(GameScene& i_parentGameScene)
{
	i_parentGameScene.addChild(this);
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Hero/Walk_1.png");
	this->setPosition(GameScene::m_visibleSize.width / 2, GameScene::m_visibleSize.height / 2);
	this->setZOrder(1);

	m_coin				= CNT_COINT_IN_BEGIN;
	m_positionTarget	= Point::ZERO;
	m_stateHero			= StateHero::NOTHING;
	m_rectHero			= this->getBoundingBox();
}

HeroGraphicComponent::HeroGraphicComponent(HeroGraphicComponent& heroGraphicComponent)
{
	
}

/*virtual*/ void HeroGraphicComponent::Update(ManagerComponent& i_manager)
{
	switch (m_stateHero)
	{
		case HeroGraphicComponent::SEARCH_WAY:
		{
			AlgorithmLi* _searchWay = new AlgorithmLi(this->getPosition(), m_positionTarget, i_manager.m_mapLayer->GetMapCoordinate());
			if (_searchWay->WayFound())
			{
				i_manager.m_inputComponent->SetZeroLocation();
				i_manager.m_mapLayer->ReleasePositionAfterSearchWay();
				std::copy(_searchWay->GetFoundWay().begin(), _searchWay->GetFoundWay().end(), std::back_inserter(m_vecWayWalkHero));
				m_iterInWayWalk = m_vecWayWalkHero.size() - 1;

				m_stateHero = HeroGraphicComponent::WALK;
			}
			
			delete _searchWay;

			break;
		}
		case HeroGraphicComponent::StateHero::WALK:
		{
			//if (this->getPositionX() == m_vecWayWalkHero[m_iterInWayWalk].x)
			//{
			//	int _positionY = i_manager.m_mapLayer->getPositionY();
			//	if (this->getPositionY() > m_vecWayWalkHero[m_iterInWayWalk].y)
			//	{
			//		i_manager.m_mapLayer->setPositionY(_positionY - 1);
			//		//this->getParent()->setPositionY(this->getParent()->getPositionY() + 1);
			//	}
			//	else
			//	{
			//		i_manager.m_mapLayer->setPositionY(_positionY + 1);
			//		//this->getParent()->setPositionY(this->getParent()->getPositionY() - 1);
			//	}
			//}
			//else
			//{
			//	int _positionX = i_manager.m_mapLayer->getPositionX();
			//	if (this->getPositionX() > m_vecWayWalkHero[m_iterInWayWalk].x)
			//	{
			//		i_manager.m_mapLayer->setPositionX(_positionX - 1);
			//		//this->getParent()->setPositionX(this->getParent()->getPositionX() + 1);
			//	}
			//	else
			//	{
			//		i_manager.m_mapLayer->setPositionX(_positionX + 1);
			//		//this->getParent()->setPositionX(this->getParent()->getPositionX() - 1);
			//	}
			//}
			
			this->setPosition(m_vecWayWalkHero[m_iterInWayWalk]);
			if (--m_iterInWayWalk < 0)
			{
				m_stateHero = StateHero::NOTHING;
				m_vecWayWalkHero.clear();
				m_rectHero = this->getBoundingBox();
			}
			break;
		}
		case HeroGraphicComponent::NOTHING:
		{
			if (CheckToGoTarget(i_manager))
			{
				m_stateHero  = StateHero::SEARCH_WAY;
			}

			break; 
		}
	default:
		break;
	}
}

bool HeroGraphicComponent::CheckToGoTarget(ManagerComponent& i_manager)
{
	Vec2 _previousLocationTouch = i_manager.m_inputComponent->GetPreviousLocationTouch();
	Vec2 _currentLocationTouch	= i_manager.m_inputComponent->GetLocationTouch();

	if (m_rectHero.containsPoint(_previousLocationTouch))
	{
		m_positionTarget = _currentLocationTouch;

		return true;
	}
	return false;
}

bool HeroGraphicComponent::CheckProductionKnightBlack()
{
	if (m_coin >= CNT_COIN_FOR_START_KNIGHT_BLACK)
	{
		m_coin -= CNT_COIN_FOR_START_KNIGHT_BLACK;
		return true;
	}
	return false;
}

bool HeroGraphicComponent::CheckProductionKnightBronze()
{
	if (m_coin >= CNT_COIN_FOR_START_KNIGHT_BRONZE)
	{
		m_coin -= CNT_COIN_FOR_START_KNIGHT_BRONZE;
		return true;
	}
	return false;
}

bool HeroGraphicComponent::CheckProductionKnightSilver()
{
	if (m_coin >= CNT_COIN_FOR_START_KNIGHT_SILVER)
	{
		m_coin -= CNT_COIN_FOR_START_KNIGHT_SILVER;
		return true;
	}
	return false;
}

bool HeroGraphicComponent::CheckProductionTank()
{
	if (m_coin >= CNT_COIN_FOR_START_TANK)
	{
		m_coin -= CNT_COIN_FOR_START_TANK;
		return true;
	}
	else
	{
		return false;
	}
}

bool HeroGraphicComponent::CheckProductionCar()
{
	if (m_coin >= CNT_COIN_FOR_START_CAR)
	{
		m_coin -= CNT_COIN_FOR_START_CAR;
		return true;
	}
	else
	{
		return true;
	}
}

bool HeroGraphicComponent::CheckProductionFactoryMachine()
{
	if (m_coin >= CNT_COIN_FOR_START_FACTORY_MACHINE)
	{
		m_coin -= CNT_COIN_FOR_START_FACTORY_MACHINE;
		return true;
	}
	else
	{
		return false;
	}
}

bool HeroGraphicComponent::CheckProductionFactoryWarrior()
{
	if (m_coin >= CNT_COIN_FOR_START_FACTORY_WARRIOR)
	{
		m_coin -= CNT_COIN_FOR_START_FACTORY_WARRIOR;
		return true;
	}
	else
	{
		return false;
	}
}



HeroGraphicComponent::~HeroGraphicComponent()
{
	CCLOG("destructor herographic");
}

/*  GraphicComponent	- тільки малює спрайти 
	PhysicsComponent	- виявлє зіткнення героя
	InputComponent		- приймає діна з клавіатури
	ManagerComponent	- контейнер для цих компонентів
*/

/* Tasks on 31:10:2016
	- add on HUDLayer all factory;
	- add in factory ___all objects;
	- add thread for search way;
	------ ATTENTION!|^|
	- relasize	   it|||
				all	 |_|
*/