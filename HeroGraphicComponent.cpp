#include "HeroGraphicComponent.h"

HeroGraphicComponent::HeroGraphicComponent()
{
	
}

HeroGraphicComponent::HeroGraphicComponent(HeroGraphicComponent& heroGraphicComponent)
{
	
}

/*virtual*/ void HeroGraphicComponent::Update(GameScene& i_gameScene)
{

}

HeroGraphicComponent::~HeroGraphicComponent()
{
	CCLOG("destructor herographic");
}

/*  GraphicComponent	- тільки малює спрайти 
	PhysicsComponent	- виявлє зіткнення героя
	InputComponent		- приймає діна з клавіатури
	ManagerComponent	- контейнер для цих компонентів
*/