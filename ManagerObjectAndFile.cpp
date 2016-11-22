#include "ManagerObjectAndFile.h"
#include "GraphicComponent.h"
#include "constants.h"
#include <fstream>


ManagerObjectAndFile::ManagerObjectAndFile()
{

}

ManagerObjectAndFile::ManagerObjectAndFile(ManagerObjectAndFile& i_ManagerObjectAndFile)
{

}

void ManagerObjectAndFile::ResetCurrentPosition(GraphicComponent& i_component, Point i_visible, Point i_origin)
{
	i_component.ResetPositionObject(i_visible, i_origin);
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
			if ((int)_value >= 48 && (int)_value <= 57)
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
		_object.positionVisibleWithOrigin = Point(_vecPropertiesObject[5], _vecPropertiesObject[6]);

		m_vecObject.push_back(_object);
		_readFromFile.get();
	}

	_readFromFile.close();

	std::ofstream _clearFile(CNT_PATH_TO_RESOURCES + "Map/Map.xml", std::ios::out | std::ios::trunc);
	_clearFile.close();
}

void ManagerObjectAndFile::WriteObjectInFile(	int i_typeObject,
												Point i_positionVisible,
												Point i_positionOrigin,
												Point i_positionVisibleWithOrigin
											)
{
	std::ofstream	_fileForWrite;
	_fileForWrite.open(CNT_PATH_TO_RESOURCES + "/Map/Map.xml", std::ios_base::app);

	_fileForWrite << "<" << i_typeObject
		<< " position visible x = " << (int)i_positionVisible.x
		<< " position visible y = " << (int)i_positionVisible.y
		<< " position origin x = " << (int)i_positionOrigin.x
		<< " position origin y = " << (int)i_positionOrigin.y
		<< " position visiblewithorigin x = " << (int)i_positionVisibleWithOrigin.x
		<< " position visiblewithorigin y = " << (int)i_positionVisibleWithOrigin.y
		<< " >" << std::endl;

	_fileForWrite.close();
}

ManagerObjectAndFile::~ManagerObjectAndFile()
{

}