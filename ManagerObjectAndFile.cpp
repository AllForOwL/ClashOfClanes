#include "ManagerObjectAndFile.h"
#include "GraphicComponent.h"
#include "MapLayer.h"
#include "ManagerArmy.h"
#include "ManagerMachine.h"
#include "ManagerFactory.h"
#include "ManagerComponent.h"
#include "GameScene.h"
#include "constants.h"
#include <fstream>

const int ASCII_CODE_0 = 48;
const int ASCII_CODE_9 = 57;

ManagerObjectAndFile::ManagerObjectAndFile()
{

}

ManagerObjectAndFile::ManagerObjectAndFile(ManagerObjectAndFile& i_ManagerObjectAndFile)
{

}

void ManagerObjectAndFile::AddObjectFromFile(GameScene& i_gameScene, ManagerComponent& i_manager)
{
	using StateArmy		= ManagerArmy::StateManagerArmy;
	using StateMachine	= ManagerMachine::StateManagerMachine;
	using StateFactory	= ManagerFactory::StateManagerFactory;

	StateArmy _stateArmy		= StateArmy::NOTHING;
	StateMachine _stateMachine	= StateMachine::NOTHING;
	StateFactory _stateFactory	= StateFactory::NOTHING;
	
	for (int i = 0; i < m_vecObject.size(); i++)
	{
		_stateArmy		= StateArmy::NOTHING;
		_stateMachine	= StateMachine::NOTHING;
		_stateFactory	= StateFactory::NOTHING;
		switch (m_vecObject[i].typeObject)
		{
			case CNT_OBJECT_FACTORY_WARRIOR:
			{
				_stateFactory = StateFactory::ADD_FACTORY_WARRIOR;
				break;
			}
			case CNT_OBJECT_FACTORY_MACHINE:
			{
				_stateFactory = StateFactory::ADD_FACTORY_MACHINE;
				break;
			}
			case CNT_OBJECT_FACTORY_ENEMY_WARRIOR:
			{
				_stateFactory = StateFactory::ADD_FACTORY_ENEMY_WARRIOR;
				break;
			}
			case CNT_OBJECT_FACTORY_ENEMY_MACHINE:
			{
				_stateFactory = StateFactory::ADD_FACTORY_ENEMY_MACHINE;
				break;
			}
			case CNT_OBJECT_KNIGHT_BLACK:
			{
				_stateArmy = StateArmy::ADD_KNIGHT_BLACK;
				break;
			}
			case CNT_OBJECT_KNIGHT_BRONZE:
			{
				_stateArmy = StateArmy::ADD_KNIGHT_BRONZE;
				break;
			}
			case CNT_OBJECT_KNIGHT_SILVER:
			{
				_stateArmy = StateArmy::ADD_KNIGHT_SILVER;
				break;
			}
			case CNT_OBJECT_ENEMY_BOWMAN:
			{
				_stateArmy = StateArmy::ADD_ENEMY_BOWMAN;
				break;
			}
			case CNT_OBJECT_ENEMY_KNIGHT:
			{
				_stateArmy = StateArmy::ADD_ENEMY_KNIGHT;
				break;
			}
			case CNT_OBJECT_ENEMY_WIZARD:
			{
				_stateArmy = StateArmy::ADD_ENEMY_WIZARD;
				break;
			}
			case CNT_OBJECT_ENEMY_PALADIN:
			{
				_stateArmy = StateArmy::ADD_ENEMY_PALADIN;
				break;
			}
			case CNT_OBJECT_ENEMY_OCTOPEDE:
			{
				_stateMachine = StateMachine::ADD_ENEMY_OCTOPEDE;
				break;
			}
			case CNT_OBJECT_ENEMY_BRAIN:
			{
				_stateMachine = StateMachine::ADD_ENEMY_BRAIN;
				break;
			}
			case CNT_OBJECT_ENEMY_TURTLE:
			{
				_stateMachine = StateMachine::ADD_ENEMY_TURTLE;
				break;
			}
		}

		if (_stateArmy != StateArmy::NOTHING)
		{
			i_manager.m_mapLayer->setPosition				(m_vecObject[i].positionOrigin);
			i_manager.m_managerArmy->SetState				(_stateArmy);
			i_manager.m_managerArmy->SetPositionForWarrior	(m_vecObject[i].positionVisible);
			i_manager.m_managerArmy->Update					(i_gameScene, i_manager);
			i_manager.m_mapLayer->setPosition				(Point::ZERO);
		}
		else if (_stateFactory != StateFactory::NOTHING)
		{
			i_manager.m_mapLayer->setPosition					(m_vecObject[i].positionOrigin);
			i_manager.m_managerFactory->SetState				(_stateFactory);
			i_manager.m_managerFactory->SetPositionBuildFactory	(m_vecObject[i].positionVisible);
			i_manager.m_managerFactory->Update					(i_gameScene, i_manager);
			i_manager.m_mapLayer->setPosition					(Point::ZERO);
		}
		else if (_stateMachine != StateMachine::NOTHING)
		{
			i_manager.m_mapLayer->setPosition					(m_vecObject[i].positionOrigin);
			i_manager.m_managerMachine->SetState				(_stateMachine);
			i_manager.m_managerMachine->SetPositionForMachine	(m_vecObject[i].positionVisible);
			i_manager.m_managerMachine->Update					(i_gameScene, i_manager);
			i_manager.m_mapLayer->setPosition					(Point::ZERO);
		}
	}
}

