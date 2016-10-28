#include "FamilyHouse.h"
#include "GameScene.h"
#include "constants.h"

FamilyHouse::FamilyHouse()
{
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Castle/castle_beige.png");
	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 6,
		GameScene::m_visibleSize.height / this->getContentSize().height / 6);
	this->setPosition(GameScene::m_visibleSize.width / 2, GameScene::m_visibleSize.height / 2);
	this->setZOrder(1);
}

FamilyHouse::FamilyHouse(GameScene& i_parentGameScene)
{
	i_parentGameScene.addChild(this);

	this->initWithFile(CNT_PATH_TO_RESOURCES + "Castle/castle_beige.png");
	this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 6,
		GameScene::m_visibleSize.height / this->getContentSize().height / 6);
	this->setPosition(GameScene::m_visibleSize.width / 2, GameScene::m_visibleSize.height / 2);
	this->setZOrder(1);
}


FamilyHouse::FamilyHouse(const FamilyHouse& i_familyHouse)
{

}

/*virtual*/ void FamilyHouse::Update(GameScene& i_gameScene)
{

}

FamilyHouse::~FamilyHouse()
{

}
