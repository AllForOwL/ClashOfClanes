#include "MessagingSystem.h"
#include "MapLayer.h"

USING_NS_CC;

MessagingSystem::MessagingSystem(MapLayer& i_parent)
{
	m_textMessage = Label::create(" ", "Herbana", 20);
	m_textMessage->setTextColor(Color4B::WHITE);
	i_parent.addChild(m_textMessage);
}

MessagingSystem::MessagingSystem(MessagingSystem& i_messageSystem)
{

}

void MessagingSystem::CloseMessage()
{
	m_textMessage->setVisible(false);
}

void MessagingSystem::ShowMessageInformation(Point i_positionMessage, std::string i_message)
{
	m_textMessage->setPosition(i_positionMessage);
	m_textMessage->setString(i_message);
	m_textMessage->setTextColor(Color4B::BLUE);
}

void MessagingSystem::ShowMessageWarning(Point i_positionMessage, std::string i_message)
{
	m_textMessage->setPosition(i_positionMessage);
	m_textMessage->setString(i_message);
	m_textMessage->setTextColor(Color4B::YELLOW);
}

void MessagingSystem::ShowMessageError(Point i_positionMessage, std::string i_message)
{
	m_textMessage->setPosition(i_positionMessage);
	m_textMessage->setString(i_message);
	m_textMessage->setTextColor(Color4B::RED);
}

MessagingSystem::~MessagingSystem()
{

}