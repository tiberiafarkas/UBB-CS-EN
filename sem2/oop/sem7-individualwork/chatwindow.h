#pragma once
#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include "user.h"
#include "oberserver.h"
#include "chatsession.h"

class ChatWindow : public QWidget, public Obersver {
	Q_OBJECT
public:
	ChatWindow(User user, ChatSession& chatSession, QWidget* parent = nullptr);
	void update() override;
	void sendMessage();
	void unregister();
	void reregister();

private:
	User user;
	ChatSession& chatSession;

	QTextEdit* messageDisplay; // Display area for messages
	QLineEdit* messageInput;   // Input field for new messages
	QPushButton* sendButton;   // Button to send messages
	QPushButton* unregisterButton; // Button to unregister from the chat session
	QPushButton* registerButton; // Button to register back to the chat session if unregistered
};