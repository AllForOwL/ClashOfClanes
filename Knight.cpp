#include "Knight.h"
#include "GameScene.h"
#include "MapLayer.h"
#include "ManagerComponent.h"
#include "HeroInputComponent.h"
#include "AlgorithmLi.h"
#include "AIAct.h"
#include "AIDirection.h"
#include "HeroGraphicComponent.h"

const int INDEX_TASK_GOLD	= 0;
const int INDEX_TASK_OIL	= 1;
const int INDEX_TASK_TREE	= 2;

const Point	CNT_POSITION_SHELTER = Point(700, 700);

const int CNT_ATTACK	= 0;
const int CNT_RUN		= 1;
const int CNT_WANDER	= 2;
const int CNT_HIDE		= 3;

const Point CNT_POSITION_GOLD	= Point(200, 200);
const Point CNT_POSITION_OIL	= Point(400, 400);
const Point CNT_POSITION_TREE	= Point(600, 600);

Knight::Knight()
{

} 

Knight::Knight(Point i_positionVisible, MapLayer& i_parentMapLayer, std::string i_fileWarrior) : Warrior(i_positionVisible, i_parentMapLayer, i_fileWarrior)
{		
	m_spear			= true;
	m_locationTouch = Point::ZERO;
}

Knight::Knight(Knight& Knight)
{
	
}

int Knight::GetAct(ManagerComponent&	i_manager)
{
	double _spear	= 0.0;
	double	_enemy	= i_manager.m_mapLayer->GetQuentityEnemy(this->getPosition());
	if (m_spear)
	{
		_spear = 1.0;
	}
	double _health	=	0.0;
	if (m_health >= 75)
	{
		_health	= 2.0;
	}
	else if (m_health >= 35)
	{
		_health	= 1.0;
	}
	int	_actWander = i_manager.m_AIAct->FindAct(_health, _spear, _enemy);

	return _actWander;
}

void Knight::FindResources(ManagerComponent& i_manager, Point i_positionTarget)
{
	Point _positionOriginMapLayer = this->getParent()->getPosition();
	_positionOriginMapLayer.x *= (-1);
	_positionOriginMapLayer.y *= (-1);

	AlgorithmLi* _searchWay = new AlgorithmLi( CNT_OBJECT_KNIGHT_BLACK,
												_positionOriginMapLayer,
												this->getPosition(),
												i_positionTarget,
												i_manager.m_mapLayer->GetMapCoordinate()
											 );

	if (_searchWay->WayFound())
	{
		i_manager.m_inputComponent->SetZeroLocation();
		i_manager.m_mapLayer->ReleasePositionAfterSearchWay();
		std::copy(_searchWay->GetFoundWay().begin(), _searchWay->GetFoundWay().end(),
			std::back_inserter(m_vecWayWalkKnight));
		m_iterInWayWalk = 0;

		m_state = Combatant::GOES_TO_TARGET;
	}

	delete _searchWay;
}

/*virtual*/ void Knight::Update(ManagerComponent& i_manager)
{
	switch (m_state)
	{
		case StateCombatant::GOES_TO_TARGET:
		{
			// here has been code verify position { m_state = StateCombatant::VERIFY_STATUS_POSITION; }
			this->setPosition(m_vecWayWalkKnight[m_iterInWayWalk]);
			if (++m_iterInWayWalk == m_vecWayWalkKnight.size())
			{
				--m_iterInWayWalk;
				LoadProperties(this->getPosition(), i_manager.m_mapLayer->getPosition());
				m_state = StateCombatant::GOES_BACK;
			}

			break;
		}
		case StateCombatant::GOES_BACK:
		{
			this->setPosition(m_vecWayWalkKnight[m_iterInWayWalk]);
			if (--m_iterInWayWalk == 0)
			{
				LoadProperties(this->getPosition() + this->getParent()->getPosition(), i_manager.m_mapLayer->getPosition());
				m_state	=	StateCombatant::LISTEN;
				m_vecWayWalkKnight.clear();
			}

			break;											
		}
		case StateCombatant::VERIFY_STATUS_POSITION:
		{
			int	_statusAct = 3; //GetAct(i_manager);

			if (_statusAct == CNT_ATTACK)
			{
				m_state	= StateCombatant::ACT_ATTACK;
			}
			else if (_statusAct == CNT_RUN)
			{
				m_state	= StateCombatant::ACT_RUN;
			}
			else if (_statusAct	== CNT_WANDER)
			{
				m_state	= StateCombatant::GOES_TO_TARGET;
			}
			else
			{
				m_state	= StateCombatant::ACT_HIDE;
			}

			break;
		}
		case StateCombatant::FIND_GOLD:
		{
			FindResources(i_manager, CNT_POSITION_GOLD);

			break;
		}
		case StateCombatant::FIND_OIL:
		{
			FindResources(i_manager, CNT_POSITION_OIL);
	
			break;
		}
		case StateCombatant::FIND_TREE:
		{
			FindResources(i_manager, CNT_POSITION_TREE);

			break;
		}
		case StateCombatant::MOVE_FORWARD:
		{
			MoveForward();
			m_state = StateCombatant::FIND_ACT;

			break;
		}
		case StateCombatant::MOVE_BACK:
		{
			MoveBack();
			m_state = StateCombatant::FIND_ACT;

			break;
		}
		case StateCombatant::MOVE_RIGHT:
		{
			MoveRight();
			m_state = StateCombatant::FIND_ACT;

			break;
		}
		case StateCombatant::MOVE_LEFT:
		{
			MoveLeft();
			m_state = StateCombatant::FIND_ACT;

			break;
		}
		case StateCombatant::FIND_ACT:
		{
			SetStatusPositionForCurrentDirection(i_manager);
			UpdateDirection(i_manager);

			break;
		}
		case StateCombatant::ACT_ATTACK:
		{
			/*
				Changes sprites
			*/
			m_state	=	StateCombatant::GOES_TO_TARGET;

			break;
		}
		case StateCombatant::ACT_RUN:
		{
			MoveBack();

			++m_iterInWayWalk;
			if (m_iterInWayWalk == 20)
			{
				m_state = StateCombatant::FIND_ACT;
			}

			break;
		}
		case StateCombatant::ACT_HIDE:
		{
			Point	_positionParent	=	this->getParent()->getPosition();
			_positionParent.x	*=	(-1);
			_positionParent.y	*=	(-1);

			Point	_positionShelter = i_manager.m_mapLayer->GetPositionShelter();

			AlgorithmLi* _wayToShelter = new AlgorithmLi( CNT_OBJECT_SHELTER,
														  _positionParent,
														  this->getPosition(),
														  CNT_POSITION_SHELTER,
														  i_manager.m_mapLayer->GetMapCoordinate()
														 );

			if (_wayToShelter->WayFound())
			{
				i_manager.m_inputComponent->SetZeroLocation();
				i_manager.m_mapLayer->ReleasePositionAfterSearchWay();
				std::copy(_wayToShelter->GetFoundWay().begin(), _wayToShelter->GetFoundWay().end(),
					std::back_inserter(m_vecWayWalkKnight));
				m_iterInWayWalk = 0;

				m_state = StateCombatant::GOES_TO_TARGET;
			}
			m_state	=	StateCombatant::GOES_TO_TARGET;

			break;
		}
		case StateCombatant::NOTHING:
		{
			m_locationTouch	= i_manager.m_inputComponent->GetLocationTouch();
			m_locationTouch += (i_manager.m_mapLayer->getPosition() * -1);
			ConvertToOrigin(m_locationTouch);
			if (m_rectOriginWithVisible.containsPoint(m_locationTouch))
			{
				if (m_vecNameForSprites.empty())
				{
					LoadNameForSprites();
					LoadSprites();
				}

				ShowMenu();
				LoadPosition();
				m_state	= StateCombatant::LISTEN;
				i_manager.m_inputComponent->SetZeroLocation();
			}

			break;
		}
		case StateCombatant::LISTEN:
		{
			m_locationTouch	= i_manager.m_inputComponent->GetLocationTouch();
			ConvertToOrigin(m_locationTouch);
			if (DetermineCommand())
			{	
				i_manager.m_inputComponent->SetZeroLocation();
			}

			break;
		}
	default:
		break;
	}
}