void ManagerObjectAndFile::AddObjectOnMap(GameScene& i_gameScene, ManagerComponent& i_manager)
{
	LoadObjectFromFile();
	AddObjectFromFile(i_gameScene, i_manager);
}

void ManagerObjectAndFile::LoadObjectFromFile()
{
	std::ifstream _readFromFile;
	_readFromFile.open(CNT_PATH_TO_RESOURCES + "Map/Map.xml");

	int _index = 1;
	char _value;
	std::vector<int> _vecPropertiesObject;
	std::string _intermediateString;

	while (_value = _readFromFile.get() == '<')
	{
		_vecPropertiesObject.clear();
		_intermediateString.clear();
		do
		{
			if ((int)_value >= ASCII_CODE_0 && (int)_value <= ASCII_CODE_9)
			{
				_intermediateString = _value;
				_readFromFile.get(_value);
				while (_value != ' ')
				{
					_intermediateString += _value;
					_readFromFile.get(_value);
				}
				_vecPropertiesObject.push_back(std::stoi(_intermediateString));
			}
			else
			{
				_readFromFile.get(_value);
			}
		} while (_value != '>');

		ObjectInFile _object;
		_object.typeObject = _vecPropertiesObject[0];
		_object.positionVisible = Point(_vecPropertiesObject[1], _vecPropertiesObject[2]);
		_object.positionOrigin = Point(_vecPropertiesObject[3], _vecPropertiesObject[4]);

		m_vecObject.push_back(_object);
		_readFromFile.get();
	}

	_readFromFile.close();

	// clear file from objects;
	std::ofstream _clearFile(CNT_PATH_TO_RESOURCES + "Map/Map.xml", std::ios::out | std::ios::trunc);
	_clearFile.close();
}

void ManagerObjectAndFile::WriteObjectInFile(	int i_typeObject,
												Point i_positionVisible,
												Point i_positionOrigin
											)
{
	std::ofstream	_fileForWrite;
	_fileForWrite.open(CNT_PATH_TO_RESOURCES + "/Map/Map.xml", std::ios_base::app);

	_fileForWrite << "<" << i_typeObject
		<< " position visible x = " << (int)i_positionVisible.x
		<< " position visible y = "	<< (int)i_positionVisible.y
		<< " position origin x = "	<< (int)i_positionOrigin.x
		<< " position origin y = "	<< (int)i_positionOrigin.y
		<< " >" << std::endl;

	_fileForWrite.close();
}

ManagerObjectAndFile::~ManagerObjectAndFile()
{

}