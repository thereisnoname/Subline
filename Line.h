#ifndef LINE_H
#define LINE_H
#include "Station.h"
#include <iostream>
using namespace std;
class Line
{
public:
	Line(char *a);
	int add(Station *a);
	char* getName();
	//Station* get(int i); not used
	Station* getLast();
	int getStationNo(int i);
	int getStationnum();
	//void printPath(int start, int end);
	int coutPath(int start, int end);
	void printsta();
	virtual ~Line();
protected:
private:
	char name[namelength];
	int stanum;
	Station *list[100];
};

#endif // LINE_H
