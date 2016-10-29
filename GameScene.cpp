#include "GameScene.h"
#include "MapLayer.h"
#include "FamilyHouse.h"
#include "HeroGraphicComponent.h"
#include "ManagerComponent.h"
#include "HUDLayer.h"

Size GameScene::m_visibleSize = Size(0, 0);

Scene *GameScene::createScene() 
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_visibleSize   = Director::getInstance()->getVisibleSize();
	m_origin		= Director::getInstance()->getVisibleOrigin();

	m_manager = new ManagerComponent(*this);

	m_HUDLayer = HUDLayer::create();
	this->addChild(m_HUDLayer, 100);

	return true;
}

GameScene::~GameScene()
{
	CCLOG("destructor gamescene");
}