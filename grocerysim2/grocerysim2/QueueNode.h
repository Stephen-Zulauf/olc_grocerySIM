#pragma once

#include <iostream>
#include <stdlib.h> 
#include "Data.h"
#include "olcPixelGameEngine.h"

using std::cout;
using std::endl;

class QueueNode {
private:
	int QType = 0; //queue type
	Data* pData = nullptr; // The memory for Data will need to be allocated on the heap as well!
	QueueNode* pNext = nullptr;
	olc::Pixel color;


public:
	/*constructor*/
	//Allocates heap for data. (check for null to verify)
	QueueNode(int type) {
		this->QType = type;
		this->pData = new (std::nothrow) Data(type);
		this->pNext = nullptr;

		//set rand color for drawing
		color.r = rand() % 256;
		color.g = rand() % 256;
		color.b = rand() % 256;
	}

	/*copy*/
	//pData will be null if allocation error
	QueueNode(const QueueNode& copy) {
		this->QType = copy.getType();
		this->pData = new (std::nothrow) Data(copy.getData());
		this->pNext = nullptr;

		//set rand color for drawing
		color.r = rand() % 256;
		color.g = rand() % 256;
		color.b = rand() % 256;
	}

	/*destructor*/
	//check if data was allocated and delete
	~QueueNode() {
		if (this->pData) {
			delete this->pData;
		}

	}
	/*Setters*/

	//set pNext
	//this function creates new node and sets it to next!
	//check for proper allocation!
	bool setNext();

	/*getters*/
	int getType() const;
	const Data& getData() const;
	QueueNode* getNext() const;
	olc::Pixel getColor();

	/*members*/
	void printData();

};
