#include "Line.h"

Line::Line(char *a)
{
	stanum = 0;
	if (strlen(a)>29)
	{
		strcpy(name, "´íÎó!");
		return;
	}
	else
	{
		strcpy(name, a);
		return;
	}
	//ctor
}

Line::~Line()
{
	//dtor
}
int Line::add(Station *a)
{
	if (stanum>99)
		return 1;
	list[stanum] = a;
	stanum++;
	if (stanum>99)
		return 1;
	return 0;
}
char* Line::getName()
{
	return name;
}
Station* Line::getLast()
{
	if (stanum == 0)
		return NULL;
	return list[stanum - 1];
}
int Line::getStationNo(int i)
{
	if (i >= stanum)
		return -1;
	return list[i]->getNo();
}
int Line::getStationnum()
{
	return stanum;
}/*
int Line::coutPath(int start, int end)
{
	int i, j, n, m;
	for (i = n = 0;i<stanum;i++)
		if (list[i]->getNo() == start)
			break;
	m = n = 0;
	for (j = i;j<stanum;j++) {
		if (list[j]->getNo() == end)
			break;
		n++;
		if ((j + 1) == stanum)
			j = -1;
	}
	for (j = i;j >= 0;j--)
	{
		if (list[j]->getNo() == end)
			break;
		m++;
		if (j == 0)
			j = stanum;
	}
	if (n>m)
		return m;
	return n;
}
*/
void Line::printsta()
{
	int i, j;
	bool flag = false;
	for (i = 0;i<stanum;i++)
	{
		for (j = 0;j<i;j++) {
			if (list[j]->getNo() == list[i]->getNo()) {
				flag = true;
				break;
			}
		}
		if (flag) {
			flag = false;
			continue;
		}
		cout << list[i]->getName() << endl;
	}
}
/* 
void Line::printPath(int start, int end)
{
	int i, j, n, m;
	for (i = n = 0;i<stanum;i++)
		if (list[i]->getNo() == start)
			break;
	m = n = 0;
	for (j = i;j<stanum;j++) {
		if (list[j]->getNo() == end)
			break;
		n++;
		if ((j + 1) == stanum&&list[0]->getNo() == list[j]->getNo())
			j = -1;
	}
	if (j == stanum)
		n = 9999;
	for (j = i;j >= 0;j--)
	{
		if (stanum < 1)
			break;
		if (list[j]->getNo() == end)
			break;
		m++;
		if (j == 0 && list[j]->getNo() == list[stanum - 1]->getNo())
			j = stanum;
	}
	if (j == -1)
		m = 9999;
	if (n>m) {
		if (i <= 0 || i > stanum)
			return;
		while (list[i - 1]->getNo() != end) {
			cout << list[i - 1]->getName() << endl;
			i--;
			if (i == 0)
				i = stanum;
		}
	}
	else {
		while (list[i + 1]->getNo() != end) {
			cout << list[i + 1]->getName() << endl;
			i++;
			if (i == (stanum - 1))
				i = -1;
		}
	}
}
*/