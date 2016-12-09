#include "HeroGraphicComponent.h"
#include "GameScene.h"
#include "constants.h"
#include "ManagerComponent.h"
#include "HeroInputComponent.h"
#include "AlgorithmLi.h"
#include "MapLayer.h"
#include "MessagingSystem.h"

const int CNT_COIN_FOR_START_KNIGHT_BLACK	= 50;
const int CNT_COIN_FOR_START_KNIGHT_BRONZE	= 50;
const int CNT_COIN_FOR_START_KNIGHT_SILVER	= 50;
const int CNT_COIN_FOR_START_TANK	= 90;
const int CNT_COIN_FOR_START_CAR	= 70;
const int CNT_COIN_FOR_START_FACTORY_MACHINE	= 300;
const int CNT_COIN_FOR_START_FACTORY_WARRIOR	= 250;

const int CNT_COINT_IN_BEGIN = 10000;

const int CNT_LENGTH_HERO_FROM_ORDER = 100;

const int INDEX_FIND_GOLD	= 0;
const int INDEX_FIND_OIL	= 1;

const Point CNT_POSITION_GOLD	= Point(800, 800);
const Point CNT_POSITION_OIL	= Point(600, 600);
const Point CNT_POSITION_TREE	= Point(700, 700);

const Point POSITION_BEGIN_HERO = Point(100, 100);

HeroGraphicComponent::HeroGraphicComponent()
{
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Hero/Walk_1.png");
	this->setPosition(GameScene::m_visibleSize.width / 2 - 50, GameScene::m_visibleSize.height / 2);
	
	m_coin				= CNT_COINT_IN_BEGIN;
	m_positionTarget	= Point::ZERO;
	m_stateHero			= StateHero::NOTHING;
	m_rectHero			= this->getBoundingBox();
}

HeroGraphicComponent::HeroGraphicComponent(MapLayer& i_parentMapLayer)
{
	i_parentMapLayer.addChild(this);
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Hero/Walk_1.png");

	GraphicComponent::LoadProperties(POSITION_BEGIN_HERO, i_parentMapLayer.getPosition());

	m_coin				= CNT_COINT_IN_BEGIN;
	m_positionTarget	= Point::ZERO;
	m_stateHero			= StateHero::NOTHING;
	m_loadProperties	= true;
}

HeroGraphicComponent::HeroGraphicComponent(HeroGraphicComponent& heroGraphicComponent)
{
	
}

bool HeroGraphicComponent::RunSearchWay(ManagerComponent& i_manager)
{
	Point _positionOriginMapLayer = this->getParent()->getPosition();
	_positionOriginMapLayer.x *= (-1);
	_positionOriginMapLayer.y *= (-1);
	AlgorithmLi* _searchWay = new AlgorithmLi(CNT_POSITION_FREE,
											_positionOriginMapLayer,
											this->getPosition(),
											m_positionTarget,
											i_manager.m_mapLayer->GetMapCoordinate());
	if (_searchWay->WayFound())
	{
		i_manager.m_inputComponent->SetZeroLocation();
		i_manager.m_mapLayer->ReleasePositionAfterSearchWay();
		std::copy(_searchWay->GetFoundWay().begin(), _searchWay->GetFoundWay().end(),
			std::back_inserter(m_vecWayWalkHero));
		m_iterInWayWalk = 0;
		
		delete _searchWay;

		return true;
	}
	return false;
}

