#include "MessagingSystem.h"
#include "GameScene.h"
#include "constants.h"

USING_NS_CC;


void MessagingSystem::AddMesssage(std::string i_message)
{
	m_vecMessages.push_back(i_message);
}