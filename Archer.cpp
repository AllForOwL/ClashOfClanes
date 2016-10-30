#include "Archer.h"
#include "GameScene.h"
#include "constants.h"
#include "MapLayer.h"

Archer::Archer()
{
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Hero/Walk_1.png");
	this->setPosition(GameScene::m_visibleSize.width / 2 - 50, GameScene::m_visibleSize.height / 2);
	this->setZOrder(1);
}

Archer::Archer(GameScene& i_parentGameScene)
{			
	i_parentGameScene.addChild(this);

	this->initWithFile(CNT_PATH_TO_RESOURCES + "Warrior/black_knight/attack_1.png");
	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 8,
		GameScene::m_visibleSize.height / this->getContentSize().height / 8);
	this->setPosition(GameScene::m_visibleSize.width / 2 - 50, GameScene::m_visibleSize.height / 2 + 50);
	this->setZOrder(1);
}

Archer::Archer(Archer& Archer)
{
	
}

/*virtual*/ void Archer::Update(ManagerComponent& i_manager)
{

}

Archer::~Archer()
{
	CCLOG("destructor archer");
}

/*  GraphicComponent	- тільки малює спрайти 
	PhysicsComponent	- виявлє зіткнення героя
	InputComponent		- приймає діна з клавіатури
	ManagerComponent	- контейнер для цих компонентів
*/