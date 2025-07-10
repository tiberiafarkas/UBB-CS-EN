#include "DynamicArray.h"
#include "domain.h"
#include "Repository.h"

Repository::Repository(){}

Repository::~Repository(){}

/*
	Adds a subscription to the repository
	It searches for the subscription in the repository and if it doesn't exist, it adds it
	Input: s - domain
	Output: true - if the subscription was added successfully
			false - if the subscription already exists
*/

bool Repository::addSubscription(domain s)
{
	for (int i = 0; i < this->subscriptions.getSize(); i++)
	{
		if (this->subscriptions[i].getName() == s.getName() && this->subscriptions[i].getDate() == s.getDate() )
			return false;
	}

	this->subscriptions.add(s);
	return true;
}

DynamicArray<domain> Repository::getSubscriptions()
{
	return this->subscriptions;
}


