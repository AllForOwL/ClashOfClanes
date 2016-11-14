#include "MapLayer.h"
#include "constants.h"
#include "GameScene.h"
#include "ManagerComponent.h"

const int CNT_TAG_ARCHER = 1000;

const int CNT_SPEED_MAP = 1;

MapLayer::MapLayer()
{
	this->initWithTMXFile(CNT_PATH_TO_RESOURCES + "Map/Map.tmx");
}

MapLayer::MapLayer(GameScene& i_parentGameScene)
{
	i_parentGameScene.addChild(this);
	this->initWithTMXFile(CNT_PATH_TO_RESOURCES + "Map/Map.tmx");

	Size _size = Size(this->getMapSize().width * this->getTileSize().width,
				this->getMapSize().height * this->getTileSize().height);

	m_mapCoordinate.resize(_size.width);
	for (int i = 0; i < _size.width; i++)
	{
		m_mapCoordinate[i].resize(_size.height);
	}

	for (int i = 0; i < _size.width; i++)
	{
		for (int j = 0; j < _size.height; j++)
		{
			if (i == 0 || i == _size.width - 1 || j == 0 || j == _size.height - 1)
			{
				m_mapCoordinate[i][j] = CNT_POSITION_BUSY_ORDER;
			}
		}
	}

}

void MapLayer::Update(ManagerComponent& i_manager)
{
	switch (m_stateMap)
	{
		case StateMap::MOVE_UP:
		{
			setPositionY(getPositionY() + CNT_SPEED_MAP);

			break;
		}
		case StateMap::MOVE_DOWN:
		{
			setPositionY(getPositionY() - CNT_SPEED_MAP);

			break;
		}
		case StateMap::MOVE_LEFT:
		{
			setPositionX(getPositionX() - CNT_SPEED_MAP);

			break;
		}
		case StateMap::MOVE_RIGHT:
		{
			setPositionX(getPositionX() + CNT_SPEED_MAP);			

			break;
		}
		case StateMap::STOP:
		{
			
			break;
		}
	default:
		break;
	}
}

void MapLayer::ReleasePositionAfterSearchWay()
{
	Size _size = Size(this->getMapSize().width * this->getTileSize().width,
		this->getMapSize().height * this->getTileSize().height);

	for (int i = 0; i < _size.width; i++)
	{
		for (int j = 0; j < _size.height; j++)
		{
			if (m_mapCoordinate[i][j] == CNT_POSITION_BUSY_SEARCH_WAY)
			{
				m_mapCoordinate[i][j] = CNT_POSITION_FREE;
			}
		}
	}
}

std::vector<std::vector<int>>& MapLayer::GetMapCoordinate()
{
	return m_mapCoordinate;
}

void MapLayer::FillRegionFromObject(int i_typeObject, Point i_point, Size i_size)
{
	Point _positionBegin = Point(i_point.x - (i_size.width / 2), i_point.y + (i_size.height / 2));
	Point _positionEnd	 = Point(i_point.x + (i_size.width / 2), i_point.y - (i_size.height / 2));
	Point _thisPosition = this->getPosition();
	_thisPosition.x *= (-1);
	_thisPosition.y *= (-1);

	_positionBegin	+= _thisPosition;
	_positionEnd	+= _thisPosition;
	for (int i = _positionBegin.x; i < _positionEnd.x; i++)
	{
		for (int j = _positionBegin.y; j > _positionEnd.y; j--)
		{
			this->m_mapCoordinate[i][j] = i_typeObject;
		}
	}
}

void MapLayer::SetState(StateMap& i_statemap)
{
	m_stateMap = i_statemap;
}

double MapLayer::StatusCells(Point i_position, int i_typeObject)
{
	Point _thisPosition = this->getPosition();
	_thisPosition.x *= (-1);
	_thisPosition.y *= (-1);
	i_position += _thisPosition;
	
	if (m_mapCoordinate[i_position.x][i_position.y] == CNT_POSITION_FREE || 
		m_mapCoordinate[i_position.x][i_position.y] == i_typeObject)
	{
		return 1.0;
	}
	else
	{
		return 0.0;
	}

}

int MapLayer::GetQuentityEnemy(Point i_position)
{
	int _quentityEnemy = 0;

	Point _thisPosition = this->getPosition();
	_thisPosition.x *= (-1);
	_thisPosition.y *= (-1);
	i_position += _thisPosition;

	for (int x = i_position.x - 8; x < i_position.x + 8; x++)
	{
		for (int y = i_position.y - 8; y < i_position.y + 8; y++)
		{
			if (this->m_mapCoordinate[x][y] != CNT_POSITION_FREE)
			{
				++_quentityEnemy;
			}
		}
	}
	return _quentityEnemy;
}

MapLayer::~MapLayer()
{

}
