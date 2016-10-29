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
		NOTHING
	};

	virtual bool init();

	~HUDLayer();

	CREATE_FUNC(HUDLayer);

	void Update(ManagerComponent& i_manager);
	bool DetermineCommand();
	void ExecuteCommand(ManagerComponent& i_manager);
	
private:
	Sprite*	m_factoryMachine;
	Sprite*	m_factoryWarrior;
	Rect	m_rectFactoryMachine;
	Rect	m_rectFactoryWarrior;
	Command	m_command;

	Vec2	m_locationTouch;
};

#endif // __HUD_LAYER_H__
