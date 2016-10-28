#include "ManagerArmy.h"
#include "GameScene.h"
#include "ManagerComponent.h"
#include "Archer.h"

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
		case ManagerArmy::ADD_ARCHER:
		{
			Archer* _newArcher = new Archer(i_gameScene);
			m_vecArcher.push_back(_newArcher);

			break;
		}
		case ManagerArmy::ADD_TANK:
		{

			break;
		}
		case ManagerArmy::NOTHING:
		{				
			for (int i = 0; i < m_vecArcher.size(); i++)
			{
				m_vecArcher[i]->Update(i_manager);
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

ManagerArmy::~ManagerArmy()
{

}