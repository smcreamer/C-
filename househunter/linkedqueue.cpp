#include "linkedqueue.h"
#include <fstream>
#include <cassert>

/*********************
private:
node * front;
node * rear;
*********************/

queue::queue() :front(NULL), rear(NULL)
{
}

queue::queue(char * fileName) : front(NULL), rear(NULL)
{
	ifstream inStream;
	data currData;
	char address[100];
	int sqFt;
	int numBed;
	float numBath;
	char desc[100];
	
	inStream.open(fileName);
	if (!inStream)
	{
		cerr << "fail to open " << fileName << " for input!" << endl;
		exit(1);
	}

	inStream.get(address, 100, ';');
	while (!inStream.eof())
	{
		inStream.ignore(100, ';');
		inStream >> sqFt;
		inStream.ignore(5, ';');
		inStream >> numBed;
		inStream.ignore(1, ';');
		inStream >> numBath;
		inStream.ignore(3, ';');
		inStream.get(desc, 100, '\n');
		inStream.ignore(100, '\n');

		currData.setAddress(address);
		currData.setDesc(desc);
		currData.setNumBed(numBed);
		currData.setNumBath(numBath);
		currData.setSqFt(sqFt);

		enqueue(currData);

		inStream.get(address, 100, ';');
	}
	inStream.close();
}
queue::queue(const queue& aQueue) :front(NULL), rear(NULL)
{
	if (aQueue.front == NULL)
	{
		front = rear = NULL;
	}
	else
	{
		front = new node;
		assert(front != NULL); 
		front->item = aQueue.front->item;

		node * destNode = front;			
		node * srcNode = aQueue.front->next; 
		while (srcNode != NULL)
		{
			destNode->next = new node;
			assert(destNode->next != NULL); 
			destNode = destNode->next;
			destNode->item = srcNode->item;

			srcNode = srcNode->next;
		}
		destNode->next = NULL;

		rear = destNode;
	}
}
const queue& queue::operator= (const queue& aQueue)
{
	if (this == &aQueue)
		return *this;
	else
	{
		node * curr = front;
		while (front)
		{
			curr = front->next;
			delete front;
			front = curr;
		}

		if (aQueue.front == NULL)
		{
			front = rear = NULL;
		}
		else
		{
			//copy first node
			front = new node;
			assert(front != NULL);
			front->item = aQueue.front->item;

			node * destNode = front;			
			node * srcNode = aQueue.front->next;
			while (srcNode != NULL) 
			{
				destNode->next = new node;
				assert(destNode->next != NULL); 
				destNode = destNode->next;
				destNode->item = srcNode->item;

				srcNode = srcNode->next;
			}
			destNode->next = NULL;

			rear = destNode;
		}
		return *this;
	}
}

queue::~queue()
{
	node * curr = front;
	while (front)
	{
		curr = front->next;
		delete front;
		front = curr;
	}
	front = rear = NULL;
}

bool queue::enqueue(const data& aData)
{
	node * newNode = new node;
	assert(newNode);
	newNode->item = aData;
	newNode->next = NULL;

	if (rear == NULL)
		front = rear = newNode;
	else
	{
		rear->next = newNode;
		rear = newNode;		
	}

	return true;
}

bool queue::dequeue(data& aData)
{
	if (isEmpty())
		return false;
	else
	{
		node * temp = front;
		if (front == rear)
			front = rear = NULL;
		else
			front = front->next;

		temp->next = NULL;
		aData = temp->item;
		delete temp;
		return true;
	}
}

bool queue::isEmpty() const
{
	return front == NULL;
}

bool queue::peek(data& aData)const
{
	if (isEmpty())
		return false;
	else
	{
		aData = front->item;
		return true;
	}
}

void queue::display() const
{
	node * curr;

	for (curr = front; curr; curr = curr->next)
	{
		cout << curr->item << endl;
	}
}
