#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
   
    CREATE_FUNC(HelloWorld);

	virtual void update(float dt);

	virtual bool onTouchBegan(cocos2d::Touch* i_touch, cocos2d::Event* i_event);

private:
	cocos2d::Size			m_visibleSize;
	cocos2d::TMXTiledMap*	m_map;
	cocos2d::Camera*		m_camera;
	
	cocos2d::Rect			m_rectBottomLeft;
	cocos2d::Rect			m_rectBottomRight;
	cocos2d::Rect			m_rectTopRight;
	cocos2d::Rect			m_rectTopLeft;


};

#endif // __HELLOWORLD_SCENE_H__
