#ifndef __MANAGER_OBJECT_AND_FILE_H__
#define __MANAGER_OBJECT_AND_FILE_H__

#include "cocos2d.h"

USING_NS_CC;

class GraphicComponent;
class Factory;
class GameScene;
class ManagerComponent;

class ManagerObjectAndFile
{
public:
	struct ObjectInFile
	{
		int		typeObject;
		Point	positionVisible;
		Point	positionOrigin;

		ObjectInFile() : typeObject(0), 
						 positionVisible(Point::ZERO),
						 positionOrigin(Point::ZERO)
		{

		}
	};


	ManagerObjectAndFile();
	ManagerObjectAndFile(ManagerObjectAndFile& i_ManagerObjectAndFile);

	void AddObjectFromFile(GameScene& i_gameScene, ManagerComponent& i_manager);
	void LoadObjectFromFile();

	void AddObjectOnMap(GameScene& i_gameScene, ManagerComponent& i_manager);

	void WriteObjectInFile(	int i_typeObject, 
							Point i_positionVisible,
							Point i_positionOrigin
							);

	~ManagerObjectAndFile();

private:
	std::vector<ObjectInFile>		m_vecObject;
};

#endif