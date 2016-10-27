#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene *createScene();
	virtual bool init();

	CREATE_FUNC(MainMenuScene);

	void GoToGameScene(cocos2d::Ref* ref);
};

#endif // __MAIN_MENU_SCENE_H__
