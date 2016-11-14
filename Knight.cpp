#include "Knight.h"
#include "GameScene.h"
#include "MapLayer.h"
#include "ManagerComponent.h"

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

	m_spear	= true;
}

Knight::Knight(Knight& Knight)
{
	
}

/*virtual*/ void Knight::Update(ManagerComponent& i_manager)
{
	switch (m_state)
	{
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

			break;
		}
	default:
		break;
	}
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