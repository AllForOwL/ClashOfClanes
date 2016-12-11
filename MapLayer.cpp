#include "MapLayer.h"
#include "constants.h"
#include "GameScene.h"
#include "ManagerComponent.h"
#include "HeroGraphicComponent.h"
#include "ManagerComponent.h"
#include "ManagerObjectAndFile.h"
#include <fstream>
#include <string>
#include <regex>

const int CNT_ZONE_WIDTH_RESOURCES	= 100;
const int CNT_ZONE_HEIGHT_RESOURCES = 100;

MapLayer::MapLayer()
{
	this->initWithTMXFile(CNT_PATH_TO_RESOURCES + "Map/Map.tmx");
}

MapLayer::MapLayer(GameScene& i_parentGameScene)
{
	i_parentGameScene.addChild(this);
	this->initWithTMXFile(CNT_PATH_TO_RESOURCES + "Map/Map.tmx");

	m_mapSize = Size(this->getMapSize().width * this->getTileSize().width,
				this->getMapSize().height * this->getTileSize().height);

	m_mapCoordinate.resize(m_mapSize.width);
	for (int i = 0; i < m_mapSize.width; i++)
	{
		m_mapCoordinate[i].resize(m_mapSize.height);
	}

	for (int i = 0; i < m_mapSize.width; i++)
	{
		for (int j = 0; j < m_mapSize.height; j++)
		{
			if (i == 0 || i == m_mapSize.width - 1 || j == 0 || j == m_mapSize.height - 1)
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
			i_manager.m_hero->MoveUp();

			break;
		}
		case StateMap::MOVE_DOWN:
		{
			setPositionY(getPositionY() - CNT_SPEED_MAP);
			i_manager.m_hero->MoveDown();
	
			break;
		}
		case StateMap::MOVE_LEFT:
		{
			setPositionX(getPositionX() - CNT_SPEED_MAP);
			i_manager.m_hero->MoveLeft();
			
			break;
		}
		case StateMap::MOVE_RIGHT:
		{
			setPositionX(getPositionX() + CNT_SPEED_MAP);			
			i_manager.m_hero->MoveRight();
			i_manager.m_hero->HideMenu();

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

void MapLayer::FillRegionFromObject(ManagerComponent& i_manager, int i_typeObject, Point i_positionObject, Size i_size)
{
	Point _positionBegin = Point(i_positionObject.x - (i_size.width / 2), i_positionObject.y + (i_size.height / 2));
	Point _positionEnd	 = Point(i_positionObject.x + (i_size.width / 2), i_positionObject.y - (i_size.height / 2));
	Point _positionOrigin = this->getPosition();

	if (_positionOrigin.x < 0)
	{
		_positionOrigin.x *= (-1);
	}
	if (_positionOrigin.y < 0)
	{
		_positionOrigin.y *= (-1);
	}
	
	for (int i = _positionBegin.x; i < _positionEnd.x; i++)
	{
		for (int j = _positionBegin.y; j > _positionEnd.y; j--)
		{
			this->m_mapCoordinate[i][j] = i_typeObject;
		}
	}
}

Point MapLayer::GetPositionShelter()
{
	for (int x = 0; x < m_mapSize.width; x++)
	{
		for (int y = 0; y < m_mapSize.height; y++)
		{
			if (m_mapCoordinate[x][y] == CNT_OBJECT_SHELTER)
			{
				return Point(x, y);
			}
		}
	}

	return Point::ZERO;
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
	CCLOG("DESTRUCTOR MAPLAYER");
}
