#include "tests.h"
#include <assert.h>
#include "repository.h"

void testAll()
{
	Repository repo;

	repo.getIdeas().clear();

	repo.addIdea(Idea{ "wow", "proposed", "me", 1 }); 

	assert(repo.getIdeas()[0].getDescription() == "wow"); 

	repo.getIdeas()[0].setStatus("accepted");

	assert(repo.getIdeas()[0].getStatus() == "accepted");  
}
