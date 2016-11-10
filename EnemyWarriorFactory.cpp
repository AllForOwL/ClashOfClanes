#include "EnemyWarriorFactory.h"
#include "ManagerComponent.h"
#include "HeroGraphicComponent.h"
#include "GameScene.h"
#include "GraphicComponent.h"
#include "ManagerArmy.h"
#include "HeroInputComponent.h"
#include "HUDLayer.h"
#include "MapLayer.h"

EnemyWarriorFactory::EnemyWarriorFactory()
{

}

EnemyWarriorFactory::EnemyWarriorFactory(Point i_positionVisible, MapLayer& i_mapLayer) : Factory(i_positionVisible, i_mapLayer, "Home/render6.png")
{
	m_stateWarrior	= StateFactoryWarrior::NOTHING;

	LoadNameForSprites();
}
EnemyWarriorFactory::EnemyWarriorFactory(EnemyWarriorFactory& i_EnemyWarriorFactory)
{

}

void EnemyWarriorFactory::LoadNameForSprites()
{
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Warrior/black_knight/attack_1.png");
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Warrior/bronze_knight/attack_1.png");
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Warrior/silver_knight/attack_1.png");
}

/*virtual*/ void EnemyWarriorFactory::Update(ManagerComponent& i_manager)
{
	
}

bool EnemyWarriorFactory::DetermineCommand()
{
	return false;
}

using STATE_FACTORY = EnemyWarriorFactory::StateFactoryWarrior;
void EnemyWarriorFactory::SetState(STATE_FACTORY& i_stateWarrior)
{
	m_stateWarrior = i_stateWarrior;
}

EnemyWarriorFactory::StateFactoryWarrior& EnemyWarriorFactory::GetStateWarrior()
{
	return m_stateWarrior;
}

EnemyWarriorFactory::~EnemyWarriorFactory()
{

}