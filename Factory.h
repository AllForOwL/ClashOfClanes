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

		m_positionVisible = i_positionVisible;

		m_positionOrigin = this->getParent()->getPosition();
		m_positionOrigin.x *= (-1);
		m_positionOrigin.y *= (-1);

		this->initWithFile(CNT_PATH_TO_RESOURCES + i_fileFactory);
		this->setScale(GameScene::m_visibleSize.width / this->getContentSize().width / 6,
			GameScene::m_visibleSize.height / this->getContentSize().height / 6);

		m_locationTouch = Point::ZERO;

		Rect _box = this->getBoundingBox();

		// calculate RectOrigin(system coordinate all MapLayer)
		m_rectOrigin = Rect(this->getBoundingBox().getMinX() + m_positionOrigin.x, this->getBoundingBox().getMinY() + m_positionOrigin.y,
			this->getBoundingBox().size.width, this->getBoundingBox().size.height);
		// calculate RectVisible(system coordinate visible MapLayer)
		m_rectVisible = Rect(this->getBoundingBox().getMinX() + m_positionVisible.x, this->getBoundingBox().getMinY() + m_positionVisible.y,
			this->getBoundingBox().size.width, this->getBoundingBox().size.height);

		m_rectOriginWithVisible = Rect(this->getBoundingBox().getMinX() + m_positionOrigin.x + m_positionVisible.x,
			this->getBoundingBox().getMinY() + m_positionOrigin.y + m_positionVisible.y,
			this->getBoundingBox().size.width, this->getBoundingBox().size.height
			);

		m_numberComplete = 0;

		m_positionOriginWithVisible = m_positionOrigin + m_positionVisible;
		this->setPosition(m_positionOriginWithVisible);

	}

	virtual void Update(ManagerComponent& i_manager) = 0;

	~Factory(){};

};

#endif