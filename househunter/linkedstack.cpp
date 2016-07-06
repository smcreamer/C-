#include "linkedstack.h"
#include <fstream>
#include <cassert>
#include <iomanip>

/*********************
private:
node * top;
*********************/

stack::stack() :top(NULL)
{
}

stack::stack(const stack& aStack)
{
	if (aStack.top == NULL)
		top = NULL;
	else
	{
		top = new node;
		assert(top != NULL);
		top->item = aStack.top->item;

		node * destNode = top;				
		node * srcNode = aStack.top->next;
		while (srcNode != NULL)
		{
			destNode->next = new node;
			assert(destNode->next != NULL);
			destNode = destNode->next;
			destNode->item = srcNode->item;

			srcNode = srcNode->next;
		}
		destNode->next = NULL;
	}

}

const stack& stack::operator=(const stack& aStack)
{
	if (this == &aStack)
		return *this;
	else
	{
		node * curr = top;
		while (top)
		{
			curr = top->next;
			delete top;
			top = curr;
		}

		if (!aStack.top)
			top = NULL;
		else
		{
			top = new node;
			assert(top != NULL);
			top->item = aStack.top->item;

			node * destNode = top;
			node * srcNode = aStack.top->next;

			while (srcNode)
			{
				destNode->next = new node;
				assert(destNode->next);
				destNode = destNode->next;
				destNode->item = srcNode->item;

				srcNode = srcNode->next;
			}
			destNode->next = NULL;
		}

		return *this;
	}
}

stack::~stack()
{
	node * curr = top;
	while (top)
	{
		curr = top->next;
		delete top;
		top = curr;
	}
	top = NULL;
}

bool stack::push(const data& aData)
{
	node * newNode = new node;
	newNode->item = aData;
	newNode->next = NULL;

	newNode->next = top;
	top = newNode;

	return true;
}

bool stack::pop(data& aData)
{
	node * temp;
	if (isEmpty())
		return false;
	else
	{
		aData = top->item;
		temp = top;
		top = top->next;
		delete temp;
		return true;
	}
}

bool stack::isEmpty() const
{
	return top == NULL;
}

bool stack::peek(data& aData)const
{
	if (isEmpty())
		return false;
	else
	{
		aData = top->item;
		return true;
	}
}

void stack::display() const
{
	node * curr;

	for (curr = top; curr; curr = curr->next)
	{
		cout << curr->item << endl;
	}
}
