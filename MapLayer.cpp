#include "MapLayer.h"
#include "constants.h"
#include "GameScene.h"

const int CNT_TAG_ARCHER = 1000;

MapLayer::MapLayer()
{
	this->initWithTMXFile(CNT_PATH_TO_RESOURCES + "Map/Map.tmx");
}

MapLayer::MapLayer(GameScene& i_parentGameScene)
{
	i_parentGameScene.addChild(this);
	this->initWithTMXFile(CNT_PATH_TO_RESOURCES + "Map/Map.tmx");
	auto layer = this->layerNamed("Layer");

	Size _size = Size(this->getMapSize().width * this->getTileSize().width,
	this->getMapSize().height * this->getTileSize().height);

	m_mapCoordinate.resize(_size.width);
	for (int i = 0; i < _size.width; i++)
	{
		m_mapCoordinate[i].resize(_size.height);
	}
}

void MapLayer::FillRegionFromOvbject(Point i_point, Size i_size)
{
	for (int i = _position.x; i < _position.x + i_size.width; i++)
	{
		for (int j = _position.y; j < _position.y + i_size.height; j++)
		{
			this->m_mapCoordinate[i][j] = CNT_TAG_ARCHER;
		}
	}
}

MapLayer::~MapLayer()
{

}
