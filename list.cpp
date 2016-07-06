#include "list.h"
#include <iomanip>
#include <fstream>
#include <cassert>
using namespace std;

list::list() :headByName(NULL), headByRating(NULL)
{

}

list::list(char *fileName) : headByName(NULL), headByRating(NULL)
{
	ifstream inStream;
	data currData;
	char name[100];
	char loc[100];
	float acres;
	float rating;
	int year;

	inStream.open(fileName);
	if (!inStream)
	{
		cerr << fileName << " is not a valid file." << endl;
		exit(1);
	}

	inStream.get(name, 100, ';');
	while (!inStream.eof())
	{
		inStream.ignore(100, ';');
		inStream.get(loc, 100, ';');
		inStream.ignore(100, ';');
		inStream >> year;
		inStream.ignore(5, ';');
		inStream >> acres;
		inStream.ignore(4, ';');
		inStream >> rating;
		inStream.ignore(100, '\n');

		currData.setName(name);
		currData.setLocation(loc);
		currData.setYear(year);
		currData.setAcres(acres);
		currData.setRating(rating);


		insert(currData);

		inStream.get(name, 100, ';');
	}
	inStream.close();
}

list::list(const list& aList)
{
	nodeType *rateOrder = new nodeType;
	nodeType * destNode = headByName;
	nodeType * srcNode = aList.headByName->nextByName;

	cout << "copy constructor called!";
	if (aList.headByName == NULL)
	{
		headByName = NULL;
		headByRating = NULL;
	}
	else
	{
		headByName = new nodeType;
		assert(headByName != NULL); 
		headByName->winery = aList.headByName->winery;

		headByRating = new nodeType;
		assert(headByRating != NULL); 
		headByRating->winery = aList.headByRating->winery;


		while (srcNode != NULL) 
		{
			destNode->nextByName = new nodeType;
			assert(destNode->nextByName != NULL); 
			destNode = destNode->nextByName;
			destNode->winery = srcNode->winery;

			srcNode = srcNode->nextByName;
		}
		destNode->nextByName = NULL;

		
		destNode = headByRating;
		srcNode = aList.headByRating->nextByRating;
		
		rateOrder = headByName;
		while (srcNode != NULL)
		{
			while (rateOrder != NULL && rateOrder->winery < srcNode->winery)
			{
				rateOrder = rateOrder->nextByName;
			}
			if (srcNode->winery == rateOrder->winery)
			{
				destNode->nextByRating = rateOrder;
				srcNode = srcNode->nextByRating;
				rateOrder = headByName;
			}
		}
		destNode->nextByRating = NULL;
	}
}

const list& list::operator= (const list& aList)
{
	nodeType * destNode = headByName;
	nodeType * srcNode = aList.headByName->nextByName;
	nodeType * curr = headByName;

	if (this == &aList)
		return *this;
	else
	{
		
		while (headByName)
		{
			curr = headByName->nextByName;
			delete headByName;
			headByName = curr;
		}

		if (!aList.headByName)
			headByName = NULL;
		else
		{
			headByName = new nodeType;
			assert(headByName != NULL);
			headByName->winery = aList.headByName->winery;

			

			while (srcNode)
			{
				destNode->nextByName = new nodeType;
				assert(destNode->nextByName);
				destNode = destNode->nextByName;
				destNode->winery = srcNode->winery;

				srcNode = srcNode->nextByName;
			}
			destNode->nextByName = NULL;
		}

		return *this;
	}
}

list::~list()
{
	nodeType * curr = headByName;

	while (headByName)
	{
		curr = headByName->nextByName;
		delete headByName;		
		headByName = curr;
	}
}

bool list::insert(const data& winery)
{
	nodeType * prev = NULL;
	nodeType * curr = headByName;
	nodeType * newNode = new nodeType;

	while (curr != NULL && curr->winery < winery)
	{
		prev = curr;
		curr = curr->nextByName;
	}

	if (curr && curr->winery == winery)
		return false;
	else
	{
		
		newNode->winery = winery;
		newNode->nextByName = NULL;
		newNode->nextByRating = NULL;
		newNode->nextByName = curr;
		if (prev == NULL)
			headByName = newNode;

		else
			prev->nextByName = newNode;

		curr = headByRating;
		prev = NULL;
		while (curr != NULL && curr->winery.getRating() > winery.getRating())
		{
			prev = curr;
			curr = curr->nextByRating;
		}
		if (curr != NULL && curr->winery.getRating() == winery.getRating())
		{
			while (curr != NULL && (curr->winery.getRating() == winery.getRating()) && curr->winery.getAcres() < winery.getAcres())
			{
				prev = curr;
				curr = curr->nextByRating;
			}
			newNode->nextByRating = curr;
			if (prev == NULL)
				headByRating = newNode;

			else
				prev->nextByRating = newNode;
			return true;
		}
		else
		{

			newNode->nextByRating = curr;
			if (prev == NULL)
				headByRating = newNode;

			else
				prev->nextByRating = newNode;
			return true;
		}
	}
}

