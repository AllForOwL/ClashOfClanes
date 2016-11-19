#include "MapLayer.h"
#include "constants.h"
#include "GameScene.h"
#include "ManagerComponent.h"
#include "HeroGraphicComponent.h"
#include <fstream>
#include <string>
#include <regex>

const int CNT_SPEED_MAP = 1;

const int CNT_ZONE_WIDTH_RESOURCES	= 100;
const int CNT_ZONE_HEIGHT_RESOURCES = 100;

MapLayer::MapLayer()
{
	this->initWithTMXFile(CNT_PATH_TO_RESOURCES + "Map/Map.tmx");
	AddObjectFromFile();
}

void MapLayer::AddObjectFromFile()
{
	std::ifstream _readFromFile;
	_readFromFile.open(CNT_PATH_TO_RESOURCES + "Map/Map.xml");

	char* _linePropertiesObject = new char[200];

	while (!_readFromFile.eof())
	{
		_readFromFile.getline(_linePropertiesObject, 200);
		int _index = 1;
		std::vector<int> _vecPropertiesObject;
		std::string _intermediateString;

		char _value = _linePropertiesObject[_index];
		do
		{
			if ((int)_value >= 48 && (int)_value <= 57)
			{
				_intermediateString = _value;
				_value = _linePropertiesObject[++_index];
				while (_value != ' ')
				{
					_intermediateString += _value;
					_value = _linePropertiesObject[++_index];
				}
				_vecPropertiesObject.push_back(std::stoi(_intermediateString));
			}
			_value = _linePropertiesObject[++_index];
		} while (_value != '>');

		ObjectInFile _object;
		_object.typeObject	= _vecPropertiesObject[0];
		Size _size			= Size(_vecPropertiesObject[1], _vecPropertiesObject[2]);
		_object.size		= _size;;
		Point _point		= Point(_vecPropertiesObject[3], _vecPropertiesObject[4]);
		_object.position	= _point;

		m_vecObject.push_back(_object);
	}

	_readFromFile.close();
}

std::vector<MapLayer::ObjectInFile>& MapLayer::GetVectorObject()
{
	return m_vecObject;
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

	FillRegionForResources();
	AddObjectFromFile();
}

void MapLayer::Update(ManagerComponent& i_manager)
{
	switch (m_stateMap)
	{
		case StateMap::MOVE_UP:
		{
			setPositionY(getPositionY() + CNT_SPEED_MAP);
			i_manager.m_hero->setPositionY(i_manager.m_hero->getPositionY() - CNT_SPEED_MAP);

			break;
		}
		case StateMap::MOVE_DOWN:
		{
			setPositionY(getPositionY() - CNT_SPEED_MAP);
			i_manager.m_hero->setPositionY(i_manager.m_hero->getPositionY() + CNT_SPEED_MAP);

			break;
		}
		case StateMap::MOVE_LEFT:
		{
			setPositionX(getPositionX() - CNT_SPEED_MAP);
			i_manager.m_hero->setPositionX(i_manager.m_hero->getPositionX() + CNT_SPEED_MAP);

			break;
		}
		case StateMap::MOVE_RIGHT:
		{
			setPositionX(getPositionX() + CNT_SPEED_MAP);			
			i_manager.m_hero->setPositionX(i_manager.m_hero->getPositionX() - CNT_SPEED_MAP);

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
	WriteObjectToFile(i_typeObject, _positionBegin, i_size);

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
}

void MapLayer::SetState(StateMap& i_statemap)
{
	m_stateMap = i_statemap;
}

void MapLayer::FillRegionForResources()
{
	/*srand(time(NULL));

	int _x	= rand() % 700 + 500;
	int _y	= rand() % 300 + 100;
	Point	_positionBegin	= Point(_x, _y);
	for (int x = _positionBegin.x; x < _positionBegin.x + CNT_ZONE_WIDTH_RESOURCES; x++)
	{
		for (int y = _positionBegin.y; y < _positionBegin.y + CNT_ZONE_HEIGHT_RESOURCES; y++)
		{
			m_mapCoordinate[x][y]	= CNT_RESOURCES_GOLD;
		}
	}

	_x	= rand() % 700 + 600;
	_y	= rand() % 700 + 500;
	_positionBegin.setPoint(_x, _y);
	for (int x = _positionBegin.x; x < _positionBegin.x + CNT_ZONE_WIDTH_RESOURCES; x++)
	{
		for (int y = _positionBegin.y; y < _positionBegin.y + CNT_ZONE_HEIGHT_RESOURCES; y++)
		{
			m_mapCoordinate[x][y] = CNT_RESOURCES_TREE;
		}
	}

	_x	= rand() % 1000 + 500;
	_y	= rand() % 900 + 800;
	_positionBegin.setPoint(_x, _y);
	for (int x = _positionBegin.x; x < _positionBegin.x + CNT_ZONE_WIDTH_RESOURCES; x++)
	{
		for (int y = _positionBegin.y; y < _positionBegin.y + CNT_ZONE_HEIGHT_RESOURCES; y++)
		{
			m_mapCoordinate[x][y] = CNT_RESOURCES_OIL;
		}
	}*/
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

void MapLayer::WriteObjectToFile(int i_typeObject, Point i_point, Size i_size)
{
	std::ofstream	_fileForWrite;
	_fileForWrite.open(CNT_PATH_TO_RESOURCES + "/Map/Map.xml", std::ios_base::app);

	_fileForWrite	<< "<"				<< i_typeObject	
					<< " size width = "	<< (int)i_size.width
					<< " height = "		<< (int)i_size.height
					<< " position x = "	<< (int)i_point.x
					<< " y = "			<< (int)i_point.y
					<< ">" << std::endl;

	_fileForWrite.close();
}

MapLayer::~MapLayer()
{
	CCLOG("DESTRUCTOR MAPLAYER");
}
