#include "MessagingSystem.h"
#include "ManagerComponent.h"
#include "ManagerFactory.h"
#include "MapLayer.h"
#include "GameScene.h"
#include "constants.h"

USING_NS_CC;

std::vector<std::string>MessagingSystem::m_vecMessages;
int MessagingSystem::g_typeFactory;


const Point CNT_POSITION_GOLD	= Point(200, 200);
const Point CNT_POSITION_OIL	= Point(600, 600);
const Point CNT_POSITION_TREE	= Point(700, 700);


MessagingSystem::MessagingSystem()
{
	m_stateMessage = StateMessage::NOTHING;
	g_typeFactory = 0;
}

MessagingSystem::MessagingSystem(MessagingSystem& i_messageSystem)
{

}

int MessagingSystem::GetQuentityMessage() const
{
	return m_vecMessages.size();
}

void MessagingSystem::Update(ManagerComponent& i_manager)
{
	switch (m_stateMessage)
	{
		case StateMessage::BUILD_FACTORY_GOLD:
		{
			ManagerFactory::StateManagerFactory _newStateFactory = ManagerFactory::StateManagerFactory::ADD_FACTORY_GOLD;
			i_manager.m_managerFactory->SetState(_newStateFactory);
			i_manager.m_managerFactory->SetPositionBuildFactory(CNT_POSITION_GOLD);
			i_manager.m_mapLayer->setPosition(CNT_POSITION_GOLD * (-1));

			m_stateMessage = StateMessage::NOTHING;

			break;												
		}
		case StateMessage::BUILD_FACTORY_OIL:
		{
			ManagerFactory::StateManagerFactory _newStateFactory = ManagerFactory::StateManagerFactory::ADD_FACTORY_OIL;														
			i_manager.m_managerFactory->SetState(_newStateFactory);
			i_manager.m_managerFactory->SetPositionBuildFactory(CNT_POSITION_OIL);
			i_manager.m_mapLayer->setPosition(CNT_POSITION_OIL * (-1));

			m_stateMessage = StateMessage::NOTHING;

			break;
		}
		case StateMessage::NOTHING:
		{
			VerifyGoBuildFactory();
		
			break;
		}
	default:
		break;
	}
}

void MessagingSystem::VerifyGoBuildFactory()
{
	if (g_typeFactory == TYPE_GOLD)
	{
		m_stateMessage = StateMessage::BUILD_FACTORY_GOLD;
		g_typeFactory = 0;
	}
	else if (g_typeFactory == StateMessage::BUILD_FACTORY_OIL)
	{
		m_stateMessage = StateMessage::BUILD_FACTORY_OIL;
		g_typeFactory = 0;
	}
}

void MessagingSystem::SetState(StateMessage i_state)      
{
	m_stateMessage = i_state;
}

MessagingSystem::StateMessage MessagingSystem::GetState() const
{
	return m_stateMessage;
}

void MessagingSystem::AddMesssage(std::string i_message)
{
	m_vecMessages.push_back(i_message);
}