#include "GameScene.h"
#include "MapLayer.h"
#include "FamilyHouse.h"
#include "HeroGraphicComponent.h"
#include "ManagerComponent.h"
#include "HUDLayer.h"
#include "HeroInputComponent.h"

const float CNT_TIME_UPDATE_SCENE = 0.01;

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

	auto _touchListener = EventListenerTouchOneByOne::create();
	_touchListener->onTouchBegan = CC_CALLBACK_2(HeroInputComponent::onTouchBegan, m_manager->m_inputComponent);
	_touchListener->onTouchMoved = CC_CALLBACK_2(HeroInputComponent::onTouchMoved, m_manager->m_inputComponent);
	_touchListener->onTouchEnded = CC_CALLBACK_2(HeroInputComponent::onTouchEnded, m_manager->m_inputComponent);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

	this->schedule(schedule_selector(GameScene::update), CNT_TIME_UPDATE_SCENE);

	return true;
}

void GameScene::update(float dt)
{
	m_HUDLayer->Update	(*m_manager);
	m_manager->Update	(*this);
}

GameScene::~GameScene()
{
	delete m_manager;
	CCLOG("destructor gamescene");
}