/*virtual*/ void HeroGraphicComponent::Update(ManagerComponent& i_manager)
{
	switch (m_stateHero)
	{
		case HeroGraphicComponent::SEARCH_WAY:
		{
			if (RunSearchWay(i_manager))
			{
				m_stateHero = HeroGraphicComponent::WALK;
			}
			else
			{
				m_stateHero = HeroGraphicComponent::LISTEN;
			}

			break;
		}
		case HeroGraphicComponent::StateHero::WALK:
		{
			this->setPosition(m_vecWayWalkHero[m_iterInWayWalk]);
			if (++m_iterInWayWalk == m_vecWayWalkHero.size())
			{
				m_rectHero	=	this->getBoundingBox();
				m_stateHero = StateHero::NOTHING;
				m_vecWayWalkHero.clear();
			}
			break;
		}
		case HeroGraphicComponent::SEARCH_WAY_TO_RESOURCES:
		{
			if (RunSearchWay(i_manager))
			{
				HideMenu();
				m_stateHero = HeroGraphicComponent::GO_TO_RESOURCES;
			}
			else
			{
				m_stateHero = HeroGraphicComponent::LISTEN;
			}

			break;
		}
		case HeroGraphicComponent::GO_TO_RESOURCES:
		{
			this->setPosition(m_vecWayWalkHero[m_iterInWayWalk]);
			if (++m_iterInWayWalk == m_vecWayWalkHero.size())
			{
				m_rectHero	=	this->getBoundingBox();
				m_stateHero = StateHero::COME_AGAIN;
				--m_iterInWayWalk;
			}

			break;
		}
		case HeroGraphicComponent::COME_AGAIN:
		{
			this->setPosition(m_vecWayWalkHero[m_iterInWayWalk]);
			if (--m_iterInWayWalk == 0)
			{
				m_rectHero	= this->getBoundingBox();
				m_stateHero = StateHero::LISTEN;
				m_vecWayWalkHero.clear();
				AddMessage(i_manager);
			}
			
			break;
		}
		case HeroGraphicComponent::NOTHING:
		{
			if (TouchOnHero(i_manager))
			{
				if (!GoToTouchMouse(i_manager))
				{
					NeedShowMenu(i_manager);
				}
				i_manager.m_inputComponent->SetZeroLocation();
				m_stateHero = HeroGraphicComponent::LISTEN;
			}

			break; 
		}
		case HeroGraphicComponent::LISTEN:
		{
			m_locationTouch	= i_manager.m_inputComponent->GetLocationTouch();
			ConvertToOrigin(m_locationTouch);
			if (DetermineCommand())
			{	
				i_manager.m_inputComponent->SetZeroLocation();
				m_stateHero = HeroGraphicComponent::SEARCH_WAY_TO_RESOURCES;
			}				

			break;
		}

	default:
		break;
	}
}

void HeroGraphicComponent::AddMessage(ManagerComponent& i_manager)
{
	i_manager.m_messagingSystem->AddMesssage(m_textMessage);
	m_textMessage.clear();
}

bool HeroGraphicComponent::DetermineCommand()
{
	if (m_rectForSprites[INDEX_FIND_GOLD].containsPoint(m_locationTouch))
	{
		m_positionTarget	= CNT_POSITION_GOLD;
		m_textMessage		= "Gold: \t\t\t Need: \n  - 5 bronze warrior \n";
		return true;
	}
	else if (m_rectForSprites[INDEX_FIND_OIL].containsPoint(m_locationTouch))
	{
		m_locationTouch = CNT_POSITION_OIL;
		m_textMessage	= "Oil: \t\t\t Need: \n		- 3 bronze warrior \n";
		return true;
	}
	return false;
}

void HeroGraphicComponent::MoveUp()
{
	setPositionY(getPositionY() - CNT_SPEED_MAP);
	HideMenu();

	if (m_stateHero == HeroGraphicComponent::LISTEN)
	{
		m_stateHero = HeroGraphicComponent::NOTHING;
	}
}

void HeroGraphicComponent::MoveDown()
{
	setPositionY(getPositionY() + CNT_SPEED_MAP);
	HideMenu();

	if (m_stateHero == HeroGraphicComponent::LISTEN)
	{
		m_stateHero = HeroGraphicComponent::NOTHING;
	}
}

void HeroGraphicComponent::MoveRight()
{
	setPositionX(getPositionX() - CNT_SPEED_MAP);
	HideMenu();	

	if (m_stateHero == HeroGraphicComponent::LISTEN)
	{
		m_stateHero = HeroGraphicComponent::NOTHING;
	}
}

void HeroGraphicComponent::MoveLeft()
{
	setPositionX(getPositionX() + CNT_SPEED_MAP);
	HideMenu();

	if (m_stateHero == HeroGraphicComponent::LISTEN)
	{
		m_stateHero = HeroGraphicComponent::NOTHING;
	}
}

