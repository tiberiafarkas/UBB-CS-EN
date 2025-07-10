#include "repository.h"
#include <fstream>
#include <sstream>

Repository::Repository()
{
	readAnswersFromFile(); 
	readQuestionsFromFile(); 
	readUsersFromFile(); 
}

Repository::~Repository()
{
}

std::vector<Question>& Repository::getQuestions()
{
	return questions;
}

std::vector<Answer>& Repository::getAnswers()
{
	return answers;
}

std::vector<User>& Repository::getUsers()
{
	return users;
}

void Repository::addQuestion(Question q)
{
	questions.push_back(q); 
}

void Repository::readQuestionsFromFile()
{
	std::ifstream fin("q.txt"); 
	std::string line; 
	while (std::getline(fin, line))
	{
		std::stringstream ss(line); 
		std::string text, name;
		int id;
		ss >> id >> text >> name; 
		Question q{ id, text, name}; 
		questions.push_back(q); 
	}
	fin.close(); 
}

void Repository::readAnswersFromFile()
{
	std::ifstream fin("a.txt");
	std::string line; 
	while (std::getline(fin, line)) 
	{
		std::stringstream ss(line); 
		std::string answer, name; 
		int id, quesionID, nrOfVotes; 
		ss >> id >> quesionID >> name >> answer >> nrOfVotes;
		Answer a{ id, quesionID, name, answer, nrOfVotes}; 
		answers.push_back(a); 
	}
	fin.close();
}

void Repository::readUsersFromFile()
{
	std::ifstream fin("user.txt"); 
	std::string line;  
	while (std::getline(fin, line)) 
	{
		std::stringstream ss(line); 
		std::string name; 
		ss >> name;  
		User u{ name };  
		users.push_back(u);  
	}
	fin.close(); 
}

void Repository::writeQuestionsToFile()
{
	std::ofstream file("q.txt");
	for (int i = 0; i < questions.size(); i++)
	{
		file << questions[i].getId() << " " << questions[i].getText() << " " << questions[i].getUserName();
		if (i < questions.size() - 1)
			file << "\n";
	}
	file.close();
}

void Repository::writeAnswersToFile()
{
	std::ofstream file("a.txt");
	for (int i = 0; i < answers.size(); i++)
	{
		file << answers[i].getId() << " " << answers[i].getQuestionId() << " " << answers[i].getText() << " " << answers[i].getUserName() << " " << answers[i].getNrOfVotes();
		if (i < answers.size() - 1)
			file << "\n";
	}
	file.close();
}
