#include "chatsession.h"

void ChatSession::addMessage(User u, Message m) {
	UserMessage userMessage(u, m);
	messages.push_back(userMessage);
	notifyObservers();
}

vector<UserMessage> ChatSession::getMessages() {
	return messages;
}

