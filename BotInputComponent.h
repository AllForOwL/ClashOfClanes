#ifndef __BOT_INPUT_COMPONENT_H__
#define __BOT_INPUT_COMPONENT_H__

#include "cocos2d.h"
#include "InputComponent.h"

USING_NS_CC;

class ManagerComponent;

class BotInputComponent : public InputComponent
{
public:
	BotInputComponent();

	virtual void Update(ManagerComponent& i_manager);

	~BotInputComponent();

private:

};

#endif