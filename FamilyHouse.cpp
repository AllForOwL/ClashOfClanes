#include "FamilyHouse.h"
#include "GameScene.h"
#include "constants.h"

FamilyHouse::FamilyHouse()
{
	m_visibleSize = Director::getInstance()->getVisibleSize();

	this->initWithFile(CNT_PATH_TO_RESOURCES + "Castle/castle_beige.png");
	this->setScale(m_visibleSize.width / this->getContentSize().width / 6,
		m_visibleSize.height / this->getContentSize().height / 6);
	this->setPosition(m_visibleSize.width / 2, m_visibleSize.height / 2);
	this->setZOrder(1);
}

FamilyHouse::FamilyHouse(GameScene& i_parentGameScene)
{
	this->setParent(&i_parentGameScene);

	m_visibleSize = Director::getInstance()->getVisibleSize();
	
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Castle/castle_beige.png");
	this->setScale(m_visibleSize.width / this->getContentSize().width / 6,
		m_visibleSize.height / this->getContentSize().height / 6);
	this->setPosition(m_visibleSize.width / 2, m_visibleSize.height / 2);
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
