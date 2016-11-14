#include "EnemyWarrior.h"
#include "GameScene.h"
#include "MapLayer.h"
#include "ManagerComponent.h"

const int CNT_SPEED_BOWMAN			= 2;
const int CNT_SPEED_ENEMY_KNIGHT	= 3;

EnemyWarrior::EnemyWarrior()
{

}

EnemyWarrior::EnemyWarrior(std::string i_EnemyWarrior, MapLayer& i_parentMapLayer) : Warrior(i_parentMapLayer)
{			
	if (i_EnemyWarrior == CNT_TYPE_BOWMAN)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Enemy/Bowman.png");
		m_speed			= CNT_SPEED_BOWMAN;
		m_typeObject	= CNT_OBJECT_ENEMY_BOWMAN;
	}
	else if (i_EnemyWarrior == CNT_TYPE_ENEMY_KNIGHT)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Enemy/EnemyKnight.png");
		m_speed			= CNT_SPEED_ENEMY_KNIGHT;
		m_typeObject	= CNT_OBJECT_ENEMY_KNIGHT;
	}
	else if (i_EnemyWarrior == CNT_TYPE_WIZARD)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Enemy/Wizard.png");
		m_typeObject	= CNT_OBJECT_ENEMY_WIZARD;
	}
	else if (i_EnemyWarrior == CNT_TYPE_PALADIN)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Enemy/Paladin.png");
		m_typeObject	= CNT_OBJECT_ENEMY_PALADIN;
	}

	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 13,
		GameScene::m_visibleSize.height / this->getContentSize().height / 13);
}

EnemyWarrior::EnemyWarrior(EnemyWarrior& EnemyWarrior)
{
	
}

/*virtual*/ void EnemyWarrior::Update(ManagerComponent& i_manager)
{
	switch (m_state)
	{
		case StateWarrior::MOVE_FORWARD:
		{
			MoveForward();

			break;
		}
		case StateWarrior::MOVE_BACK:
		{
			MoveBack();
		
			break;
		}
		case StateWarrior::MOVE_RIGHT:
		{
			MoveRight();
		
			break;
		}
		case StateWarrior::MOVE_LEFT:
		{
			MoveLeft();

			break;
		}
		case StateWarrior::FIND_ACT:
		{
			SetStatusPositionForCurrentDirection(i_manager);
			UpdateDirection(i_manager);

			break;
		}
		case StateWarrior::NOTHING:
		{

			break;
		}
	default:
		break;
	}
	m_state = StateWarrior::FIND_ACT;
}

EnemyWarrior::~EnemyWarrior()
{
	CCLOG("destructor EnemyWarrior");
}

/*  GraphicComponent	- тільки малює спрайти 
	PhysicsComponent	- виявлє зіткнення героя
	InputComponent		- приймає діна з клавіатури
	ManagerComponent	- контейнер для цих компонентів
*/