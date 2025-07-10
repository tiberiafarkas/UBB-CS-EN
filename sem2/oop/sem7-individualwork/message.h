#pragma once
#include <string>
#include <ctime>

using std::string;

class Message {
private:
	std::time_t timestamp; // Timestamp for the message
	string messageText;

public:
	Message(const string& text) : messageText(text), timestamp(std::time(nullptr)) {}
	string getText() const {
		return messageText;
	}
	std::time_t getTimestamp() const {
		return timestamp;
	}
};