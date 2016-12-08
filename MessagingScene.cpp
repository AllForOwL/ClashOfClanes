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
		Label* _label = Label::create(MessagingSystem::m_vecMessages[i], "Herbana", 12);
		_positionY -= _label->getContentSize().height / 2;
		_label->setPosition(GameScene::m_visibleSize.width / 2, _positionY);
		this->addChild(_label);
	}
}

void MessagingScene::CloseCurrentScene()
{
	Director::getInstance()->popScene();
}

/*virtual*/ bool MessagingScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* i_event)
{
	if (m_close->getBoundingBox().containsPoint(touch->getLocation()))
	{
		CloseCurrentScene();
	}

	return true;
}
