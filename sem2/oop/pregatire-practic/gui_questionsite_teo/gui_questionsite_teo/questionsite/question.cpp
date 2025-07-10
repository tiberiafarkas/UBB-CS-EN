#include "question.h"

Question::Question()
{
	id = 0;
	userName = "";
	text = "";

}

Question::Question(int id, std::string text, std::string userName)
{
	this->id = id;
	this->text = text;
	this->userName = userName;
}

int Question::getId()
{
	return id;
}

std::string Question::getText()
{
	return text;
}

std::string Question::getUserName()
{
	return userName;
}

std::string Question::toString()
{
	return std::to_string(id) + " " + text + " " + userName;
}




Answer::Answer()
{
	questionId = 0;
	id = 0;
	text = "";
	userName = "";
	nrOfVotes = 0;
}

Answer::Answer(int id, int questionId, std::string author, std::string text, int nrOfVotes)
{
	this->id = id;
	this->questionId = questionId;
	this->text = text;
	this->userName = author;
	this->nrOfVotes = nrOfVotes;
}

int Answer::getId()
{
	return id;
}

int Answer::getQuestionId()
{
	return questionId;
}

std::string Answer::getText()
{
	return text;
}

std::string Answer::getUserName()
{
	return userName;
}

int Answer::getNrOfVotes()
{
	return nrOfVotes;
}
