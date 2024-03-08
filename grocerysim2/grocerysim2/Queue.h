#pragma once

#include <iostream>
#include <stdlib.h>  
#include <time.h>    
#include "QueueNode.h"

class Queue
{
private:
	int currentID;
	int queueType;
	int waitTime;
	QueueNode* pHead;
	QueueNode* pTail;

	//target time(passed from constructor)
	float targetTime = 0.0f;

	//time before enqueue
	float enQTime = 0.0f;

	//time before dequeu
	float deQTime = 0.0f;

public:
	//constructor
	Queue(int type, float targetT) {
		this->targetTime = targetT;
		this->currentID = 0;
		this->queueType = type;
		this->pHead = nullptr;
		this->pTail = nullptr;
		this->waitTime = 0;

		//set initial enqueue time
		if (type == 0) {
			this->enQTime = (rand() % 5 + 1) * targetTime;
		}
		else {
			this->enQTime = (rand() % (8 - 3) + 3) * targetTime;
		}

	}

	//destructor /*TODO: delete all allocated nodes*/
	~Queue() {
		if (this->pHead) {
			delete this->pHead;
		}

	}

	/*members*/

	//get head node
	QueueNode* getHead();

	//get tail node
	QueueNode* getTail();

	//returns true if queue is empty
	bool isEmpty();

	//returns true if allocated node and enqueued it. 
	//passes current id to QueueNode constructor
	bool enqueue();

	//currently need to check if queue is empty or else 
	Data dequeue();

	//print queue members
	void printQueue();

	//check enqueu/dequeu times
	bool checkEnQTime();
	//only return true if nodes are queued***
	bool checkDecQTime();

	//decrement dequeue and enqueue times
	void decEnQTime(float decTime);
	void decDecQTime(float decTime);

	//reset enqueue time
	void resetEnq();

	//get size of queue
	int queueSize();

	//get longest wait time
	int getWait();
};
