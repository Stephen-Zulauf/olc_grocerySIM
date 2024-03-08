#include "Queue.h"

/*members*/

//get head node
QueueNode* Queue::getHead() {
	return this->pHead;
}

//get tail node
QueueNode* Queue::getTail() {
	return this->pTail;
}

bool Queue::isEmpty() {
	if (this->pHead == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

bool Queue::enqueue() {
	//If empty set head and tail to new node
	if (this->isEmpty() == true) {
		this->pHead = new (std::nothrow) QueueNode(this->queueType);
		if (pHead) {
			this->pTail = this->pHead;
			//set dequeue time
			this->deQTime = (this->pHead->getData().getTime()) * targetTime;
			//set wait time
			this->waitTime = this->pHead->getData().getTime();
			return true;
			
		}
	}
	else {
		//set current tail next to new node then set tail to new node
		this->pTail->setNext();
		this->pTail = this->pTail->getNext();

		if (pTail) {
			//set wait time
			this->waitTime = this->pTail->getData().getTotal();
			return true;
		}
		else {
			return false;
		}

	}
}

Data Queue::dequeue() {
	QueueNode* temp = this->pHead;
	Data tData = temp->getData();
	this->pHead = pHead->getNext();
	delete temp;

	//set dequeue and wait time
	if (this->isEmpty() == false) {
		this->deQTime = (this->pHead->getData().getTime()) * targetTime;
		//set wait time
		this->waitTime = this->pTail->getData().getTotal();
	}
	else {
		//set wait time
		this->waitTime = 0;
	}

	return tData;

}

void Queue::printQueue() {
	QueueNode* temp = this->pHead;

	while (temp != nullptr) {
		temp->printData();
		temp = temp->getNext();
	}
}

//check enqueu/dequeu times
bool Queue::checkEnQTime() {
	if (this->enQTime <= 0) {
		return true;
	}
	else {
		return false;
	}
}
bool Queue::checkDecQTime() {
	if (this->deQTime <= 0 && this->isEmpty() == false) {
		return true;
	}
	else {
		return false;
	}
}

//decrement times
void Queue::decEnQTime(float decTime) {
	this->enQTime -= decTime;
}

void Queue::decDecQTime(float decTime) {
	this->deQTime -= decTime;
}

//reset enqueue time
void Queue::resetEnq() {
	if (this->queueType == 0) {
		this->enQTime = (rand() % 5 + 1) * targetTime;
	}
	else {
		this->enQTime = (rand() % (8 - 3) + 3) * targetTime;
	}
}

//get size of queue
int Queue::queueSize() {
	int i = 0;
	QueueNode* temp = this->pHead;

	while (temp != nullptr) {
		i++;
		temp = temp->getNext();
	}

	return i;
}

//get longest wait time
int Queue::getWait() {
	return this->waitTime;
}