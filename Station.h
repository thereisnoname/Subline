#ifndef STATION_H
#define STATION_H
#include "string.h"
//#define _CRT_SECURE_NO_WARNINGS

#define namelength 30
#define maxnearbynum 20
class Station
{
public:
	Station(char *a, int no);
	int add(int lineNo);
	char* getName();
	int addNear(int nearstaNo, int sublineNo);
	int getNo();
	int getNearbysta(int i);
	int getNearbynum();
	int getNearbypath(int i);
	int getSublinenum();
	int getSubline(int i);
	virtual ~Station();
protected:
private:
	int line[10];
	int linenum;
	int nearbysta[maxnearbynum][2];//[0] for station [1] for subwayline
	int nearbynum;
	int staNo;
	char name[namelength];
};

#endif // STATION_H
#pragma once
