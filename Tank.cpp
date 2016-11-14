#include "Tank.h"
#include "MapLayer.h"
#include "GameScene.h"

Tank::Tank()
{
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Machine/Tank_1.png");
}

Tank::Tank(MapLayer& i_parentMapLayer)
{
	i_parentMapLayer.addChild(this);
	
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Machine/Tank_1.png");
	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 8,
		GameScene::m_visibleSize.height / this->getContentSize().height / 8);
}

Tank::Tank(Tank& i_tank)
{
	
}

/*virtual*/ void Tank::Update(ManagerComponent& i_manager)
{

}

Tank::~Tank()
{
	CCLOG("destructor Tank");
}

/*  GraphicComponent	- тільки малює спрайти 
	PhysicsComponent	- виявлє зіткнення героя
	InputComponent		- приймає діна з клавіатури
	ManagerComponent	- контейнер для цих компонентів
*/