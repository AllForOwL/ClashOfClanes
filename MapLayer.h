#ifndef __MAP_LAYER_H__
#define __MAP_LAYER_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameScene;
class ManagerComponent;

class MapLayer : public TMXTiledMap
{
public:

	struct ObjectInFile
	{
		int		typeObject;
		Size	size;
		Point	position;
	};

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
	void FillRegionFromObject			(int i_typeObject, Point i_point, Size i_size);
	void ReleasePositionAfterSearchWay	();
	void SetState						(StateMap& i_statemap);
	int GetQuentityEnemy				(Point i_position);
	double StatusCells					(Point i_position, int i_typeObject);	// STATUS = { FREE = 1.0, BUSY = 0.0 }
	void FillRegionForResources			();
	Point GetPositionShelter			();
	void WriteObjectToFile(int i_typeObject, Point i_point, Size i_size);
	
	void AddObjectFromFile();
	std::vector<ObjectInFile>& GetVectorObject();

private:
	std::vector<ObjectInFile>		m_vecObject;
	std::vector<std::vector<int>>	m_mapCoordinate;
	StateMap m_stateMap;
	Size	m_mapSize;
};

#endif