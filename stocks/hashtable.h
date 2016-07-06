#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "data.h"

class hashTable
{
public:
	hashTable();
	hashTable(char * fileName);
	hashTable(const hashTable& aTable);
	~hashTable();

	const hashTable& operator= (const hashTable& aTable);

	void insert(const data& aData);
	bool remove(char * ticker);
	bool retrieve(char * ticker, data& aData)const;
	bool modify(char *ticker, float newNetValue, char * newValueDate, float newYtdReturn);
	void display(void)const;
	void monitor(void)const;
	void writeOut(char * fileName);
	

private:
	struct node
	{
		data item;
		node * next;
		node(const data& aData)
		{
			item = aData;
			next = NULL;
		}
	};

	node ** table;
	int capacity;
	int size;
	const static int DEFAULT_CAPACITY = 11;

	void destroyTable();
	void initializeTable();
	int calculateIndex(char * ticker)const;
};
#endif