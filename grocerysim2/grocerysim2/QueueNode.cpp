#include "QueueNode.h"

/*Setters*/

//set pNext
bool QueueNode::setNext() {
	this->pNext = new (std::nothrow) QueueNode(*this);
	if (this->pNext) {
		return true;
	}
	else {
		return false;
	}

}

/*getters*/
int QueueNode::getType() const {
	return this->QType;
}

const Data& QueueNode::getData() const {
	return *this->pData;
}

QueueNode* QueueNode::getNext() const {
	return this->pNext;
}

olc::Pixel QueueNode::getColor() {
	return this->color;
}

/*members*/
void QueueNode::printData() {
	cout << "type: " << this->pData->getType() << endl;
	cout << "ID: " << this->pData->getID() << endl;
	cout << "Service Time: " << this->pData->getTime() << endl;
	cout << "Total Time: " << this->pData->getTotal() << endl;
	cout << "------------------------" << endl;
}