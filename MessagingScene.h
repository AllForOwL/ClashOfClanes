#ifndef __MESSAGING_SCENE_H__
#define __MESSAGING_SCENE_H__

#include "cocos2d.h"

class MessagingScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene *createScene();
	virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* i_event);

	CREATE_FUNC(MessagingScene);

	void CloseCurrentScene();

	void OpenMessagings();

	void AddElement();

	void CallBuildFactory();

private:
	cocos2d::Sprite* m_close;
	cocos2d::Label* m_buildFactory;
	cocos2d::Label* m_message;
};

#endif
