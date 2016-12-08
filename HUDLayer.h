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
		OPEN_MESSAGES,
		NOTHING
	};

	virtual bool init();

	~HUDLayer();

	CREATE_FUNC(HUDLayer);

	void Update(ManagerComponent& i_manager);
	bool DetermineCommandForManagerFactory();

	void ExecuteCommandForManagerFactory(ManagerComponent& i_manager);

	void LoadSpritesForMenu();
	void LoadSpritesCombatantBar();

	void OpenMessages();

	void UpdateQuentityCombatant(ManagerComponent& i_manager);

private:
	Command	m_command;
	Vec2	m_locationTouch;
	std::vector<Rect> m_vecRectMachine;

	std::vector<Label*> m_vecLabelCombatant;
	std::vector<int>	m_vecQuentityCombatant;
};

#endif // __HUD_LAYER_H__
