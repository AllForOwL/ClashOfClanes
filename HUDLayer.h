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
		OPEN_MESSAGES,
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

	void OpenMessages();

	void UpdateQuentityCombatant(ManagerComponent& i_manager);

	void VerifyOpenMessage(ManagerComponent& i_manager);

	bool ShowContextMenu(ManagerComponent& i_manager);
	void HideContextMenu();

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

	Point m_prevPositionMapLayer;
	Point m_currPositionMapLayer;

};

#endif // __HUD_LAYER_H__
