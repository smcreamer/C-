#include <stdlib.h>
#include <crtdbg.h>


#include "list.h"
#include <iostream>
using namespace std;

void displayMenu();
char getCommand();
void executeCmd(char command, list& aList);

void getWinery(data & winery);
int getInt(char * prompt);
float getFloat(char * prompt);
void getString(char * prompt, char * input);

void display(const list & aList);

const int MAX_LEN = 100;

int main()
{
	//use memory leak detection tool in Visual Studio .Net. 
	//comment it out if you are not using Visual Studio .Net
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	char command = 'a';
	char fileName[] = "data.dat";
	list wineries(fileName);

	displayMenu();
	command = getCommand();
	while(command != 'q')
	{
 		executeCmd(command, wineries);
		displayMenu();
		command = getCommand();
	}
	
	wineries.writeOut (fileName);
	cout << "\nThank you for using CWMS!" << endl << endl;
	return 0;
}

void displayMenu()
{
	cout << "\nImplemented by: Li Liang" << endl;
	cout << "\nWelcome to CS Winery Management System! "<< endl;
	cout << "\ta> add a winery" << endl
		 << "\tr> remove a winery" << endl
		 << "\ts> search for a winery" << endl
		 << "\tl> list all the wineries" << endl 
		 << "\tq> quit the application" << endl << endl;
}

char getCommand()
{
	char cmd;
	cout << "Please enter your choice (a, r, s, l or q):";
	cin >> cmd;
	cin.ignore(100, '\n');
	return tolower(cmd);
}

void executeCmd(char command, list & aList)
{
	data winery;
	char key[MAX_LEN];

	switch(command)
	{
	case 'a': getWinery(winery);
			  aList.insert (winery);
			  cout << endl << "the winery has been saved in the database. " << endl;
		break;
	case 'r': getString("\nPlease enter the name of the winery you want to remove: ", key);
		      aList.remove(key);
			  cout << endl << key << " has been removed from the database. " << endl;
		break;
	case 's': getString("\nPlease enter the name of the winery you want to search: ", key);
			  aList.retrieve (key, winery);
			  cout << endl << "Information about " << key << ": " << endl << '\t' << winery << endl;
		break;
	case 'l': display(aList);
		break;
	default: cout << "illegal command!" << endl;
		break;
	}
}

void display(const list & aList)
{
	char choice;

	cout << "\n\tn: list ordered by name" << endl
		<< "\tr: list ordered by rating" << endl << endl;

	choice = getCommand();
	switch (choice)
	{
	case 'n': aList.displayByName ();
		break;
	case 'r': aList.displayByRating ();
		break;
	default:
		cout << "illegal command!" << endl;
		break;
	}
}

void getWinery(data & winery)
{
	 char name[MAX_LEN];
	 char location[MAX_LEN];
	 int year;
	 float acres;
	 float rating;

	 cout << "\nPlease enter information about the winery: " << endl;
	 getString("\tname: ", name);
	 getString("\tlocation: ", location);
	 year = getInt("\tyear: ");
	 acres = getFloat("\tacres: ");
	 rating = getFloat("\trating: ");

	 winery.setName(name);
	 winery.setAcres (acres);
	 winery.setLocation (location);
	 winery.setRating (rating);
	 winery.setYear (year);
}
int getInt(char * prompt)
{
	int temp;
	cout << prompt;
	cin >> temp;
	while(!cin)
	{
		cin.clear ();
		cin.ignore(100, '\n');
		cout << "Illegal input -- try again: ";
		cin >> temp;
	}
	cin.ignore(100, '\n');
	return temp;
}
float getFloat(char * prompt)
{
	float temp;
	cout << prompt;
	cin >> temp;
	while(!cin)
	{
		cin.clear ();
		cin.ignore(100, '\n');
		cout << "Illegal input -- try again: ";
		cin >> temp;
	}
	cin.ignore(100, '\n');
	return temp;
}
void getString(char * prompt, char * input)
{
	cout << prompt;
	cin.get(input, MAX_LEN, '\n');
	cin.ignore (100, '\n');
}

