#ifndef DATA_H
#define DATA_H
#include <iostream>
using namespace std;

class data
{
public:
	data();
	data(const char *address, int sqFt, int numBed, float numBath, const char *desc);
	data(const data& house);
	~data();

	void getAddress(char *address) const;
	float getNumBath() const;
	int getSqFt() const;
	int getNumBed() const;
	void getDesc(char *desc) const;

	void setAddress(const char *address);
	void setSqFt(const int sqFt);
	void setNumBed(const int numBed);
	void setNumBath(const float numBath);
	void setDesc(const char *desc);

	friend ostream& operator<< (ostream& out, const data& house);
	const data& operator=(const data& house);

private:
	char *address;
	int sqFt;
	int numBed;
	float numBath;
	char *desc;

};

#endif