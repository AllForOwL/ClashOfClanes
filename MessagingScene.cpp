#include "MessagingScene.h"
#include "GameScene.h"
#include  "constants.h"

USING_NS_CC;

Scene *MessagingScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MessagingScene::create();

	scene->addChild(layer);

	return scene;
}

bool MessagingScene::init()
{
	if (!Layer::init())	// if layer not create exit from function
	{
		return false;
	}

	OpenMessagings();

	m_close = Sprite::create(CNT_PATH_TO_RESOURCES + "Item/Message/Close.png",
		Rect(GameScene::m_visibleSize.width - 40, 20, 40, 20));
	m_close->setScale(GameScene::m_visibleSize.width / 10, GameScene::m_visibleSize.height / 10);
	this->addChild(m_close);

	auto _touchListener = EventListenerTouchOneByOne::create();
	_touchListener->onTouchBegan = CC_CALLBACK_2(MessagingScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

	return true;
}

void MessagingScene::OpenMessagings()
{

}

void MessagingScene::CloseCurrentScene()
{
	Director::getInstance()->popScene();
}

/*virtual*/ bool MessagingScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* i_event)
{
	if (m_close->getBoundingBox().containsPoint(touch->getLocationInView()))
	{
		CloseCurrentScene();
	}

	return true;
}
