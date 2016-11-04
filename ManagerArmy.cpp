#include "ManagerArmy.h"
#include "GameScene.h"
#include "ManagerComponent.h"
#include "Knight.h"
#include "MapLayer.h"
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
			Knight* _newKnightBlack = new Knight(CNT_TYPE_KNIGHT_BLACK, i_gameScene);
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
	   		Knight* _newKnightBronze = new Knight(CNT_TYPE_KNIGHT_BRONZE, i_gameScene);
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
			Knight* _newKnightSilver = new Knight(CNT_TYPE_KNIGHT_SILVER, i_gameScene);
			_newKnightSilver->setPosition(m_positionWarrior);
			m_vecKnight.push_back(_newKnightSilver);
			
			Point _position	= _newKnightSilver->getPosition();
			Size _size		= _newKnightSilver->getBoundingBox().size;
			i_manager.m_mapLayer->FillRegionFromObject(_position, _size);

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