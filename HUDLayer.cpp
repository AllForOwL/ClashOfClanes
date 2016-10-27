#include "HUDLayer.h"

USING_NS_CC;


bool HUDLayer::init()
{
	if (!Layer::init())	// if layer not create exit from function
	{
		return false;
	}

	m_visibleSize	= Director::getInstance()->getVisibleSize();
	m_origin		= Director::getInstance()->getVisibleOrigin();
	
	return true;
}