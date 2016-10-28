#ifndef __GRAPHIC_COMPONENT_H__
#define __GRAPHIC_COMPONENT_H__

#include "cocos2d.h"

using namespace cocos2d;

class ManagerComponent;

class GraphicComponent : public Sprite
{
public:
	GraphicComponent(){};
	virtual ~GraphicComponent(){};

	virtual void Update(ManagerComponent& i_manager) = 0;
	
	virtual std::chrono::time_point<std::chrono::system_clock> GetTime()
	{
		std::chrono::time_point<std::chrono::system_clock> _time = std::chrono::system_clock::now();

		return _time;
	}

};

#endif