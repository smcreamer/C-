#ifndef LIST_H
#define LIST_H

#include "data.h"

using namespace std;

class list
{
public:
	list();
	list(char *fileName);
	list(const list& aList);
	~list();

	void wineries(const char &fileName);
	void displayByName() const;
	void displayByRating() const;

	bool insert(const data& winery);
	bool remove(const char *name);
	bool retrieve(char * name, data& winery) const;
	void display(void) const;
	int getSize() const;
	void writeOut(char *fileName)const;

const list& list::operator=(const list& aList);


private:
	struct nodeType
	{
		data winery;
		nodeType *nextByName;
		nodeType *nextByRating;
	};
	nodeType *headByName;
	nodeType *headByRating;
	int size;

};
#endif