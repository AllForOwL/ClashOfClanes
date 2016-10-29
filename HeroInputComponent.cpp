#include "HeroInputComponent.h"
#include "ManagerComponent.h"

HeroInputComponent::HeroInputComponent()
{
	m_locationTouch = Point::ZERO;
}

HeroInputComponent::HeroInputComponent(HeroInputComponent& i_inputComponent)
{

}

/*virtual*/ void HeroInputComponent::Update(ManagerComponent& i_manager)
{
		
}

/*virtual*/ bool HeroInputComponent::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	m_locationTouch = touch->getLocation();

	return true;
}

void HeroInputComponent::SetZeroLocation()
{
	m_locationTouch = Point::ZERO;
}

/*virtual*/ void HeroInputComponent::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

/*virtual*/ void HeroInputComponent::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	
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