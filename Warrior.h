#ifndef __WARRIOR_H__
#define __WARRIOR_H__

#include "cocos2d.h"
#include "GraphicComponent.h"

class ManagerComponent;

class Warrior : public GraphicComponent
{
public:
	~Warrior(){};

	virtual void Update(ManagerComponent& i_manager) = 0;
};

#endif