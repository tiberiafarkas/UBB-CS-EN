#pragma once
#include <vector>
#include "user.h"
#include "message.h"
#include "subject.h"
#include "usermessage.h"

using std::vector;

class ChatSession : public Subject {
private:
	vector<UserMessage> messages;
public:
	void addMessage(User u, Message m);
	vector<UserMessage> getMessages();
};
