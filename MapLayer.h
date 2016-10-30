#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameScene;

class MapLayer : public TMXTiledMap
{
public:
	MapLayer();
	MapLayer(GameScene& i_parentGameScene);
	~MapLayer();

	void FillRegionFromOvbject(Point i_point, Size i_size);

private:
	std::vector<std::vector<int>> m_mapCoordinate;
};

#endif