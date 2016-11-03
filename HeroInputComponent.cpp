#include "HeroInputComponent.h"
#include "ManagerComponent.h"
#include "MapLayer.h"

HeroInputComponent::HeroInputComponent()
{
	m_locationTouch			= Point::ZERO;
	m_previousLocationTouch = Point::ZERO;
}

HeroInputComponent::HeroInputComponent(HeroInputComponent& i_inputComponent)
{
	
}

/*virtual*/ void HeroInputComponent::Update(ManagerComponent& i_manager)
{
	switch (m_stateInput)
	{
		case StateInput::VERIFY_INPUT_MOVED:
		{
			MapLayer::StateMap _state;
			if ((int)m_startPositionMoved.x > ((int)m_endPositionMoved.x + 2))
			{
				_state = MapLayer::StateMap::MOVE_LEFT;
				i_manager.m_mapLayer->SetState(_state);
			}
			else if (((int)m_startPositionMoved.x + 2) < (int)m_endPositionMoved.x)
			{
				_state = MapLayer::StateMap::MOVE_RIGHT;
				i_manager.m_mapLayer->SetState(_state);
			}
			else if ((int)m_startPositionMoved.y > ((int)m_endPositionMoved.y + 2))
			{
				_state = MapLayer::StateMap::MOVE_DOWN;
				i_manager.m_mapLayer->SetState(_state);
			}
			else if (((int)m_startPositionMoved.y + 2) < (int)m_endPositionMoved.y)
			{
				_state = MapLayer::StateMap::MOVE_UP;
				i_manager.m_mapLayer->SetState(_state);
			}
			m_stateInput = StateInput::NOTHING;

			break;
		}
		case StateInput::STOP:
		{
			MapLayer::StateMap _state = MapLayer::StateMap::STOP;
			i_manager.m_mapLayer->SetState(_state);
		}
		case StateInput::NOTHING:
		{
			

			break;
		}
	default:
		break;
	}
}

/*virtual*/ bool HeroInputComponent::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	m_previousLocationTouch = m_locationTouch;
	m_locationTouch			= touch->getLocation();

	return true;
}

/*virtual*/ void HeroInputComponent::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* i_event)
{
	m_startPositionMoved	= touch->getStartLocation();
	m_endPositionMoved		= touch->getLocation();

	m_stateInput = StateInput::VERIFY_INPUT_MOVED;
}

/*virtual*/ void HeroInputComponent::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* i_event)
{
	m_stateInput = StateInput::STOP;
}

void HeroInputComponent::SetZeroLocation()
{
	m_previousLocationTouch = Point::ZERO;
	m_locationTouch			= Point::ZERO;
}

Vec2 HeroInputComponent::GetLocationTouch() const
{
	return m_locationTouch;
}

Vec2 HeroInputComponent::GetPreviousLocationTouch() const
{
	return m_previousLocationTouch;
}

HeroInputComponent::~HeroInputComponent()
{
	CCLOG("destructor playerinput");
}

/*  GraphicComponent	- тільки малює спрайти 
	PhysicsComponent	- виявлє зіткнення героя
	InputComponent		- приймає дані з клавіатури
	ManagerComponent	- контейнер для цих компонентів
*/
/* Поле ділится на 2 рівних частини. Перша - поле гравця. Друга - ворогів, яка ще поділена на рівні частини, так, що ці утворюють стовпці і рядки, отже виходить квадратне поле. 
   Через Spawn на полі з₴'являються вороги, які протягом певного інтервалу просто лежать на полі, а після нього стріляють в гравця, якому потрібно не прогавати цей момент оскільки 
   на полі їх буде кілька.
 */