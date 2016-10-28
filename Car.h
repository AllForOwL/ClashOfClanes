#ifndef __Car_H__
#define __Car_H__

#include "cocos2d.h"
#include "Warrior.h"

USING_NS_CC;

class ManagerComponent;
class GameScene;

class Car : public Warrior
{
public:
	Car();
	Car(GameScene& i_parentGameScene);
	Car(Car& i_car);

	~Car();

	virtual void Update(ManagerComponent& i_manager);

private:

};

#endif