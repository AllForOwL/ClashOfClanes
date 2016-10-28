/*
	Architecture game

	ManagerComponent
*/



#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MapLayer;
class FamilyHouse;
class HeroGraphicComponent;
class ManagerComponent;

class GameScene : public cocos2d::Layer
{
public:
	~GameScene();

	static cocos2d::Scene *createScene();
	virtual bool init();

	CREATE_FUNC(GameScene);

	cocos2d::PhysicsWorld* m_sceneWorld;
	void SetPhysicsWorld(cocos2d::PhysicsWorld* world)
	{
		m_sceneWorld = world;
	}
	
	static Size	m_visibleSize;

private:
	Vec2	m_origin;

	ManagerComponent* m_manager;
};

#endif 