#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class ManagerComponent;

class HUDLayer : public cocos2d::Layer
{
public:

	enum Command
	{
		CREATE_FACTORY_MACHINE,
		CREATE_FACTORY_WARRIOR,
		CREATE_FACTORY_ENEMY_WARRIOR,
		CREATE_FACTORY_ENEMY_MACHINE,
		NOTHING
	};

	virtual bool init();

	~HUDLayer();

	CREATE_FUNC(HUDLayer);

	void Update(ManagerComponent& i_manager);
	bool DetermineCommandForManagerFactory();

	void ExecuteCommandForManagerFactory(ManagerComponent& i_manager);

	void LoadSpritesForMenu();

private:
	Command	m_command;
	Vec2	m_locationTouch;
	Rect	m_rectFactoryMachine;
	Rect	m_rectFactoryWarrior;
	Rect	m_rectFactoryEnemyWarrior;

};

#endif // __HUD_LAYER_H__
