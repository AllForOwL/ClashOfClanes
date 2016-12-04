#include "ManagerArmy.h"
#include "GameScene.h"
#include "ManagerComponent.h"
#include "MapLayer.h"
#include "EnemyWarrior.h"
#include "HeroInputComponent.h"
#include "Knight.h"
#include "ManagerObjectAndFile.h"

ManagerArmy::ManagerArmy()
{
	
}

ManagerArmy::ManagerArmy(ManagerArmy& i_managerArmy)
{

}

void ManagerArmy::LaunchFillRegion(const Warrior& i_warrior, ManagerComponent& i_manager, int i_typeWarrior)
{
	m_positionNewWarrior	= i_warrior.getPosition();
	m_sizeNewWarrior		= i_warrior.getBoundingBox().size;

	i_manager.m_mapLayer->FillRegionFromObject(i_manager, i_typeWarrior, m_positionNewWarrior, m_sizeNewWarrior);
	i_manager.m_inputComponent->SetZeroLocation();
}

void ManagerArmy::CreateWarrior(ManagerComponent& i_manager, int i_typeObject, std::string i_nameFile)
{
	Knight* _newKnightBlack = new Knight(m_positionWarrior, *i_manager.m_mapLayer, i_nameFile);
	_newKnightBlack->setPosition(m_positionWarrior);
	_newKnightBlack->SetTypeObject(CNT_OBJECT_KNIGHT_BLACK);
	m_vecKnight.push_back(_newKnightBlack);
	LaunchFillRegion(*m_vecKnight[m_vecKnight.size() - 1], i_manager, CNT_OBJECT_KNIGHT_BLACK);
	i_manager.m_managerObjectAndFile->WriteObjectInFile(CNT_OBJECT_KNIGHT_BLACK, m_positionWarrior, (i_manager.m_mapLayer->getPosition() * -1));
}

void ManagerArmy::CreateWarriorEnemy(ManagerComponent& i_manager, std::string i_typeEnemy)
{
	EnemyWarrior* _newEnemyBowman = new EnemyWarrior(i_typeEnemy, *i_manager.m_mapLayer);
	_newEnemyBowman->setPosition(m_positionWarrior);
	m_vecEnemy.push_back(_newEnemyBowman);
	LaunchFillRegion(*m_vecEnemy[m_vecEnemy.size() - 1], i_manager, CNT_OBJECT_ENEMY_BOWMAN);
	i_manager.m_managerObjectAndFile->WriteObjectInFile(CNT_OBJECT_ENEMY_BOWMAN, m_positionWarrior, (i_manager.m_mapLayer->getPosition() * -1));
}

void ManagerArmy::UpdateAllWarrior(ManagerComponent& i_manager)
{
	for (int i = 0; i < m_vecEnemy.size(); i++)
	{
		m_vecEnemy[i]->Update(i_manager);
	}
	for (int i = 0; i < m_vecKnight.size(); i++)
	{
		m_vecKnight[i]->Update(i_manager);
	}
}

void ManagerArmy::Update(GameScene& i_gameScene, ManagerComponent& i_manager)
{
	switch (m_stateManagerArmy)
	{
		case ManagerArmy::ADD_KNIGHT_BLACK:
		{
			CreateWarrior(i_manager, CNT_OBJECT_KNIGHT_BLACK, CNT_PATH_TO_RESOURCES + "Warrior/black_knight/attack_1.png");
	
			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::ADD_KNIGHT_BRONZE:
		{
	   		CreateWarrior(i_manager, CNT_OBJECT_KNIGHT_BRONZE, CNT_PATH_TO_RESOURCES + "Warrior/bronze_knigt/attack_1.png");

			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::ADD_KNIGHT_SILVER:
		{
			CreateWarrior(i_manager, CNT_OBJECT_KNIGHT_SILVER, CNT_PATH_TO_RESOURCES + "Warrior/silver_knight/attack_1.png");

			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::ADD_ENEMY_BOWMAN:
		{
			CreateWarriorEnemy(i_manager, CNT_TYPE_BOWMAN); 

			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::ADD_ENEMY_KNIGHT:
		{
			CreateWarriorEnemy(i_manager, CNT_TYPE_ENEMY_KNIGHT);

			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::ADD_ENEMY_WIZARD:
		{
			CreateWarriorEnemy(i_manager, CNT_TYPE_WIZARD);

			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::ADD_ENEMY_PALADIN:
		{
			CreateWarriorEnemy(i_manager, CNT_TYPE_PALADIN);

			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::NOTHING:
		{				
			UpdateAllWarrior(i_manager);

			break;
		}
	default:
		break;
	}
}

void ManagerArmy::SetState(StateManagerArmy& i_state)
{
	m_stateManagerArmy = i_state;
}

void ManagerArmy::SetPositionForWarrior(Point i_positionWarrior)
{
	m_positionWarrior = i_positionWarrior;
}

ManagerArmy::~ManagerArmy()
{

}