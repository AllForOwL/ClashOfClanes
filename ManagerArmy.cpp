#include "ManagerArmy.h"
#include "GameScene.h"
#include "ManagerComponent.h"
#include "Knight.h"
#include "MapLayer.h"
#include "EnemyWarrior.h"
#include "constants.h"

ManagerArmy::ManagerArmy()
{
	
}

ManagerArmy::ManagerArmy(ManagerArmy& i_managerArmy)
{

}

void ManagerArmy::Update(GameScene& i_gameScene, ManagerComponent& i_manager)
{
	switch (m_stateManagerArmy)
	{
		case ManagerArmy::ADD_KNIGHT_BLACK:
		{
			Knight* _newKnightBlack = new Knight(CNT_TYPE_KNIGHT_BLACK, *i_manager.m_mapLayer);
			_newKnightBlack->setPosition(m_positionWarrior);
			m_vecKnight.push_back(_newKnightBlack);
			
			Point _position	= _newKnightBlack->getPosition();
			Size _size		= _newKnightBlack->getBoundingBox().size;
			i_manager.m_mapLayer->FillRegionFromObject(_position, _size);

			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::ADD_KNIGHT_BRONZE:
		{
	   		Knight* _newKnightBronze = new Knight(CNT_TYPE_KNIGHT_BRONZE, *i_manager.m_mapLayer);
			_newKnightBronze->setPosition(m_positionWarrior);
			m_vecKnight.push_back(_newKnightBronze);
			
			Point _position	= _newKnightBronze->getPosition();
			Size _size		= _newKnightBronze->getBoundingBox().size;
			i_manager.m_mapLayer->FillRegionFromObject(_position, _size);

			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::ADD_KNIGHT_SILVER:
		{
			Knight* _newKnightSilver = new Knight(CNT_TYPE_KNIGHT_SILVER, *i_manager.m_mapLayer);
			_newKnightSilver->setPosition(m_positionWarrior);
			m_vecKnight.push_back(_newKnightSilver);
			
			Point _position	= _newKnightSilver->getPosition();
			Size _size		= _newKnightSilver->getBoundingBox().size;
			i_manager.m_mapLayer->FillRegionFromObject(_position, _size);

			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::ADD_ENEMY_BOWMAN:
		{
			EnemyWarrior* _newEnemyBowman = new EnemyWarrior(CNT_TYPE_BOWMAN, *i_manager.m_mapLayer);
			_newEnemyBowman->setPosition(m_positionWarrior);
			m_vecEnemy.push_back(_newEnemyBowman);
			
			Point _position = _newEnemyBowman->getPosition();
			Size _size		= _newEnemyBowman->getBoundingBox().size;
			// here need add fill region enemy
			//i_manager.m_mapLayer->FillRegionFromObject(_position, _size);

			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::ADD_ENEMY_KNIGHT:
		{
			EnemyWarrior* _newEnemyBowman = new EnemyWarrior(CNT_TYPE_ENEMY_KNIGHT, *i_manager.m_mapLayer);
			_newEnemyBowman->setPosition(m_positionWarrior);
			m_vecEnemy.push_back(_newEnemyBowman);
			
			Point _position = _newEnemyBowman->getPosition();
			Size _size		= _newEnemyBowman->getBoundingBox().size;
			// here need add fill region enemy
			//i_manager.m_mapLayer->FillRegionFromObject(_position, _size);

			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::ADD_ENEMY_WIZARD:
		{
			EnemyWarrior* _newEnemyBowman = new EnemyWarrior(CNT_TYPE_WIZARD, *i_manager.m_mapLayer);
			_newEnemyBowman->setPosition(m_positionWarrior);
			m_vecEnemy.push_back(_newEnemyBowman);
			
			Point _position = _newEnemyBowman->getPosition();
			Size _size		= _newEnemyBowman->getBoundingBox().size;
			// here need add fill region enemy
			//i_manager.m_mapLayer->FillRegionFromObject(_position, _size);

			m_stateManagerArmy = StateManagerArmy::NOTHING;

			break;
		}
		case ManagerArmy::ADD_ENEMY_PALADIN:
		{
			EnemyWarrior* _newEnemyBowman = new EnemyWarrior(CNT_TYPE_PALADIN, *i_manager.m_mapLayer);
			_newEnemyBowman->setPosition(m_positionWarrior);
			m_vecEnemy.push_back(_newEnemyBowman);
			
			Point _position = _newEnemyBowman->getPosition();
			Size _size		= _newEnemyBowman->getBoundingBox().size;
			// here need add fill region enemy
			//i_manager.m_mapLayer->FillRegionFromObject(_position, _size);

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