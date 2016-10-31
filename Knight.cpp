#include "Knight.h"
#include "GameScene.h"
#include "constants.h"
#include "MapLayer.h"

Knight::Knight()
{
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Hero/Walk_1.png");
	this->setPosition(GameScene::m_visibleSize.width / 2 - 50, GameScene::m_visibleSize.height / 2);
	this->setZOrder(1);
}

Knight::Knight(std::string i_knight, GameScene& i_parentGameScene)
{			
	i_parentGameScene.addChild(this);

	if (i_knight == CNT_TYPE_KNIGHT_BLACK)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Warrior/black_knight/attack_1.png");
	}
	else if (i_knight == CNT_TYPE_KNIGHT_BRONZE)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Warrior/bronze_knight/attack_1.png");
	}
	else if (i_knight == CNT_TYPE_KNIGHT_SILVER)
	{
		this->initWithFile(CNT_PATH_TO_RESOURCES + "Warrior/silver_knight/attack_1.png");
	}
	
	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 8,
		GameScene::m_visibleSize.height / this->getContentSize().height / 8);
	this->setPosition(GameScene::m_visibleSize.width / 2 - 50, GameScene::m_visibleSize.height / 2 + 50);
	this->setZOrder(1);
}

Knight::Knight(Knight& Knight)
{
	
}

/*virtual*/ void Knight::Update(ManagerComponent& i_manager)
{

}

Knight::~Knight()
{
	CCLOG("destructor Knight");
}

/*  GraphicComponent	- тільки малює спрайти 
	PhysicsComponent	- виявлє зіткнення героя
	InputComponent		- приймає діна з клавіатури
	ManagerComponent	- контейнер для цих компонентів
*/