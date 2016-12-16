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
	Point GetPositionShelter			();
	void SetZoneForFactory				(ManagerComponent& i_manager);

	int VerifyBuildFactoryMachine		(Point i_locationTouch);
	int VerifyBuildFactoryWarrior		(Point i_locationTouch);
	void BuildFactoryMachine			(int i_numberRect);
	void BuildFactoryWarrior			(int i_numberRect);
	void VerifyBuildFactory				(ManagerComponent& i_manager);


private:
	std::vector<std::vector<int>>	m_mapCoordinate;
	StateMap m_stateMap;
	Size	m_mapSize;

	std::vector<Rect*>	m_vecZoneFactoryWarrior;
	std::vector<Rect*>	m_vecZoneFactoryMachine;
	std::vector<Sprite*>	m_vecSprZoneFactoryWarrior;
	std::vector<Sprite*>	m_vecSprZoneFactoryMachine;

};

#endif