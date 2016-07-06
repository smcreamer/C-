#ifndef DATA_H
#define DATA_H
#include <iostream>
using namespace std;

class data
{
public:
	data();
	data(const char *name, const char *loc, int year, float acres, float rating);
	data(const data& winery);
	~data();

	void getName(char *name) const;
	float getAcres() const;
	float getRating() const;
	int getYear() const;
	void getLoc(char *loc) const;

	void setName(const char *name);
	void setLocation(const char *loc);
	void setAcres(const float acres);
	void setRating(const float rating);
	void setYear(const int year);

	friend ostream& operator<< (ostream& out, const data& winery);
	const data& operator=(const data& winery);

private:
	char *name;
	char *loc;
	int year;
	float rating;
	float acres;


};

bool operator<(const data& w1, const data& w2);
bool operator== (const data& w1, const data& w2);

#endif