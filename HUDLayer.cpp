#include "HUDLayer.h"

bool HUDLayer::init()
{
	if (!Layer::init())	
	{
		return false;
	}

	m_visibleSize	= Director::getInstance()->getVisibleSize();
	m_origin		= Director::getInstance()->getVisibleOrigin();
	
	return true;
}