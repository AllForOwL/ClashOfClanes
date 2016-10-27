#include "WarriorFactory.h"
#include "GameScene.h"

WarriorFactory::WarriorFactory()
{

}

WarriorFactory::WarriorFactory(GameScene& i_parentGameScene)
{
	this->setParent(&i_parentGameScene);
}

WarriorFactory::WarriorFactory(const WarriorFactory& i_warriorFactory)
{

}

/*virtual*/ void WarriorFactory::Update(GameScene& i_gameScene)
{

}

WarriorFactory::~WarriorFactory()
{

}
