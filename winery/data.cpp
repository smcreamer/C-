#include "data.h"
#include <iostream>
#include <iomanip>
using namespace std;

const int MAX_LEN = 100;

data::data() : year(0), acres(0.0), rating(0.0),name(NULL), loc(NULL)
{

}

data::data(const char *name, const char *loc, int year, float acres, float rating) : year(0), acres(0.0), rating(0.0), name(NULL), loc(NULL)
{
	setName(name);
	setLocation(loc);
	setYear(year);
	setAcres(acres);
	setRating(rating);
}

data::data(const data& winery) :name(NULL), loc(NULL), year(0), acres(0.0), rating(0.0)
{
	setName(winery.name);
	setLocation(winery.loc);
	setYear(winery.year);
	setAcres(winery.acres);
	setRating(winery.rating);
}

const data& data::operator=(const data& winery)
{
	if (this == &winery)
		return *this;
	else
	{
		setName(winery.name);
		setLocation(winery.loc);
		setYear(winery.year);
		setAcres(winery.acres);
		setRating(winery.rating);
		return *this;
	}
}

data::~data()
{
	if (name)
		delete[] name;
	if (loc)
		delete[] loc;
}

void data::getName(char *name) const
{
	strcpy(name, this->name);
}

void data::getLoc(char *loc) const
{
	strcpy(loc, this->loc);
}

float data::getAcres() const
{
	return acres;
}

int data::getYear() const
{
	return year;
}

float data::getRating() const
{
	return rating;
}

void data::setName(const char *name)
{
	if (this->name)
		delete[] this->name;

	this->name = new char[strlen(name)+1];
	strcpy(this->name, name);
}

void data::setLocation(const char *loc)
{
	if (this->loc)
	{
		delete[] this->loc;
	}
	this->loc = new char[strlen(loc)+1];
	strcpy(this->loc, loc);
}

void data::setAcres(const float acres)
{
	this->acres = acres;
}

void data::setRating(const float rating)
{
	this->rating = rating;
}

void data::setYear(const int year)
{
	this->year = year;
}

bool operator<(const data& w1, const data& w2)
{
	char name1[MAX_LEN];
	char name2[MAX_LEN];

	w1.getName(name1);
	w2.getName(name2);

	if (strcmp(name1, name2) < 0)
		return true;
	else
		return false;
}

bool operator== (const data& w1, const data& w2)
{
	char name1[MAX_LEN];
	char name2[MAX_LEN];

	w1.getName(name1);
	w2.getName(name2);

	if (name1 == name2)
		return true;
	else
		return false;
}

ostream& operator<< (ostream& out, const data& winery)
{
	out << setw(5) << winery.name << setw(5) << winery.loc << setw(5) << winery.acres << setw(5) << winery.rating << setw(5) << winery.year;
	return out;
}