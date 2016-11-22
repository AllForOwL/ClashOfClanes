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

	std::vector<std::vector<int>>& GetMapCoordinate();
	void Update							(ManagerComponent& i_manager);
	void FillRegionFromObject			(ManagerComponent& i_manager, int i_typeObject, Point i_positionObject, Size i_size);
	void ReleasePositionAfterSearchWay	();
	void SetState						(StateMap& i_statemap);
	int GetQuentityEnemy				(Point i_position);
	double StatusCells					(Point i_position, int i_typeObject);	// STATUS = { FREE = 1.0, BUSY = 0.0 }
	void FillRegionForResources			();
	Point GetPositionShelter			();


private:
	std::vector<std::vector<int>>	m_mapCoordinate;
	StateMap m_stateMap;
	Size	m_mapSize;
};

#endif