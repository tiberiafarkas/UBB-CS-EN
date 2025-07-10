#pragma once

#include <string>

class Question
{
private:
	int id;
	std::string text;
	std::string userName;
public:
	Question();
	Question(int id, std::string text, std::string userName);
	int getId();
	std::string getText();
	std::string getUserName();

	std::string toString(); 
};

class Answer
{
private:
	int id;
	int questionId;
	std::string text;
	std::string userName;
	int nrOfVotes;
public:
	Answer();
	Answer(int id, int questionId, std::string author, std::string text, int nrOfVotes);
	int getId();
	int getQuestionId();
	std::string getText();
	std::string getUserName();
	int getNrOfVotes();

	void setNrOfVotes(int x) 
	{
		this->nrOfVotes = x; 
	}

	std::string toString()
	{
		return std::to_string(id) + " " + std::to_string(questionId) + " " + text + " " + userName + " " + std::to_string(nrOfVotes);
	}
};