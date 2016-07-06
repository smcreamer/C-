#ifndef DATA_H
#define DATA_H
#include <iostream>
using namespace std;
class data
{
public:

	data();
	data(const char * ticker, const char * name, const float netValue, const char * valueDate, const float ytdReturn);
	data(const data& stock);		
	~data();						

	void getTicker(char * ticker) const;
	void getName(char * name) const;
	float getNetValue(void) const;
	void getValueDate(char * valueDate) const;
	float getYTDReturn(void) const;

	void setTicker(const char * ticker);
	void setName(const char * name);
	void setNetValue(const float netValue);
	void setValueDate(const char * valueDate);
	void setYTDReturn(const float ytdReturn);

	friend ostream& operator<< (ostream& out, const data& student);
	const data& operator=(const data& student);

private:
	char * ticker;
	char * name;
	float netValue;
	char * valueDate;
	float ytdReturn;
};

bool operator> (const data& d1, const data& d2);
bool operator== (const data& d1, const data& d2);

#endif