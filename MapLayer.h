#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameScene;
class ManagerComponent;

class MapLayer : public TMXTiledMap
{
public:

	enum StateMap
	{
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		STOP
	};

	MapLayer();
	MapLayer(GameScene& i_parentGameScene);
	~MapLayer();

	void Update(ManagerComponent& i_manager);
	void FillRegionFromObject(Point i_point, Size i_size);
	void ReleasePositionAfterSearchWay();
	void SetState(StateMap& i_statemap);
	std::vector<std::vector<int>>& GetMapCoordinate();
	int GetQuentityEnemy(Point i_position);

private:
	std::vector<std::vector<int>> m_mapCoordinate;
	StateMap m_stateMap;
};

#endif