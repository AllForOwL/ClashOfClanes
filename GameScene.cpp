#include "GameScene.h"

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

	 

	return true;
}

GameScene::~GameScene()
{
	CCLOG("destructor gamescene");
}