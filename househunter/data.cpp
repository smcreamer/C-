#include "data.h"
#include <iostream>
#include <iomanip>
using namespace std;

const int MAX_LEN = 100;

data::data() : sqFt(0), numBed(0), numBath(0.0), address(NULL), desc(NULL)
{

}

data::data(const char *address, int sqFt, int numBed, float numBath, const char *desc) : sqFt(0), numBed(0), numBath(0.0), address(NULL), desc(NULL)
{
	setAddress(address);
	setDesc(desc);
	setSqFt(sqFt);
	setNumBed(numBed);
	setNumBath(numBath);
}

data::data(const data& house) :address(NULL), desc(NULL), sqFt(0), numBed(0), numBath(0.0)
{
	setAddress(house.address);
	setDesc(house.desc);
	setSqFt(house.sqFt);
	setNumBed(house.numBed);
	setNumBath(house.numBath);
}

const data& data::operator=(const data& house)
{
	if (this == &house)
		return *this;
	else
	{
		setAddress(house.address);
		setDesc(house.desc);
		setSqFt(house.sqFt);
		setNumBed(house.numBed);
		setNumBath(house.numBath);
		return *this;
	}
}

data::~data()
{
	if (address)
		delete[] address;
	if (desc)
		delete[] desc;
}

void data::getAddress(char *address) const
{
	strcpy(address, this->address);
}

void data::getDesc(char *desc) const
{
	strcpy(desc, this->desc);
}

int data::getNumBed() const
{
	return numBed;
}

int data::getSqFt() const
{
	return sqFt;
}

float data::getNumBath() const
{
	return numBath;
}

void data::setAddress(const char *address)
{
	if (this->address)
		delete[] this->address;

	this->address = new char[strlen(address) + 1];
	strcpy(this->address, address);
}

void data::setDesc(const char *desc)
{
	if (this->desc)
	{
		delete[] this->desc;
	}
	this->desc = new char[strlen(desc) + 1];
	strcpy(this->desc, desc);
}

void data::setNumBed(const int numBed)
{
	this->numBed = numBed;
}

void data::setNumBath(const float numBath)
{
	this->numBath = numBath;
}

void data::setSqFt(const int sqFt)
{
	this->sqFt = sqFt;
}

ostream& operator<< (ostream& out, const data& house)
{
	out << left << setw(40) << house.address << setw(5) << house.sqFt << setw(5) << house.numBed << setw(5) << house.numBath << setw(30) << house.desc << endl;
	return out;
}
