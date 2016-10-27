#ifndef __HUD_LAYER_H__
#define __HUD_LAYER_H__

#include "cocos2d.h"

class HUDLayer : public cocos2d::Layer
{
public:
	~HUDLayer();
	virtual bool init();

	CREATE_FUNC(HUDLayer);

private:
	Size	m_visibleSize;
	Vec2	m_origin;

};

#endif // __HUD_LAYER_H__
