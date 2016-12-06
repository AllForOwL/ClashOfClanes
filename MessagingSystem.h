#ifndef __MESSAGING_SYSTEM_H__
#define __MESSAGING_SYSTEM_H__

#include "cocos2d.h"

USING_NS_CC;

class ManagerComponent;

class MessagingSystem : public cocos2d::Layer
{
public:
	static cocos2d::Scene *createScene();
	virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

	CREATE_FUNC(MessagingSystem);

	void AddMesssage(std::string i_message);
	void OpenMessages();

	void CloseScene();

private:
	std::vector<std::string> m_vecMessages;
	cocos2d::Sprite* m_sprCloseScene;
};

#endif