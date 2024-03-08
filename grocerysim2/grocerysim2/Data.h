#pragma once

#include <stdlib.h> 

class Data {
private:
	int QType;
	int customerNumber; // Unique identifier; starts at 1; after 24 hours should be reset to 1
	int serviceTime; // Random time; varies between express and normal lanes; units in minutes //1-5 mins(e)3-8(n)
	int totalTime; // totalTime = serviceTime + sum of serviceTimes of customers in line before this customer; 
	//units in minutes
   //This memory needs to be allocated on the heap!
public:

	/*Contructors*/
	//init
	Data(int type) {
		this->QType = type;
		this->customerNumber = 1;
		this->serviceTime = this->getServiceTime(type);
		this->totalTime = this->serviceTime;
	}
	//copy
	Data(const Data& copy) {
		this->QType = copy.getType();
		this->customerNumber = copy.getID() + 1;
		this->serviceTime = this->getServiceTime(this->QType);
		this->totalTime = this->serviceTime + copy.getTotal();
	}

	/*setters*/

	/*getters*/
	int getType() const;

	int getID() const;

	int getTime() const;

	int getTotal() const;

	/*members*/
	int getServiceTime(int type);

};