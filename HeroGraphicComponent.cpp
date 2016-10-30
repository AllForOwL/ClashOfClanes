#include "HeroGraphicComponent.h"
#include "GameScene.h"
#include "constants.h"
#include "ManagerComponent.h"
#include "HeroInputComponent.h"

const int CNT_COIN_FOR_START_ARCHER = 50;
const int CNT_COIN_FOR_START_TANK	= 90;
const int CNT_COIN_FOR_START_CAR	= 70;
const int CNT_COIN_FOR_START_FACTORY_MACHINE	= 300;
const int CNT_COIN_FOR_START_FACTORY_WARRIOR	= 250;

const int CNT_COINT_IN_BEGIN = 1000;

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
	this->setPosition(GameScene::m_visibleSize.width / 2 - 50, GameScene::m_visibleSize.height / 2);
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
		case HeroGraphicComponent::WALK:
		{
			// here has been algorithm search

			break;
		}
		case HeroGraphicComponent::NOTHING:
		{
			if (CheckToGoTarget(i_manager))
			{
				m_stateHero  = StateHero::WALK;
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
		i_manager.m_inputComponent->SetZeroLocation();

		return true;
	}
	return false;
}

bool HeroGraphicComponent::CheckProductionArcher()
{
	if (m_coin >= CNT_COIN_FOR_START_ARCHER)
	{
		m_coin -= CNT_COIN_FOR_START_ARCHER;
		return true;
	}
	else
	{
		return false;
	}
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