#ifndef __GRAPHIC_COMPONENT_H__
#define __GRAPHIC_COMPONENT_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameScene;

class GraphicComponent : public Sprite
{
public:
	GraphicComponent(){};
	virtual ~GraphicComponent(){};

	virtual void Update(GameScene& i_gameScene) = 0;
	
};

#endif