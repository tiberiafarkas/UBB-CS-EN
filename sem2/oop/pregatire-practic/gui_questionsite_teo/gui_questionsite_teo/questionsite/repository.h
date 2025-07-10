#pragma once

#include <vector>
#include "question.h"
#include "user.h" 
#include "subject.h"

class Repository  
{
private:
	std::vector<Question> questions;
	std::vector<Answer> answers;
	std::vector<User> users;
public:
	Repository();
	~Repository();
	std::vector<Question>& getQuestions();
	std::vector<Answer>& getAnswers();
	std::vector<User>& getUsers();
	void addQuestion(Question q);
	/*void addAnswer(Answer a);

	void removeQuestion(Question q);
	void removeAnswer(Answer a);

	void updateQuestion(Question q);*/
	void updateAnswer(int index, int value)
	{
		answers[index].setNrOfVotes(value); 
	}

	void readQuestionsFromFile();
	void readAnswersFromFile();
	void readUsersFromFile();

	void writeQuestionsToFile();
	void writeAnswersToFile();

};