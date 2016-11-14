#include "HeroMachine.h"
#include "GameScene.h"
#include "MapLayer.h"
#include "ManagerComponent.h"

const int CNT_SPEED_OCTOPEDE	= 2;
const int CNT_SPEED_BRAIN		= 3;

HeroMachine::HeroMachine()
{

}

HeroMachine::HeroMachine(std::string i_typeHeroMachine, MapLayer& i_parentMapLayer) : Machine(i_parentMapLayer)
{			
	if (i_typeHeroMachine == CNT_TYPE_TANK)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Machine/Tank_1.png");
		m_typeObject = CNT_OBJECT_TANK;
	}

	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 13,
		GameScene::m_visibleSize.height / this->getContentSize().height / 13);
}

HeroMachine::HeroMachine(HeroMachine& i_heroMachine)
{
	
}

/*virtual*/ void HeroMachine::Update(ManagerComponent& i_manager)
{
	switch (m_state)
	{
		case StateCombatant::MOVE_FORWARD:
		{
			MoveForward();
			m_state	= StateCombatant::FIND_ACT;

			break;
		}
		case StateCombatant::MOVE_BACK:
		{
			MoveBack();
			m_state	= StateCombatant::FIND_ACT;

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
			m_state	= StateCombatant::FIND_ACT;

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


HeroMachine::~HeroMachine()
{
	CCLOG("destructor HeroMachine");
}

/*  GraphicComponent	- тільки малює спрайти 
	PhysicsComponent	- виявлє зіткнення героя
	InputComponent		- приймає діна з клавіатури
	ManagerComponent	- контейнер для цих компонентів
*/