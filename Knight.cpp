#include "Knight.h"
#include "GameScene.h"
#include "MapLayer.h"
#include "ManagerComponent.h"
#include "HeroInputComponent.h"

const int INDEX_TASK_GOLD	= 0;
const int INDEX_TASK_OIL	= 1;
const int INDEX_TASK_TREE	= 2;

Knight::Knight()
{

} 

Knight::Knight(std::string i_knight, MapLayer& i_parentMapLayer) : Warrior(i_parentMapLayer)
{			
	if (i_knight == CNT_TYPE_KNIGHT_BLACK)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Warrior/black_knight/attack_1.png");
		m_typeObject = CNT_OBJECT_KNIGHT_BLACK;
	}
	else if (i_knight == CNT_TYPE_KNIGHT_BRONZE)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Warrior/bronze_knight/attack_1.png");
		m_typeObject = CNT_OBJECT_KNIGHT_BRONZE;
	}
	else if (i_knight == CNT_TYPE_KNIGHT_SILVER)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Warrior/silver_knight/attack_1.png");
		m_typeObject = CNT_OBJECT_KNIGHT_SILVER;
	}

	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 10,
		GameScene::m_visibleSize.height / this->getContentSize().height / 10);

	m_spear			= true;
	m_locationTouch = Point::ZERO;
}

Knight::Knight(Knight& Knight)
{
	
}

/*virtual*/ void Knight::Update(ManagerComponent& i_manager)
{
	switch (m_state)
	{
		case StateCombatant::FIND_GOLD:
		{
		
			break;
		}
		case StateCombatant::FIND_OIL:
		{
		
			break;
		}
		case StateCombatant::FIND_TREE:
		{
		
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
		case StateCombatant::NOTHING:
		{
			m_locationTouch	= i_manager.m_inputComponent->GetLocationTouch();
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
	InputComponent		- приймає діна з клавіатури
	ManagerComponent	- контейнер для цих компонентів
*/