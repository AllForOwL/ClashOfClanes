#ifndef __HOUSE_H__
#define __HOUSE_H__

#include "cocos2d.h"
#include "GraphicComponent.h"

using namespace cocos2d;

class GameScene;

class House: public GraphicComponent
{
public:
	~House(){};

	virtual void Update(GameScene& i_gameScene) = 0;
};

#endif