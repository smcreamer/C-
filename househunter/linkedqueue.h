#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include "data.h"
class queue
{
public:
	queue();
	queue(char * fileName);

	queue(const queue& aQueue);
	~queue();

	const queue& operator= (const queue& aQueue);

	bool enqueue(const data&);
	bool dequeue(data&);

	bool peek(data&)const;
	bool isEmpty(void)const;

	void display() const;

private:
	struct node
	{
		data item;
		node * next;
	};
	node * front;
	node * rear;
};
#endif
