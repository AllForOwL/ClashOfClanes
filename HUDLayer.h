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
		CREATE_MACHINE,
		CREATE_WARRIOR,
		NOTHING
	};

	enum CommandMachine
	{
		CREATE_TANK,
		CREATE_CAR,
		NOTHING
	};

	enum CommandWarrior
	{
		CREATE_ARCHER,
		CREATE_KNIGHT_BLACK,
		CREATE_KNIGHT_BRONZE,
		CREATE_KNIGHT_SILVER,
		NOTHING
	};

	enum StateTypeMenu
	{
		FACTORY_MACHINE,
		FACTORY_WARRIOR,
		NOTHING
	};

	virtual bool init();

	~HUDLayer();

	CREATE_FUNC(HUDLayer);

	void Update(ManagerComponent& i_manager);
	bool DetermineCommandForManagerFactory();
	bool DetermineCommandForFactoryMachine();
	bool DetermineCommandForFactoryWarrior();
	
	void ExecuteCommandForManagerFactory(ManagerComponent& i_manager);
	void ExecuteCommandForFactoryMachine(ManagerComponent& i_manager);
	void ExecuteCommandForFactoryWarrior(ManagerComponent& i_manager);

	void LoadNameForAllSprites();
	void LoadSpritesForFactory();
	void LoadSpritesForMenu();

	void ShowMenuForFactoryMachine();
	void ShowMenuForFactoryWarrior();

	static StateTypeMenu m_typeMenu;;

private:
	Sprite*	m_factoryMachine;
	Sprite*	m_factoryWarrior;
	Rect	m_rectFactoryMachine;
	Rect	m_rectFactoryWarrior;
	Command			m_command;
	CommandMachine	m_commandMachine;
	CommandWarrior	m_commandWarrior;

	Vec2	m_locationTouch;

	std::vector<Sprite*>	m_vecSpritesForFactoryMachine;
	std::vector<Sprite*>	m_vecSpritesForFactoryWarrior;

	std::vector<std::string> m_vecNameFactoryMachine;
	std::vector<std::string> m_vecNameFactoryWarrior;

	std::vector<Rect>	m_vecRectSpritesFactoryMachine;
	std::vector<Rect>	m_vecRectSpritesFactoryWarrior;
};

#endif // __HUD_LAYER_H__
