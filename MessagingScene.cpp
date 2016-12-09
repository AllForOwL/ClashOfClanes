#include "MessagingScene.h"
#include "MessagingSystem.h"
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
	if (!Layer::init())
	{
		return false;
	}

	OpenMessagings();
	AddElement();

	auto _touchListener = EventListenerTouchOneByOne::create();
	_touchListener->onTouchBegan = CC_CALLBACK_2(MessagingScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

	return true;
}

void MessagingScene::AddElement()
{
	m_close = Sprite::create(CNT_PATH_TO_RESOURCES + "Item/Message/Close.png");
	m_close->setScale(GameScene::m_visibleSize.width / m_close->getContentSize().width / 6,
		GameScene::m_visibleSize.height / m_close->getContentSize().height / 6);
	m_close->setPosition(GameScene::m_visibleSize.width - m_close->getBoundingBox().size.width / 2, 
		m_close->getBoundingBox().size.height / 2);
	this->addChild(m_close);

}

void MessagingScene::OpenMessagings()
{
	int _positionY = GameScene::m_visibleSize.height;
	for (int i = 0; i < MessagingSystem::m_vecMessages.size(); i++)
	{
		m_message = Label::create(MessagingSystem::m_vecMessages[i], "Herbana", 12);
		_positionY -= m_message->getContentSize().height / 2;
		m_message->setPosition(GameScene::m_visibleSize.width / 2, _positionY);
		this->addChild(m_message);
	}

	m_buildFactory = Label::create("Build", "Herbana", 20);
	m_buildFactory->setPosition(GameScene::m_visibleSize.width / 2,
		m_buildFactory->getContentSize().height);
	this->addChild(m_buildFactory);
}

void MessagingScene::CloseCurrentScene()
{
	Director::getInstance()->popScene();
}

void MessagingScene::CallBuildFactory()
{
	if (m_message->getString()[0] == 'G')
	{
		MessagingSystem::g_typeFactory = TYPE_GOLD;
	}
	else if (m_message->getString()[0] == 'O')
	{
		MessagingSystem::g_typeFactory = TYPE_OIL;
	}

	CloseCurrentScene();
}

/*virtual*/ bool MessagingScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* i_event)
{
	if (m_close->getBoundingBox().containsPoint(touch->getLocation()))
	{
		CloseCurrentScene();
	}
	else if (m_buildFactory->getBoundingBox().containsPoint(touch->getLocation()))
	{
		CallBuildFactory();
	}

	return true;
}
