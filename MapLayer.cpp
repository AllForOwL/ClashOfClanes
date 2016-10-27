#include "MapLayer.h"
#include "constants.h"
#include "GameScene.h"

MapLayer::MapLayer()
{
	this->initWithTMXFile(CNT_PATH_TO_RESOURCES + "Map/Map.tmx");
}

MapLayer::MapLayer(GameScene& i_parentGameScene)
{
	i_parentGameScene.addChild(this);
	this->initWithTMXFile(CNT_PATH_TO_RESOURCES + "Map/Map.tmx");
}


MapLayer::~MapLayer()
{

}
