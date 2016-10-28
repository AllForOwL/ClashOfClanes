#ifndef __HOUSE_H__
#define __HOUSE_H__

#include "cocos2d.h"
#include "GraphicComponent.h"

using namespace cocos2d;

class ManagerComponent;

class House: public GraphicComponent
{
public:
	~House(){};

	virtual void Update(ManagerComponent& i_manager) = 0;
};

#endif