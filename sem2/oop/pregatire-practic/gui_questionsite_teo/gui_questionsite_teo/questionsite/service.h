#pragma once

#include "repository.h"

class Service : public Subject
{
private:
	Repository& repository;
public:
	Service(Repository& repository);
	~Service() {};
	std::vector<Question>& getQuestions();
	std::vector<Answer>& getAnswers();
	std::vector<User>& getUsers();

	std::vector<Question> getQuestionsSortedByNrOfAnswers();

	void addQuestion(Question q);

	void updateAnswer(int index, int nrOfVotes)
	{
		repository.updateAnswer(index, nrOfVotes);
		notify(); 
	}
	
};