void Knight::LoadNameForSprites()
{
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Item/TasksKnight/Gold.png");
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Item/TasksKnight/Oil.png");
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Item/TasksKnight/Tree.png");
}

bool Knight::DetermineCommand()
{
	if (m_rectForSprites[INDEX_TASK_GOLD].containsPoint(m_locationTouch))
	{
		m_state = StateCombatant::FIND_GOLD;
		return true;
	}
	else if (m_rectForSprites[INDEX_TASK_OIL].containsPoint(m_locationTouch))
	{
		m_state = StateCombatant::FIND_OIL;
		return true;
	}
	else if (m_rectForSprites[INDEX_TASK_TREE].containsPoint(m_locationTouch))
	{
		m_state = StateCombatant::FIND_TREE;
		return true;
	}
	return false;
}

Knight::~Knight()
{
	CCLOG("destructor Knight");
}

/*  GraphicComponent	- тільки малює спрайти 
	PhysicsComponent	- виявлє зіткнення героя
	InputComponent		- приймає дії з клавіатури
	ManagerComponent	- контейнер для цих компонентів
*/

/*
	Tasks on 10:11:2016
		+ good understand algorithm;
		+ optimize for knight;

	Tasks on 11:11:2016					!-!-!-(Day Enemy!!!!!)-!-!-!
		+ create factory for enemy(warrior and machine);
		// create manager factory for enemy????;(not need)
		+ create enemy;
		
		|
		|			Tasks on 12:11:2016
  ------|------		step for execute AI in game:
		|				+ fill region for each objects;
		|				+ need add AI for act---> Wander <---;

		Tasks on 13:11:2016
			+ Execute AI;

		Tasks on 14:11:2016
			+ add AI for all objects;

		Tasks on 15:11:2016
			- create and realize possibility add for knight tasks ():
				+ list tasks:
					- find gold;
					- find tree;
					- find oil;
				- add on map region from recources for execute tasks:
					+ fill region for each type resources;
					+ show tasks when click on hero
					 (!!! add positionWarrior in her constructor;)
				+ each hero responsible zone on map(gold, tree and etc.);
				+ hero add on mapLayer;
				+ knight goes to zone from resources and back;
			When hero goes find gold, tree, oil(LI):
				+ verify status;
				+ realize all act(for attack need sprite);
				+ look enemy her need assess the situation(AI);
			+ add act : 
			{
				- attack;
				- run;
				- hide;
				- wander;
			};

		Tasks on 28:11:2016
			+- write sniffer!!!;
			- refactoring ALL CODE!!!!!
			- add object after load game:
				+ write new code !!!necessarily!!!;
				+ solution:
					___write in file for object visible and origin position;
			+ save game, write mapCoordinate in xml!!!

			Tasks on 03:12:2016
			 + load object from file;
			 + refactoring All code;
			 
			 Tasks on 04:12:2016
			 + Refactoring;
			 - refactoring All code;

			 Tasks on 05:12:2016
			 - mission 1:
				+ find and create factory(for hero);
					+ factory:
						+ gold;
						+ oil;

			Tasks on 8:12:2016
				- when click on field show menu from lists factory;
*/