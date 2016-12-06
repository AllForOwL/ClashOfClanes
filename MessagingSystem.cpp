#include "MessagingSystem.h"
#include "GameScene.h"
#include "constants.h"

USING_NS_CC;

Scene *MessagingSystem::createScene()
{
	auto scene = Scene::create();

	auto layer = MessagingSystem::create();

	scene->addChild(layer);

	return scene;
}

bool MessagingSystem::init()
{
	if (!Layer::init())	// if layer not create exit from function
	{
		return false;
	}

	this->setColor(Color3B(rand() % 255 + 0, rand() % 255 + 0, rand() % 255 + 0));
	this->setPosition(GameScene::m_visibleSize.width / 2, GameScene::m_visibleSize.height / 2);

	m_sprCloseScene = Sprite::create(CNT_PATH_TO_RESOURCES + "Item/Message/Close.png", Rect(GameScene::m_visibleSize.width - 40, 
		GameScene::m_visibleSize.height - 20, 40, 20));
	this->addChild(m_sprCloseScene);

	auto _touchListener = EventListenerTouchOneByOne::create();
	_touchListener->onTouchBegan = CC_CALLBACK_2(MessagingSystem::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

	return true;
}

/*virtual*/ bool MessagingSystem::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (m_sprCloseScene->getBoundingBox().containsPoint(touch->getLocationInView()))
	{
		CloseScene();
	}

	return true;
}

void MessagingSystem::CloseScene()
{

}

void MessagingSystem::AddMesssage(std::string i_message)
{
	m_vecMessages.push_back(i_message);
}

void MessagingSystem::OpenMessages()
{
	Point _positionLabel = Point(GameScene::m_visibleSize.width / 2, GameScene::m_visibleSize.height);
	for (int i = 0; i < m_vecMessages.size(); i++)
	{
		Label* _label = Label::create(m_vecMessages[i], "Helvetica", 20.0);
		_positionLabel.y -= _label->getContentSize().height / 2;
		_label->setPosition(_positionLabel.x, _positionLabel.y);
		this->addChild(_label);
	}
}
