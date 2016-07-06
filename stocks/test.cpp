#include "stdlib.h"

#include "data.h"
#include "hashtable.h"
#include "string.h"
#include <iostream>
using namespace std;

const int static MAX_LEN = 100;
void getData(data &stock);
float getFloat(const char * prompt);
void getString(const char * prompt, char * input);
void displayMenu();
char getCommand();
void executeCmd(char commmand, hashTable &table);

int main()
{
	char fileName[] = "data.dat";
	hashTable roster(fileName);
	char command = 'a';

	displayMenu();
	command = getCommand();
	while (command != 'q')
	{
		executeCmd(command, roster);
		displayMenu();
		command = getCommand();
	}

	roster.writeOut(fileName);
	cout << "Thank you for testing!" << endl;
	return 0;
}

void displayMenu()
{
	cout << "Welcome to the NYSE!" << endl
		<< "Menu options: " << endl
		<< "\ta> add a stock to the database" << endl
		<< "\tc> change stock information" << endl
		<< "\td> display list of stocks in the database" << endl
		<< "\te> erase a stock from the database" << endl
		<< "\tm> list number of nodes in table" << endl
		<< "\tr> retrieve a specific stock by ticker" << endl
		<< "\tq> quit program" << endl << endl; 
}

char getCommand()
{
	char cmd;
	cout << "Enter option: ";
	cin >> cmd;
	cin.ignore(100, '\n');
	return tolower(cmd);
}

void executeCmd(char command, hashTable &table)
{
	data stock;
	char ticker[6];
	float netValue;
	char valueDate[MAX_LEN];
	float ytdReturn;

	switch (command)
	{
	case 'a': getData(stock);
		table.insert(stock);
		cout << endl << "the stock has been saved in the database. " << endl;
		break;
	case 'c': getString("\nPlease enter the ticker of the stock you want to change the information for: ", ticker);
		getString("\tticker: ", ticker);
		netValue = getFloat("\tnet value: ");
		getString("\tvalue date: ", valueDate);
		ytdReturn = getFloat("\tytd return: ");
		table.modify(ticker, netValue, valueDate, ytdReturn);
		break;
	case 'e': getString("\nPlease enter the ticker of the stock you want to remove: ", ticker);
		table.remove(ticker);
		cout << endl << ticker << " has been removed from the database. " << endl;
		break;
	case 'm': table.monitor();
		break;
	case 'r': getString("\nPlease enter the ticker of the stock you want to search: ", ticker);
		table.retrieve(ticker, stock);
		cout << endl << "Information about " << ticker << ": " << endl << '\t' << stock << endl;
		break;
	case 'd': table.display();
		break;
	default: cout << "illegal command!" << endl;
		break;
	}
}

void getData(data & stock)
{
	char ticker[6];
	char name[MAX_LEN];
	float netValue;
	char valueDate[MAX_LEN];
	float ytdReturn;

	cout << "\nPlease enter information about the stock: " << endl;
	getString("\tticker: ", ticker);
	getString("\tname: ", name);
	netValue = getFloat("\tnet value: ");
	getString("\tvalue date: ", valueDate);
	ytdReturn = getFloat("\tytd return: ");

	stock.setTicker(ticker);
	stock.setName(name);
	stock.setNetValue(netValue);
	stock.setValueDate(valueDate);
	stock.setYTDReturn(ytdReturn);
}

void getString(const char * prompt, char * input)
{
	cout << prompt;
	cin.get(input, MAX_LEN, '\n');
	cin.ignore(100, '\n');
}

float getFloat(const char * prompt)
{
	float temp;
	cout << prompt;
	cin >> temp;
	while (!cin)
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Illegal input -- try again: ";
		cin >> temp;
	}
	cin.ignore(100, '\n');
	return temp;
}
