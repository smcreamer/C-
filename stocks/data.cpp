#include "data.h"
#include "string.h"
#include "stdlib.h"
#include <iostream>
#include <iomanip>
using namespace std;

data::data() :ticker(NULL), name(NULL), netValue(0), valueDate(NULL), 
ytdReturn(0)
{
	
}

data::data(const char * ticker, const char * name, const float netValue, const char * valueDate, const float ytdReturn) : ticker(NULL), name(NULL), netValue(0), valueDate(NULL), ytdReturn(0.0)
{
	setTicker(ticker);
	setName(name);
	setNetValue(netValue);
	setValueDate(valueDate);
	setYTDReturn(ytdReturn);
}

data::data(const data& stock) :ticker(NULL), name(NULL), netValue(0), valueDate(NULL), ytdReturn(0.0)
{
	setTicker(stock.ticker);
	setName(stock.name);
	setNetValue(stock.netValue);
	setValueDate(stock.valueDate);
	setYTDReturn(stock.ytdReturn);
}

const data& data::operator=(const data& stock)
{
	if (this == &stock)
		return *this;
	else
	{
		setTicker(stock.ticker);
		setName(stock.name);
		setNetValue(stock.netValue);
		setValueDate(stock.valueDate);
		setYTDReturn(stock.ytdReturn);
		return *this;
	}
}

data::~data()
{
	if (ticker)
		delete[] ticker;
	if (name)
		delete[] name;
	if (valueDate)
		delete[] valueDate;
}

void data::getTicker(char * ticker)const
{
	strcpy(ticker, this->ticker);
}

void data::getName(char * name)const
{
	strcpy(name, this->name);
}

float data::getNetValue(void) const
{
	return netValue;
}

void data::getValueDate(char * valueDate)const
{
	strcpy(valueDate, this->valueDate);
}

float data::getYTDReturn(void)const
{
	return ytdReturn;
}

void data::setTicker(const char * ticker)
{
	if (this->ticker)
		delete[] this->ticker;

	this->ticker = new char[strlen(ticker) + 1];
	strcpy(this->ticker, ticker);
}

void data::setName(const char * name)
{
	if (this->name)
		delete[] this->name;

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void data::setNetValue(const float netValue)
{
	this->netValue = netValue;
}

void data::setValueDate(const char * valueDate)
{
	if (this->valueDate)
		delete[] this->valueDate;

	this->valueDate = new char[strlen(valueDate) + 1];
	strcpy(this->valueDate, valueDate);
}

void data::setYTDReturn(const float ytdReturn)
{
	this->ytdReturn = ytdReturn;
}

bool operator> (const data& d1, const data& d2)
{
	char ticker1[6];
	char ticker2[6];

	d1.getName(ticker1);
	d2.getName(ticker2);

	if (strcmp(ticker1, ticker2) > 0)
		return true;
	else
		return false;
}

bool operator== (const data& d1, const data& d2)
{
	char ticker1[6];
	char ticker2[6];

	d1.getTicker(ticker1);
	d2.getTicker(ticker2);

	if (strcmp(ticker1, ticker2) == 0)
		return true;
	else
		return false;
}


ostream& operator<< (ostream& out, const data& stock)
{
	out << left << setw(10) << stock.ticker << setw(50) << stock.name << setw(10) << stock.netValue << setw(50) << stock.valueDate << setw(10) << stock.ytdReturn;
	return out;
}
