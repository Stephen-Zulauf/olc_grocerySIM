#include "Data.h"

/*Getters*/
int Data::getType() const {
	return this->QType;
}

int Data::getID() const {
	return this->customerNumber;
}

int Data::getTime() const {
	return this->serviceTime;
}

int Data::getTotal() const {
	return this->totalTime;

}

/*members*/
//generate a random service time(0 express, 1 normal)
//1 - 5 mins(e)3 - 8(n)
int Data::getServiceTime(int type) {
	if (type == 0) {
		return rand() % 5 + 1;
	}
	else {
		return rand() % (8 - 3) + 3;
	}
}