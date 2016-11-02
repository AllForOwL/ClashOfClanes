#ifndef __HERO_INPUT_COMPONENT_H__
#define __HERO_INPUT_COMPONENT_H__

#include "cocos2d.h"
#include "InputComponent.h"

USING_NS_CC;

class ManagerComponent;
class GameScene;

class HeroInputComponent : public InputComponent
{
public:

	enum StateInput
	{
		VERIFY_INPUT_MOVED,
		STOP,
		NOTHING
	};

	HeroInputComponent();
	HeroInputComponent(HeroInputComponent& i_inputComponent);

	virtual void Update(ManagerComponent& i_manager);
	
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* i_event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* i_event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* i_event);

	Vec2 GetLocationTouch() const;
	void SetZeroLocation();

	Vec2 GetPreviousLocationTouch() const;

	~HeroInputComponent();

private:
	cocos2d::Vec2	m_locationTouch;
	cocos2d::Vec2	m_previousLocationTouch;

	Point m_startPositionMoved;
	Point m_endPositionMoved;

	StateInput m_stateInput;

};

#endif