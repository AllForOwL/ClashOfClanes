#include "HeroGraphicComponent.h"
#include "GameScene.h"
#include "constants.h"

const int CNT_COIN_FOR_START_ARCHER = 50;
const int CNT_COIN_FOR_START_TANK	= 90;
const int CNT_COIN_FOR_START_CAR	= 70;

HeroGraphicComponent::HeroGraphicComponent()
{
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Hero/Walk_1.png");
	this->setPosition(GameScene::m_visibleSize.width / 2 - 50, GameScene::m_visibleSize.height / 2);
	this->setZOrder(1);
}

HeroGraphicComponent::HeroGraphicComponent(GameScene& i_parentGameScene)
{
	i_parentGameScene.addChild(this);
	this->initWithFile(CNT_PATH_TO_RESOURCES + "Hero/Walk_1.png");
	this->setPosition(GameScene::m_visibleSize.width / 2 - 50, GameScene::m_visibleSize.height / 2);
	this->setZOrder(1);
}

HeroGraphicComponent::HeroGraphicComponent(HeroGraphicComponent& heroGraphicComponent)
{
	
}

/*virtual*/ void HeroGraphicComponent::Update(ManagerComponent& i_manager)
{

}

bool HeroGraphicComponent::CheckProductionArcher()
{
	if (m_coin >= CNT_COIN_FOR_START_ARCHER)
	{
		m_coin -= CNT_COIN_FOR_START_ARCHER;
		return true;
	}
	else
	{
		return false;
	}
}

bool HeroGraphicComponent::CheckProductionTank()
{
	if (m_coin >= CNT_COIN_FOR_START_TANK)
	{
		m_coin -= CNT_COIN_FOR_START_TANK;
		return true;
	}
	else
	{
		return false;
	}
}

bool HeroGraphicComponent::CheckProductionCar()
{
	if (m_coin >= CNT_COIN_FOR_START_CAR)
	{
		m_coin -= CNT_COIN_FOR_START_CAR;
		return true;
	}
	else
	{
		return true;
	}
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