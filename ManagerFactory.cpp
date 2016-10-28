#include "ManagerFactory.h"
#include "GameScene.h"
#include "ManagerComponent.h"
#include "WarriorFactory.h"

ManagerFactory::ManagerFactory()
{
	
}

ManagerFactory::ManagerFactory(ManagerFactory& i_ManagerFactory)
{

}

void ManagerFactory::Update(GameScene& i_gameScene, ManagerComponent& i_manager)
{
	switch (m_stateManagerFactory)
	{
		case ManagerFactory::ADD_FACTORY_WARRIOR:
		{
			

			break;
		}
		case ManagerFactory::ADD_FACTORY_MACHINE:
		{
			
			
			break;
		}
		case ManagerFactory::NOTHING:
		{
			

			break;
		}
	default:
		break;
	}
}

void ManagerFactory::SetState(StateManagerFactory& i_state)
{
	m_stateManagerFactory = i_state;
}

ManagerFactory::~ManagerFactory()
{

}