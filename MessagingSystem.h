#ifndef __MESSAGING_SYSTEM_H__
#define __MESSAGING_SYSTEM_H__

#include "cocos2d.h"

USING_NS_CC;

class ManagerComponent;
class MapLayer;

class MessagingSystem 
{
public:
	MessagingSystem(MapLayer& i_parent);
	MessagingSystem(MessagingSystem& i_messageSystem);
	~MessagingSystem();

	void ShowMessageInformation(Point i_positionMessage, std::string i_message);
	void ShowMessageWarning(Point i_positionMessage, std::string i_messge);
	void ShowMessageError(Point i_positionMessage, std::string i_message);

	void CloseMessage();

private:
	Label*	m_textMessage;
};

#endif