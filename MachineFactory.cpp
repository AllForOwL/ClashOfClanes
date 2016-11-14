#include "MachineFactory.h"
#include "ManagerComponent.h"
#include "HeroGraphicComponent.h"
#include "GameScene.h"
#include "GraphicComponent.h"
#include "ManagerMachine.h"
#include "HeroInputComponent.h"
#include "MapLayer.h"

const int CNT_TIME_FOR_COMPLETE_TANK	= 40;
const int CNT_TIME_FOR_COMPLETE_CAR		= 30;

const int CNT_INDEX_TANK = 0;

MachineFactory::MachineFactory()
{

}

MachineFactory::MachineFactory(Point i_positionVisible, MapLayer& i_mapLayer) : Factory(i_positionVisible, i_mapLayer, "Castle/FactoryMachine.png")
{
	m_stateMachine	= StateFactoryMachine::NOTHING;
}

MachineFactory::MachineFactory(MachineFactory& i_MachineFactory)
{

}

void MachineFactory::SetState(MachineFactory::StateFactoryMachine& i_state)
{
	m_stateMachine = i_state;
}

void MachineFactory::LoadNameForSprites()
{
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Machine/Tank_1.png");
}

/*virtual*/ void MachineFactory::Update(ManagerComponent& i_manager)
{
	switch (m_stateMachine)
	{
		case StateFactoryMachine::START_TANK:
		{
			if (i_manager.m_hero->CheckProductionTank())
			{
				m_timeForComplete	= CNT_TIME_FOR_COMPLETE_TANK;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateMachine				= StateFactoryMachine::WORKING;
				m_stateManagerMachine		= ManagerMachine::StateManagerMachine::ADD_TANK;
			}
			break;
		}
		case StateFactoryMachine::WORKING:
		{
			if (isComplete())
			{
				m_stateMachine = StateFactoryMachine::NOTHING;
				i_manager.m_managerMachine->SetState(m_stateManagerMachine);
				i_manager.m_managerMachine->SetPositionForMachine(m_vecPosition[m_numberComplete]);
				++m_numberComplete;
			}
			break;
		}
		case StateFactoryMachine::NOTHING:
		{
			m_locationTouch		= i_manager.m_inputComponent->GetLocationTouch();
			ConvertToOrigin(m_locationTouch);
			if (m_rectOriginWithVisible.containsPoint(m_locationTouch))
			{
				if (m_vecNameForSprites.empty())
				{
					LoadNameForSprites();
					LoadSprites();
				}

				ShowMenu();
				LoadPosition();
				m_stateMachine	= StateFactoryMachine::LISTEN;
				i_manager.m_inputComponent->SetZeroLocation();
			}
			break;
		}
		case StateFactoryMachine::LISTEN:
		{
			m_locationTouch = i_manager.m_inputComponent->GetLocationTouch();
			ConvertToOrigin(m_locationTouch);
			if (DetermineCommand())
			{
				i_manager.m_inputComponent->SetZeroLocation();
			}

			break;
		}
	default:
		break;
	}
}

bool MachineFactory::DetermineCommand()
{
	if (m_rectForSprites[CNT_INDEX_TANK].containsPoint(m_locationTouch))
	{
		m_stateMachine = StateFactoryMachine::START_TANK;
		return true;
	}
	return false;
}

MachineFactory::StateFactoryMachine& MachineFactory::GetState()
{
	return m_stateMachine;
}

MachineFactory::~MachineFactory()
{

}


/*
 Hero has goes on map
*/