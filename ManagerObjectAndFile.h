#ifndef __MANAGER_OBJECT_AND_FILE_H__
#define __MANAGER_OBJECT_AND_FILE_H__

#include "cocos2d.h"

USING_NS_CC;

class GraphicComponent;
class Factory;

class ManagerObjectAndFile
{
public:
	struct ObjectInFile
	{
		int		typeObject;
		Point	positionVisible;
		Point	positionOrigin;
	};


	ManagerObjectAndFile();
	ManagerObjectAndFile(ManagerObjectAndFile& i_ManagerObjectAndFile);

	void ResetCurrentPosition(GraphicComponent& i_component, Point i_visible, Point i_origin);

	void LoadObjectFromFile();
	void WriteObjectInFile(	int i_typeObject, 
							Point i_positionVisible,
							Point i_positionOrigin
							);

	std::vector<ObjectInFile>& GetVectorObject();

	~ManagerObjectAndFile();

private:
	std::vector<ObjectInFile>		m_vecObject;

};

#endif