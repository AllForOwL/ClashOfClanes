#ifndef __EnemyMachine_H__
#define __EnemyMachine_H__

#include "cocos2d.h"
#include "Machine.h"

USING_NS_CC;

class ManagerComponent;
class MapLayer;

class EnemyMachine : public Machine
{
public:
	EnemyMachine();
	EnemyMachine(std::string i_typeEnemyMachine, MapLayer& i_parentMapLayer);
	EnemyMachine(EnemyMachine& heroGraphiComponent);

	~EnemyMachine();

	virtual void Update(ManagerComponent& i_manager);

private:
};

#endif