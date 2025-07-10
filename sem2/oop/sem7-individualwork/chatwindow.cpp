#include "chatwindow.h"
#include <QVBoxLayout>
#include <QDateTime>
#include <QHBoxLayout>

ChatWindow::ChatWindow(User user, ChatSession& chatSession, QWidget* parent)
	: QWidget(parent), user(user), chatSession(chatSession) {
	// Initialize the chat window components
	chatSession.registerObserver(this);

	messageDisplay = new QTextEdit(this);
	messageInput = new QLineEdit(this);
	sendButton = new QPushButton("Send", this);
	unregisterButton = new QPushButton("Unregister", this);
	registerButton = new QPushButton("Register", this);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(messageDisplay);
	messageDisplay->setReadOnly(true); // Make the message display read-only
	layout->addWidget(messageInput);

	QHBoxLayout* buttonLayout = new QHBoxLayout();
	buttonLayout->addWidget(sendButton);
	buttonLayout->addWidget(unregisterButton);
	buttonLayout->addWidget(registerButton);

	registerButton->hide(); // Initially hide the register button

	layout->addLayout(buttonLayout);

	connect(sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);
	connect(unregisterButton, &QPushButton::clicked, this, &ChatWindow::unregister);

}

void ChatWindow::update() {
	messageDisplay->clear(); // Clear the display area
	vector<UserMessage> messages = chatSession.getMessages();

	for (const UserMessage& userMessage : messages) {
		QString time = QDateTime::fromSecsSinceEpoch(userMessage.message.getTimestamp()).toString("hh:mm:ss");
		QString line = QString::fromStdString("[" + time.toStdString() + "] " + userMessage.user.getUser() + ": " + userMessage.message.getText());
		messageDisplay->append(line);
	}
}

void ChatWindow::sendMessage() {
	QString text = messageInput->text();
	if (!text.isEmpty()) {
		Message message(text.toStdString());
		chatSession.addMessage(user, message);
		messageInput->clear(); // Clear the input field after sending
	}
}

void ChatWindow::unregister() {
	chatSession.unregisterObserver(this);
	messageDisplay->append("You have unregistered from the chat session.");

	sendButton->hide();
	unregisterButton->hide();
	messageInput->hide();
	registerButton->show(); // Show the register button to allow re-registration

	connect(registerButton, &QPushButton::clicked, this, &ChatWindow::reregister);

	//close(); // Close the chat window
}

void ChatWindow::reregister() {
	chatSession.registerObserver(this);
	messageDisplay->append("You have re-registered to the chat session.");
	sendButton->show();
	unregisterButton->show();
	messageInput->show();
	registerButton->hide();
}