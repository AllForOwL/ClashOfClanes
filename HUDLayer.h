#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class ManagerComponent;

class HUDLayer : public cocos2d::Layer
{
public:

	enum StateContextMenu
	{
		ACTIVE,
		NOT_ACTIVE
	};

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

	void LoadSpritesForMenu(Point i_locationMenu);
	void LoadSpritesCombatantBar();

	void UpdateQuentityCombatant(ManagerComponent& i_manager);

	bool ShowContextMenu(ManagerComponent& i_manager);
	void HideContextMenu();

	void VerifyBuildFactory(ManagerComponent& i_manager);
	void VerifyHideContextMenu(ManagerComponent& i_manage);

private:
	Command					m_command;
	Vec2					m_locationTouch;
	std::vector<Rect>		m_vecRectMachine;
	std::vector<Sprite*>	m_vecSpriteMachine;

	std::vector<Label*> m_vecLabelCombatant;
	std::vector<int>	m_vecQuentityCombatant;
	StateContextMenu	m_stateContextMenu;

	Sprite*	m_sprMessage;
	Rect	m_rectMessage;
	Label*	m_lblQuentityNewMessage;

	Point m_prevPositionMapLayer;
	Point m_currPositionMapLayer;

};

#endif // __HUD_LAYER_H__
