#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "cocos2d.h"
#include "GraphicComponent.h"
#include "GameScene.h"
#include "MapLayer.h"
#include "constants.h"

using namespace cocos2d;

class Factory : public GraphicComponent
{
public:
	Factory(){};
	Factory(Point i_positionVisible, MapLayer& i_mapLayer, std::string i_fileFactory)
	{
		i_mapLayer.addChild(this);
		this->initWithFile(CNT_PATH_TO_RESOURCES + i_fileFactory);
		this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 6,
			GameScene::m_visibleSize.height / this->getContentSize().height / 6);

		LoadProperties(i_positionVisible, i_mapLayer.getPosition());
	}

	virtual void Update(ManagerComponent& i_manager) = 0;

	~Factory(){};
};

#endif