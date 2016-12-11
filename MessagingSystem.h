#ifndef __MESSAGING_SYSTEM_H__
#define __MESSAGING_SYSTEM_H__

#include "cocos2d.h"

USING_NS_CC;

class ManagerComponent;

class MessagingSystem 
{
public:

	enum StateMessage
	{
		BUILD_FACTORY_GOLD,
		BUILD_FACTORY_OIL,
		NOTHING
	};

	MessagingSystem();
	MessagingSystem(MessagingSystem& i_messageSystem);

	int GetQuentityMessage() const;

	void AddMesssage(std::string i_message);

	void Update(ManagerComponent& i_manager);

	void SetState(StateMessage i_state);
	StateMessage GetState() const;

	void VerifyGoBuildFactory();

	static std::vector<std::string> m_vecMessages;
	static int g_typeFactory;

private:
	StateMessage m_stateMessage;

};

#endif