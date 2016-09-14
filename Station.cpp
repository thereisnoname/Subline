#include "Station.h"

Station::Station(char *a, int no)
{
	//line=NULL;
	linenum = 0;
	nearbynum = 0;
	staNo = no;
	if (strlen(a)>namelength) {
		strcpy(a, "´íÎó£¡");
		return;
	}
	else
		strcpy(name, a);
	return;
	//ctor
}

Station::~Station()
{
	//dtor
}
int Station::add(int lineNo)
{
	if (linenum>9)
		return 1;
	for (int i = 0;i<linenum;i++)
	{
		if (line[i] == lineNo)
			return 0;
	}
	line[linenum] = lineNo;
	linenum++;
	if (linenum>9)
		return 1;
	else
		return 0;
}
char * Station::getName()
{
	return name;
}
int Station::addNear(int nearstaNo, int sublineNo)
{
	if (nearbynum>=maxnearbynum)
		return 1;
	nearbysta[nearbynum][0] = nearstaNo;
	nearbysta[nearbynum][1] = sublineNo;
	nearbynum++;
	return 0;
}
int Station::getNearbynum()
{
	return nearbynum;
}
int Station::getNearbysta(int i)
{
	if (i >= nearbynum)
		return -1;
	return nearbysta[i][0];
}
int Station::getNearbypath(int i)
{
	if (i >= nearbynum)
		return -1;
	return nearbysta[i][1];
}
int Station::getNo()
{
	return staNo;
}
int Station::getSublinenum()
{
	return linenum;
}
int Station::getSubline(int i)
{
	if (i >= linenum)
		return -1;
	return line[i];
}
