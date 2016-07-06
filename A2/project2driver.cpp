#include <iostream>
using namespace std;
#include "data.h"
#include "linkedstack.h"
#include "linkedqueue.h"

int main()
{
	char fileName[] = "data.dat";
	queue housesOnList(fileName);
	data house;
	stack houseInterested;
	char response;

	cout << "\nthe houses we will visit today:" << endl << endl;
	housesOnList.display ();
	while(housesOnList.dequeue (house))
	{
		cout << "\nnext house to be visited:" << endl << house << endl;
		cout << "\nWould you like to revisit this house on our way back? (y, n): ";
		cin >> response;
		cin.ignore(100, '\n');
		
		if(response == 'y' || response == 'Y')
		{
			cout << "\nthe house is saved for revisiting" << endl;
			houseInterested.push (house);
		}
	}

	cout << "\nWe have finished the first round of screening" << endl << endl;
	cout << "\nOn the way back to the office: " << endl << endl;

	while(houseInterested.pop (house))
	{
		cout << "\nnext house to be revisited: " << endl << house << endl;
	}

	cout << "\nWe've finished the second round. ready to make an offer? (y, n):";
	cin >> response;
	cin.ignore (100, '\n');
	cout << "\nlet's talk about that in my office. " << endl << endl;


	return 0;
}