bool list::remove(const char * key)
{
	char id[100];

	nodeType * prev = NULL;
	nodeType * prevRating = NULL;
	nodeType * curr = headByName;
	nodeType * currRating = headByRating;

	while (curr)
	{
		curr->winery.getName(id);
		if (strcmp(key, id) == 0)
		{
			if (!prev)
			{
				headByName = curr->nextByName;
			}
			else
			{
				prev->nextByName = curr->nextByName;
			}
			while (currRating && currRating != curr)
			{
				prevRating = currRating;
				currRating = currRating->nextByRating;
			}
				if (currRating == curr)
				{
					if (!prevRating)
					{
						headByRating = currRating->nextByRating;
					}
					else
					{
						prevRating->nextByRating = currRating->nextByRating;
					}
					delete curr;
					return true;
				}
			}
		else
		{
			prev = curr;
			curr = curr->nextByName;
		}

	}
	return false;
}

bool list::retrieve(char * key, data & aData)const
{
	nodeType * curr;
	char id[100];

	for (curr = headByName; curr; curr = curr->nextByName)
	{
		curr->winery.getName(id);
		if (strcmp(key, id) == 0)
		{
			aData = curr->winery;
			return true;
		}
	}
	return false;
}

void list::display(void)const
{
	nodeType * curr;

	cout << "Data in the list: " << endl << endl;
	for (curr = headByName; curr; curr = curr->nextByName)
	{
		cout << '\t' << curr->winery << endl;
	}
}

int list::getSize() const
{
	return size;
}

void list::writeOut(char * fileName)const
{
	ofstream out;
	nodeType * curr;
	char name[100];
	char loc[100];

	out.open(fileName);
	if (!out)
	{
		cerr << "fail to open " << fileName << " for output!" << endl;
		exit(1);
	}

	for (curr = headByName; curr; curr = curr->nextByName)
	{
		curr->winery.getName(name);
		curr->winery.getLoc(loc);
		curr->winery.getYear();
		curr->winery.getAcres();
		curr->winery.getRating();
		out << name << ';' << loc << ';' << curr->winery.getYear() << ';' << curr->winery.getAcres() << ';' << curr->winery.getRating() << '\n';
	}

	out.close();
}

void list::displayByName() const
{
	nodeType * curr;
	char name[100];
	char loc[100];

	cout << right << setw(35) << "Wineries Sorted By Name" << endl
		<< left << setw(20) << "Name" << setw(20) << "Location" << setw(10) << "Year" << setw(10) << "Acres" << setw(10) << "Rating" << endl
		<< setfill('-') << setw(70) << "-" << setfill(' ') << endl;
	for (curr = headByName; curr; curr = curr->nextByName)
	{
		curr->winery.getName(name);
		curr->winery.getLoc(loc);
		cout << setw(20) << name << setw(20) << loc << setw(10) << curr->winery.getYear() << setw(10) << curr->winery.getAcres() << setw(10) << curr->winery.getRating() << '\n';
	}
}

void list::displayByRating() const
{
	nodeType * curr;
	char name[100];
	char loc[100];

	cout << right << setw(35) << "Wineries Sorted By Rating" << endl
		<< left << setw(20) << "Name" << setw(20) << "Location" << setw(10) << "Year" << setw(10) << "Acres" << setw(10) << "Rating" << endl
		<< setfill('-') << setw(50) << setfill(' ') << endl;
	for (curr = headByRating; curr; curr = curr->nextByRating)
	{
		curr->winery.getName(name);
		curr->winery.getLoc(loc);
		cout << setw(20) << name << setw(20) << loc << setw(10) << curr->winery.getYear() << setw(10) << curr->winery.getAcres() << setw(10) << curr->winery.getRating() << '\n';
	}
}