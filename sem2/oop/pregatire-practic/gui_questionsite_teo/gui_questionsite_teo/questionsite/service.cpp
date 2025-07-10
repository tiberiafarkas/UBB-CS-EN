#include "service.h"
#include "question.h"

Service::Service(Repository& repository) : repository{ repository }
{}

std::vector<Question>& Service::getQuestions()
{
	return repository.getQuestions(); 
}

std::vector<Answer>& Service::getAnswers()
{
	return repository.getAnswers();
}

std::vector<User>& Service::getUsers()
{
	return repository.getUsers();
}

std::vector<Question> Service::getQuestionsSortedByNrOfAnswers()
{
	std::vector<Question> questions = repository.getQuestions();  
	std::vector<Answer> answers = repository.getAnswers(); 
	std::vector<int> nrOfAnswers; 

	for (auto& question : questions)
	{
		int ans = 0; 
		for (auto& answer : answers)
		{
			if (answer.getQuestionId() == question.getId())
				ans++; 
		}
		nrOfAnswers.push_back(ans);
	}

	for (int i = 0; i < questions.size() - 1; i++)
		for (int j = i + 1; j < questions.size(); j++) 
			if (nrOfAnswers[i] < nrOfAnswers[j]) 
			{
				Question aux = questions[i];  
				questions[i] = questions[j];  
				questions[j] = aux;  
				int aux2 = nrOfAnswers[i];  
				nrOfAnswers[i] = nrOfAnswers[j];  
				nrOfAnswers[j] = aux2;  
			}

	return questions;
}

void Service::addQuestion(Question q)
{
	repository.addQuestion(q); 
	notify(); 
}
