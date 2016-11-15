#include "ManagerArmy.h"
#include "GameScene.h"
#include "ManagerComponent.h"
#include "MapLayer.h"
#include "EnemyWarrior.h"
#include "HeroInputComponent.h"
#include "Knight.h"

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

	i_manager.m_mapLayer->FillRegionFromObject(i_typeWarrior, m_positionNewWarrior, m_sizeNewWarrior);
	i_manager.m_inputComponent->SetZeroLocation();
}

void ManagerArmy::Update(GameScene& i_gameScene, ManagerComponent& i_manager)
{
	switch (m_stateManagerArmy)
	{
		case ManagerArmy::ADD_KNIGHT_BLACK:
		{
			Knight* _newKnightBlack = new Knight(m_positionWarrior, *i_manager.m_mapLayer, std::string("Warrior/black_knight/attack_1.png"));
			_newKnightBlack->SetTypeObject(CNT_OBJECT_KNIGHT_BLACK);
			m_vecKnight.push_back(_newKnightBlack);
			LaunchFillRegion(*m_vecKnight[m_vecKnight.size() - 1], i_manager, CNT_OBJECT_KNIGHT_BLACK);

			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::ADD_KNIGHT_BRONZE:
		{
	   		Knight* _newKnightBronze = new Knight(m_positionWarrior, *i_manager.m_mapLayer, std::string("Warrior/bronze_knight/attack_1.png"));
			_newKnightBronze->SetTypeObject(CNT_OBJECT_KNIGHT_BRONZE);
			m_vecKnight.push_back(_newKnightBronze);
			LaunchFillRegion(*m_vecKnight[m_vecKnight.size() - 1], i_manager, CNT_OBJECT_KNIGHT_BRONZE);

			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::ADD_KNIGHT_SILVER:
		{
			Knight* _newKnightSilver = new Knight(m_positionWarrior,  *i_manager.m_mapLayer, std::string("Warrior/silver_knight/attack_1.png"));
			_newKnightSilver->SetTypeObject(CNT_OBJECT_KNIGHT_SILVER);
			m_vecKnight.push_back(_newKnightSilver);
			LaunchFillRegion(*m_vecKnight[m_vecKnight.size() - 1], i_manager, CNT_OBJECT_KNIGHT_SILVER);

			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::ADD_ENEMY_BOWMAN:
		{
			EnemyWarrior* _newEnemyBowman = new EnemyWarrior(CNT_TYPE_BOWMAN, *i_manager.m_mapLayer);
			_newEnemyBowman->setPosition(m_positionWarrior);
			m_vecEnemy.push_back(_newEnemyBowman);
			LaunchFillRegion(*m_vecEnemy[m_vecEnemy.size() - 1], i_manager, CNT_OBJECT_ENEMY_BOWMAN);

			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::ADD_ENEMY_KNIGHT:
		{
			EnemyWarrior* _newEnemyBowman = new EnemyWarrior(CNT_TYPE_ENEMY_KNIGHT, *i_manager.m_mapLayer);
			_newEnemyBowman->setPosition(m_positionWarrior);
			m_vecEnemy.push_back(_newEnemyBowman);
			LaunchFillRegion(*m_vecEnemy[m_vecEnemy.size() - 1], i_manager, CNT_OBJECT_ENEMY_KNIGHT);

			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::ADD_ENEMY_WIZARD:
		{
			EnemyWarrior* _newEnemyBowman = new EnemyWarrior(CNT_TYPE_WIZARD, *i_manager.m_mapLayer);
			_newEnemyBowman->setPosition(m_positionWarrior);
			m_vecEnemy.push_back(_newEnemyBowman);
			LaunchFillRegion(*m_vecEnemy[m_vecEnemy.size() - 1], i_manager, CNT_OBJECT_ENEMY_WIZARD);

			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::ADD_ENEMY_PALADIN:
		{
			EnemyWarrior* _newEnemyBowman = new EnemyWarrior(CNT_TYPE_PALADIN, *i_manager.m_mapLayer);
			_newEnemyBowman->setPosition(m_positionWarrior);
			m_vecEnemy.push_back(_newEnemyBowman);
			LaunchFillRegion(*m_vecEnemy[m_vecEnemy.size() - 1], i_manager, CNT_OBJECT_ENEMY_PALADIN);

			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::NOTHING:
		{				
			if (m_vecKnight.size())
			{
				for (int i = 0; i < m_vecKnight.size(); i++)
				{
					m_vecKnight[i]->Update(i_manager);
				}
			}

			if (m_vecEnemy.size())
			{
				for (int i = 0; i < m_vecEnemy.size(); i++)
				{
					m_vecEnemy[i]->Update(i_manager);
				}
			}

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