bool HeroGraphicComponent::TouchOnHero(ManagerComponent& i_manager)
{
	Point _currentLocationTouch		= i_manager.m_inputComponent->GetLocationTouch();
	Point _previousLocationTouch	= i_manager.m_inputComponent->GetPreviousLocationTouch();
	Point _positionMap				= i_manager.m_mapLayer->getPosition();
	if (_positionMap.x < 0)
	{
		_positionMap.x *= -1;
	}
	if (_positionMap.y < 0)
	{
		_positionMap.y *= -1;
	}
	m_rectHero = this->getBoundingBox();
	_currentLocationTouch	+= _positionMap;
	_previousLocationTouch	+= _positionMap;
	if (m_rectHero.containsPoint(_currentLocationTouch) || m_rectHero.containsPoint(_previousLocationTouch))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void HeroGraphicComponent::LoadNameSprites()
{
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Item/TasksHero/Gold.png");
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Item/TasksHero/Oil.png");
}

void HeroGraphicComponent::NeedShowMenu(ManagerComponent& i_manager)
{
	if (m_vecNameForSprites.empty())
	{
		LoadNameSprites();
		LoadSprites();
	}
	ReloadPosition();
	ShowMenu();
}

bool HeroGraphicComponent::GoToTouchMouse(ManagerComponent& i_manager)
{
	Vec2 _previousLocationTouch = i_manager.m_inputComponent->GetPreviousLocationTouch();
	Vec2 _currentLocationTouch = i_manager.m_inputComponent->GetLocationTouch();

	if (m_rectHero.containsPoint(_previousLocationTouch) && !m_rectHero.containsPoint(_currentLocationTouch))
	{
		Point _origin = this->getParent()->getPosition();
		_origin.x *= (-1);
		_origin.y *= (-1);
		_previousLocationTouch.x += _origin.x;
		_previousLocationTouch.y += _origin.y;
		if (m_rectHero.containsPoint(_previousLocationTouch))
		{
			m_positionTarget = _currentLocationTouch;
			m_positionTarget += _origin;
			return true;
		}

		m_positionTarget = _currentLocationTouch;
	}
	else
	{
		m_positionTarget = _currentLocationTouch;
		return false;
	}
}

void HeroGraphicComponent::ReloadPosition()
{
	m_positionVisible = this->getPosition();
	m_positionOrigin = this->getParent()->getPosition();

	if (m_positionOrigin.x < 0)
	{
		m_positionOrigin.x *= (-1);
	}
	if (m_positionOrigin.y < 0)
	{
		m_positionOrigin.y *= (-1);

	}

	m_locationTouch = Point::ZERO;

	Rect _box = this->getBoundingBox();

	// calculate RectOrigin(system coordinate all MapLayer)
	m_rectOrigin = Rect(this->getBoundingBox().getMinX() + m_positionOrigin.x, this->getBoundingBox().getMinY() + m_positionOrigin.y,
		this->getBoundingBox().size.width, this->getBoundingBox().size.height);
	// calculate RectVisible(system coordinate visible MapLayer)
	m_rectVisible = Rect(this->getBoundingBox().getMinX() + m_positionVisible.x, this->getBoundingBox().getMinY() + m_positionVisible.y,
		this->getBoundingBox().size.width, this->getBoundingBox().size.height);

	m_rectOriginWithVisible = Rect(this->getBoundingBox().getMinX() + m_positionOrigin.x + m_positionVisible.x,
		this->getBoundingBox().getMinY() + m_positionOrigin.y + m_positionVisible.y,
		this->getBoundingBox().size.width, this->getBoundingBox().size.height
		);

	m_numberComplete = 0;

	m_positionOriginWithVisible = m_positionOrigin + m_positionVisible;
}

/*virtual*/ void HeroGraphicComponent::ShowMenu()
{
	m_rectForSprites.clear();
	Point _positionHeroMenu = Point(m_positionVisible.x + (m_rectVisible.size.width / 2),
		m_positionVisible.y);
	for (int i = 0; i < m_vecSprites.size(); i++)
	{
		m_vecSprites[i]->setPosition(_positionHeroMenu);
		m_vecSprites[i]->setVisible(true);
		m_rectForSprites.push_back(m_vecSprites[i]->getBoundingBox());

		_positionHeroMenu.y -= m_vecSprites[i]->getBoundingBox().size.height / 2;
	}
}

bool HeroGraphicComponent::CheckToGoTarget(ManagerComponent& i_manager)
{
	Point _previousLocationTouch = i_manager.m_inputComponent->GetPreviousLocationTouch();
	Point _currentLocationTouch	= i_manager.m_inputComponent->GetLocationTouch();

	if (m_rectHero.containsPoint(_previousLocationTouch) && !m_rectHero.containsPoint(_currentLocationTouch))
	{
		m_positionTarget = _currentLocationTouch;
		return true;
	}
	else
	{
		Point _origin = this->getParent()->getPosition();
		_origin.x	*=	(-1);
		_origin.y	*=	(-1);
		_previousLocationTouch.x	+=	_origin.x;
		_previousLocationTouch.y	+=	_origin.y;
		if (m_rectHero.containsPoint(_previousLocationTouch))
		{
			m_positionTarget	=	_currentLocationTouch;
			m_positionTarget	+=	_origin;
			return true;
		}
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

/* Tasks on 08:11:2016
	- create army from knights and tanks;
	- create city for hero;
*/

/* Tasks on 31:10:2016
	+ add on HUDLayer all factory;
	+ add in factory ___all objects;
	+ add thread for search way:
		+ optimization search way;
	------ ATTENTION!|^|
	+ relasize	   it|||
				all	 |_|
*/