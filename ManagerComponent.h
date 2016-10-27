#ifndef __MANAGER_COMPONENT_H__
#define __MANAGER_COMPONENT_H__

#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class ManagerComponent
{
public:
	ManagerComponent();
	~ManagerComponent();

	virtual void Update(GameScene& scene);

private:

};

#endif