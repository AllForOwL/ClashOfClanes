#ifndef __MESSAGING_SYSTEM_H__
#define __MESSAGING_SYSTEM_H__

#include "cocos2d.h"

USING_NS_CC;

class ManagerComponent;

class MessagingSystem 
{
public:
	void AddMesssage(std::string i_message);
	
private:
	std::vector<std::string> m_vecMessages;
};

#endif