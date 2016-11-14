#ifndef __HERO_MACHINE_H__
#define __HERO_MACHINE_H__

#include "cocos2d.h"
#include "Machine.h"

USING_NS_CC;

class ManagerComponent;
class MapLayer;

class HeroMachine : public Machine
{
public:
	HeroMachine();
	HeroMachine(std::string i_typeHeroMachine, MapLayer& i_parentMapLayer);
	HeroMachine(HeroMachine& i_heroMachine);

	~HeroMachine();

	virtual void Update(ManagerComponent& i_manager);

private:


};

#endif