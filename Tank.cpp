#include "Tank.h"
#include "GameScene.h"
#include "constants.h"

Tank::Tank()
{
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Hero/Tank_1.png");
	this->setPosition(GameScene::m_visibleSize.width / 2 - 50, GameScene::m_visibleSize.height / 2);
	this->setZOrder(1);
}

Tank::Tank(GameScene& i_parentGameScene)
{
	i_parentGameScene.addChild(this);
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Machine/Tank_1.png");
	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 8,
		GameScene::m_visibleSize.height / this->getContentSize().height / 8);
	this->setPosition(GameScene::m_visibleSize.width / 2, GameScene::m_visibleSize.height / 2 + 50);
	this->setZOrder(1);
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