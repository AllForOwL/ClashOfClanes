#ifndef __HERO_INPUT_COMPONENT_H__
#define __HERO_INPUT_COMPONENT_H__

#include "cocos2d.h"
#include "InputComponent.h"

using namespace std;
using namespace cocos2d;

class ManagerComponent;
class GameScene;

class HeroInputComponent : public InputComponent
{
public:

	HeroInputComponent();
	HeroInputComponent(HeroInputComponent& i_inputComponent);

	enum StateInput
	{

	};

	virtual void Update(ManagerComponent& i_manager);
	
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	~HeroInputComponent();

public:
	StateInput		m_stateInput;
	cocos2d::Vec2	m_locationTouch;
};

#endif