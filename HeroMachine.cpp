#include "HeroMachine.h"
#include "GameScene.h"
#include "MapLayer.h"
#include "ManagerComponent.h"

const int CNT_SPEED_OCTOPEDE	= 2;
const int CNT_SPEED_BRAIN		= 3;

HeroMachine::HeroMachine()
{

}

HeroMachine::HeroMachine(std::string i_HeroMachine, MapLayer& i_parentMapLayer) : Machine(i_parentMapLayer)
{			

}

HeroMachine::HeroMachine(HeroMachine& i_heroMachine)
{
	
}

/*virtual*/ void HeroMachine::Update(ManagerComponent& i_manager)
{
	
}


HeroMachine::~HeroMachine()
{
	CCLOG("destructor HeroMachine");
}

/*  GraphicComponent	- тільки малює спрайти 
	PhysicsComponent	- виявлє зіткнення героя
	InputComponent		- приймає діна з клавіатури
	ManagerComponent	- контейнер для цих компонентів
*/