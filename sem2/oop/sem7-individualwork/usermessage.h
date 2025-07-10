#pragma once
#include "user.h"
#include "message.h"

class UserMessage {
public:
	User user;
	Message message;
	UserMessage(User u, Message m) : user(u), message(m) {}
};
