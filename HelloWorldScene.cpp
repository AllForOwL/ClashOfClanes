#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool HelloWorld::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    m_visibleSize	= Director::getInstance()->getVisibleSize();
    Vec2 origin		= Director::getInstance()->getVisibleOrigin();


	m_rectBottomLeft.setRect	(0, 0, m_visibleSize.width / 2, m_visibleSize.height / 2);
	m_rectBottomRight.setRect	(m_visibleSize.width / 2, 0, m_visibleSize.width / 2, m_visibleSize.height / 2);
	m_rectTopLeft.setRect		(0, m_visibleSize.height / 2, m_visibleSize.width / 2, m_visibleSize.height / 2);
	m_rectTopRight.setRect		(m_visibleSize.width / 2, m_visibleSize.height / 2, m_visibleSize.width / 2, m_visibleSize.height / 2);

	m_map = TMXTiledMap::create("E:/programming/cocos/project/ClashOfClans/Resources/res/backgrounds/Map.tmx");
	m_map->setPosition(-m_visibleSize.width * 3,
		m_visibleSize.height / 2 + origin.y);
	
	this->addChild(m_map);

	auto _winSize	= Director::getInstance()->getWinSize();
	m_camera = Camera::createOrthographic(m_visibleSize.width, m_visibleSize.height, -300, 10000);
	m_camera->setPosition3D(Vec3(0, 0, 0));
	this->addChild(m_camera);

	auto _touchListener = EventListenerTouchOneByOne::create();
	_touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

	//schedule(schedule_selector(HelloWorld::update), 0.1);

    return true;
}

/*virtual*/ bool HelloWorld::onTouchBegan(cocos2d::Touch* i_touch, cocos2d::Event* i_event)
{
	Touch* _touch = i_touch;
	Vec2 _locationTouch = _touch->getLocation();
	Vec3 _positionCamera = m_camera->getPosition3D();
	if (m_rectBottomLeft.containsPoint(_locationTouch))
	{
		m_camera->setPosition3D(Vec3(_positionCamera.x - 2, _positionCamera.y, _positionCamera.z));
	}
	else if (m_rectBottomRight.containsPoint(_touch->getLocation()))
	{
		m_camera->setPosition3D(Vec3(_positionCamera.x + 2, _positionCamera.y, _positionCamera.z));
	}
	else if (m_rectTopLeft.containsPoint(_locationTouch))
	{
		m_camera->setPosition3D(Vec3(_positionCamera.x, _positionCamera.y + 2, _positionCamera.z));
	}
	else
	{
		m_camera->setPosition3D(Vec3(_positionCamera.x, _positionCamera.y - 2, _positionCamera.z));
	}

	return true;
}

/*virtual*/ void HelloWorld::update(float dt)
{
	this->setPositionX(this->getPositionX() - 50);
	this->setPositionY(this->getPositionY() - 50);
}