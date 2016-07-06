#include "hashtable.h"
#include <iostream>
#include <fstream>
#include "string.h"
#include "stdlib.h"

using namespace std;

void hashTable::initializeTable()
{
	table = new node*[capacity];

	int i;
	for (i = 0; i<capacity; i++)
		table[i] = NULL;
}

hashTable::hashTable() : capacity(DEFAULT_CAPACITY), size(0)
{
	initializeTable();
}

hashTable::hashTable(char * fileName) : capacity(DEFAULT_CAPACITY), size(0)
{
	ifstream in;
	data currData;
	char ticker[6];
	char name[100];
	float netValue;
	char valueDate[50];
	float ytdReturn;

	initializeTable();

	in.open(fileName);
	if (!in)
	{
		cerr << "fail to open " << fileName << " for input!" << endl;
		exit(1);
	}

	in.get(ticker, 6, ';');
	while (!in.eof())
	{
		in.ignore(100, ';');
		in.get(name, 100, ';');
		in.ignore(100, ';');
		in >> netValue;
		in.ignore(100, ';');
		in.get(valueDate, 100, ';');
		in.ignore(100, ';');
		in >> ytdReturn;
		in.ignore(100, '\n');

		currData.setTicker(ticker);
		currData.setName(name);
		currData.setNetValue(netValue);
		currData.setValueDate(valueDate);
		currData.setYTDReturn(ytdReturn);

		insert(currData);

		in.get(ticker, 100, ';');
	}
	in.close();
}

hashTable::hashTable(const hashTable& aTable) :capacity(aTable.capacity), size(aTable.size)
{
	table = new node*[capacity];

	int i;
	for (i = 0; i<capacity; i++)
	{
		if (aTable.table[i] == NULL)
			table[i] = NULL;
		else
		{
			table[i] = new node(aTable.table[i]->item);

			node * srcNode = aTable.table[i]->next;
			node * destNode = table[i];
			while (srcNode)
			{
				destNode->next = new node(srcNode->item);
				destNode = destNode->next;
				srcNode = srcNode->next;
			}
			destNode->next = NULL;
		}
	}
}

const hashTable& hashTable::operator= (const hashTable& aTable)
{
	if (this == &aTable)
		return *this;
	else
	{
		destroyTable();

		table = new node*[capacity];
		capacity = aTable.capacity;
		size = aTable.size;

		int i;
		for (i = 0; i<capacity; i++)
		{
			if (aTable.table[i] == NULL)
				table[i] = NULL;
			else
			{
				table[i] = new node(aTable.table[i]->item);

				node * srcNode = aTable.table[i]->next;
				node * destNode = table[i];
				while (srcNode)
				{
					destNode->next = new node(srcNode->item);
					destNode = destNode->next;
					srcNode = srcNode->next;
				}
				destNode->next = NULL;
			}
		}
		return *this;
	}
}

void hashTable::destroyTable()
{
	int i;
	for (i = 0; i<capacity; i++)
	{
		node * head = table[i];
		node * curr;
		while (head)
		{
			curr = head->next;
			head->next = NULL;
			delete head;
			head = curr;
		}
	}

	delete[] table;
}
hashTable::~hashTable()
{
	destroyTable();
}

void hashTable::insert(const data& aData)
{
	char ticker[100];
	aData.getTicker(ticker);
	int index = calculateIndex(ticker);

	node * newNode = new node(aData);

	newNode->next = table[index];
	table[index] = newNode;
	size++;
}

bool hashTable::remove(char * ticker)
{
	int index = calculateIndex(ticker);

	node * curr = table[index];
	node * prev = NULL;
	char id[100];
	while (curr)
	{
		curr->item.getTicker(id);
		if (strcmp(ticker, id) == 0)
		{
			if (!prev)
				table[index] = curr->next;
			else
				prev->next = curr->next;

			curr->next = NULL;
			delete curr;
			size--;
			return true;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return false;
}

bool hashTable::modify(char * ticker, float newAssetValue, char * newDate, float newYtdReturn)
{
	int index = calculateIndex(ticker);

	node * curr = table[index];
	char id[100];
	while (curr)
	{
		curr->item.getTicker(id);
		if (strcmp(ticker, id) == 0)
		{
			curr->item.setNetValue(newAssetValue);
			curr->item.setValueDate(newDate);
			curr->item.setYTDReturn(newYtdReturn);
			return true;
		}
		else
			curr = curr->next;
	}

	return false;
}

bool hashTable::retrieve(char * ticker, data & aData)const
{
	int index = calculateIndex(ticker);

	node * curr = table[index];
	char id[100];
	while (curr)
	{
		curr->item.getTicker(id);
		if (strcmp(ticker, id) == 0)
		{
			aData = curr->item;
			return true;
		}
		else
			curr = curr->next;
	}

	return false;
}

void hashTable::display(void)const
{
	int i;
	node * curr;

	for (i = 0; i<capacity; i++)
	{
		for (curr = table[i]; curr; curr = curr->next)
			cout << '\t' << curr->item << endl;
	}
}

void hashTable::monitor(void) const
{
	int i = 0, size = 0;
	node * curr;

	for (i = 0; i<capacity; i++)
	{
		size = 0;
		for (curr = table[i]; curr; curr = curr->next)
		{
				size++;
		}
		cout << "chain " << i;
		switch (size)
		{
		case 0: cout << " has no nodes. " << endl;
			break;
		case 1: cout << " is " << size << " node in length. " << endl;
			break;
		default: cout << " is " << size << " nodes in length. " << endl;
			break;
		}
	}
	cout << endl;
}

void hashTable::writeOut(char * fileName)
{
	ofstream out;

	out.open(fileName);
	if (!out)
	{
		cerr << "fail to open " << fileName << " for output!" << endl;
		exit(1);
	}

	int i;
	char ticker[6];
	char name[100];
	char valueDate[50];
	node * curr;
	for (i = 0; i<capacity; i++)
	{
		for (curr = table[i]; curr; curr = curr->next)
		{
			curr->item.getName(name);
			curr->item.getTicker(ticker);
			curr->item.getValueDate(valueDate);
			out << ticker << ";" << name << "; " << curr->item.getNetValue() << "; " << valueDate << ";" << curr->item.getYTDReturn() << "\n";
		}
	}
	out.close();
}

int hashTable::calculateIndex(char * ticker)const
{
	char * c = ticker;
	int total = 0;
	while (*c)
	{
		total += *c;
		c++;
	}

	return total%capacity;
}