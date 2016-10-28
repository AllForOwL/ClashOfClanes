#ifndef __FAMILY_HOUSE_H__
#define __FAMILY_HOUSE_H__

#include "cocos2d.h"
#include "House.h"

USING_NS_CC;

class FamilyHouse :	public House
{
public:
	FamilyHouse();
	FamilyHouse(GameScene& i_parentGameScene);
	FamilyHouse(const FamilyHouse& i_familyHouse);

	~FamilyHouse();

	virtual void Update(ManagerComponent& i_manager);

private:

};

#endif