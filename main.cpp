#include <iostream>
#include "string.h"
#include "stdio.h"
#include "Station.h"
#include "Line.h"
//#define _CRT_SECURE_NO_WARNINGS

using namespace std;
void shortestPath(int start, int end);
void shortestChange(int start, int end);
//void printPath(int start, int end);
int coutPath(int start, int end, int lineNo);
//global variables
Line *subline[100];
Station *sta[1000];
int linenum = 0;
int stanum = 0;

int main(int argc, char* argv[])
{
	FILE *file = fopen("beijing-subway.txt", "r");
	if (file == NULL)
		cout << "Cannot find \"beijing-subway.txt\".Please make sure you have it in your current directory." << endl;
	char a[1000], temp[namelength];
	int before=-1;
	int length;
	int i, j, tempindex;
	bool flag = false;
	//Pre-treatment
	while (fgets(a, 1000, file) != NULL)
	{
		while (strlen(a) == 1) {
			if (fgets(a, 1000, file) == NULL)
			{
				flag = true;
				break;
			}
		}
		if (flag)
			break;
		a[strlen(a) - 1] = '\0';
		subline[linenum] = new Line(a);
		fgets(a, 1000, file);
		length = strlen(a);
		if (length > 900) {
			cout << "There is no such long subway line." << endl;
			cin >> linenum;
			return 0;
		}
		before = -1;
		for (i = tempindex = 0;i <= length;i++)
		{
			if (a[i] == ' ' || a[i] == '\n' || a[i] == '\0')
			{
				if (tempindex == 0)
				{
					//do nothing
				}
				else {
					temp[tempindex] = '\0';
					//cout<<temp<<endl;
					for (j = 0;j<stanum;j++)
						if (strcmp(temp, sta[j]->getName()) == 0)
						{
							sta[j]->add(linenum);
							break;
						}
					if (j == stanum)
					{
						sta[stanum] = new Station(temp, stanum);
						sta[stanum]->add(linenum);
						stanum++;
					}
					
					if (before!=-1) {
						//cout<<subline[linenum]->getLast()->getName()<<endl;
						sta[before]->addNear(j, linenum);
						sta[before]->addNearBack(j, linenum);
						sta[j]->addNear(before, linenum);
						sta[j]->addNearBack(before, linenum);
					}
					before = j;
					subline[linenum]->add(sta[j]);
					tempindex = 0;
				}

			}
			else if (a[i] == '*')
			{
				if (tempindex == 0)
				{
					//do nothing
				}
				else {
					temp[tempindex] = '\0';
					//cout<<temp<<endl;
					for (j = 0;j<stanum;j++)
						if (strcmp(temp, sta[j]->getName()) == 0)
						{
							sta[j]->add(linenum);
							break;
						}
					if (j == stanum)
					{
						sta[stanum] = new Station(temp, stanum);
						sta[stanum]->add(linenum);
						stanum++;
					}
					if (before!=-1) {
						//cout<< sta[before]->getName()<<endl;
						sta[before]->addNearBack(j, linenum);
						sta[j]->addNear(before, linenum);
					}
					subline[linenum]->add(sta[j]);
					tempindex = 0;
					before = j;
				}
			}
			else {
				temp[tempindex] = a[i];
				tempindex++;
			}
		}
		linenum++;
		if (linenum > 99)
		{
			cout << "Does Beijing in your world-line has over one hundred subway lines?" << endl;
			cin >> linenum;
			return 0;
		}
		//cout<<a<<endl;
	}
	if (argc == 2 || argc>4 || argc == 3)
	{
		cout << "ERROR!" << endl;
		cin >> linenum;
		return 0;
	}
	char aaa[100];
	if (argc == 1)
	{
		while (true)
		{
			cin >> aaa;
			if (strlen(aaa) > 60)
				cout << "Too Long!" << endl;
			for (i = 0;i < linenum;i++)
			{
				if (strcmp(subline[i]->getName(), aaa) == 0)
				{
					subline[i]->printsta();
					break;
				}
			}
			if(i==linenum)
				cout << "NO SUCH LINE!" << endl;
		}
		cin >> linenum;
		return 0;
	}
	if (argc == 4) {
		int start, end;
		start = end = 9999;
		for (i = 0;i<stanum;i++)
		{
			if (strcmp(sta[i]->getName(), argv[2]) == 0)
				start = i;
			if (strcmp(sta[i]->getName(), argv[3]) == 0)
				end = i;
		}
		if (start == 9999 || end == 9999)
		{
			cout << "NO SUCH STATION!" << endl;
			cin >> linenum;
			return 0;
		}
		if (strcmp(argv[1], "-b") == 0)
			shortestPath(start, end);
		else if (strcmp(argv[1], "-c") == 0)
			shortestChange(start, end);
		else
			cout << "NO SUCH INSTRUCTION!" << endl;
		cin >> start;
		return 0;
	}
	/* using for test pre op
	for(i=0;i<stanum;i++)
	{
	if(strcmp(sta[i]->getName(),"Î÷Ö±ÃÅ")==0)
	{
	cout<<"Got it!"<<endl;
	length=sta[i]->getNearbynum();
	for(j=0;j<length;j++)
	{
	cout<<sta[sta[i]->getNearbysta(j)]->getName()<<endl;
	}
	}
	}
	*/
	/*
	char start[namelength],end[namelength];
	int star,en;
	while(true){
	cin>>start>>end;
	for(i=0;i<stanum;i++)
	{
	if(strcmp(sta[i]->getName(),start)==0)
	star=i;
	if(strcmp(sta[i]->getName(),end)==0)
	en=i;
	}
	cout<<sta[star]->getName()<<" "<<sta[en]->getName()<<endl;

	shortestChange(star,en);
	}
	*/
	/*
	for(int i=1;i<argc;i++)
	{
	cout<<argv[i]<<endl;

	int length=strlen(argv[i]);
	cout<<strlen(argv[i])<<endl;
	for(int j=0;j<length;j++)
	{
	cout<<int(argv[i][j])<<endl;
	}

	}
	char a[3];
	a[0]=argv[1][0];
	a[1]=argv[1][1];
	a[2]='\0';
	cout << a << endl;
	*/
}
void shortestPath(int start, int end)
{
	int temp;
	temp = start, start = end, end = temp;//reverse for backtracking
	int distance[1000];
	int prepoints[1000];
	int prelength;
	int nowpoints[1000];
	int nowlength;
	int temppoint;
	int i, j, length;
	for (i = 0;i<1000;i++)
		distance[i] = 9999;
	prelength = 1;
	prepoints[0] = start;
	distance[start] = 0;
	//get distance
	while (distance[end] == 9999) {
		for (i = nowlength = 0;i<prelength;i++)
		{
			length = sta[prepoints[i]]->getNearbynum();
		//	cout << sta[prepoints[i]]->getName() << endl;
			for (j = 0;j<length;j++)
			{
				temppoint = sta[prepoints[i]]->getNearbysta(j);
				if (distance[temppoint] <= (distance[prepoints[i]] + 1))
					continue;
				distance[temppoint] = distance[prepoints[i]] + 1;
		//		cout << sta[temppoint]->getName() << endl;
				nowpoints[nowlength] = temppoint;
				nowlength++;
			}
		}
		if (nowlength == 0)
		{
			cout << "There is no direct way." << endl;
			return;
		}
		for (i = 0;i<nowlength;i++)
			prepoints[i] = nowpoints[i];
		prelength = nowlength;
	}
	//backtracking
	temppoint = end;
	int nowsubline = -1;
	cout << distance[end] +1<< endl;
	for (nowlength = distance[end] - 1;nowlength >= 0;nowlength--) {
		length = sta[temppoint]->getNearbyBacknum();
		for (i = 0;i<length;i++)
		{
			if (distance[sta[temppoint]->getNearbyBacksta(i)] == nowlength) {
				if (nowsubline == -1) {
					nowsubline = sta[temppoint]->getNearbyBackpath(i);
					cout << sta[temppoint]->getName() << endl;
					temppoint = sta[temppoint]->getNearbyBacksta(i);
				}
				else if (nowsubline != sta[temppoint]->getNearbyBackpath(i))
				{
					nowsubline = sta[temppoint]->getNearbyBackpath(i);
					cout << sta[temppoint]->getName() << "换乘" << subline[nowsubline]->getName() << endl;
					temppoint = sta[temppoint]->getNearbyBacksta(i);
				}
				else
				{
					cout << sta[temppoint]->getName() << endl;
					temppoint = sta[temppoint]->getNearbyBacksta(i);
				}

				// cout<<"nowsubline:"<<nowsubline<<endl;
				break;
			}
		}
	}
	cout << sta[temppoint]->getName() << endl;

}
void shortestChange(int start, int end)
{
	int temp;
	temp = start, start = end, end = temp;//reverse for backtracking
	int distance[1000];
//	int points[1000];
	int prepoints[1000];
	int prelength;
	int nowpoints[1000];
	int path[1000];
//	int pathlength;
	int nowlength;
	int temppoint;
	int templine;
	int templength;
	int i, j, length;
	for (i = 0;i<1000;i++)
		distance[i] = 9999,path[i]=9999;
	prelength = 1;
	prepoints[0] = start;
	distance[start] = 0;
	path[start] = 0;
	//get distance
	while (distance[end] == 9999) {
		for (i = nowlength = 0;i<prelength;i++)
		{
			length = sta[prepoints[i]]->getSublinenum();
			if (length == 0)
				cout << "错误！该站附近没有地铁。" << endl;
			for (j = 0;j<length;j++)
			{
				templine = sta[prepoints[i]]->getSubline(j);
				templength = subline[templine]->getStationnum();
				for (int k = 0;k<templength;k++) {
					temppoint = subline[templine]->getStationNo(k);
					if (distance[temppoint] < (distance[prepoints[i]] + 1))
						continue;
					if (distance[temppoint] == (distance[prepoints[i]] + 1))
					{
						if (path[temppoint] > (path[prepoints[i]] + coutPath(prepoints[i], temppoint , templine)))
							path[temppoint] = path[prepoints[i]] + coutPath(prepoints[i], temppoint , templine);
						continue;
					}
					distance[temppoint] = distance[prepoints[i]] + 1;
					path[temppoint] = path[prepoints[i]]+coutPath(prepoints[i], temppoint,templine);
					nowpoints[nowlength] = temppoint;
					nowlength++;
				}
			}
		}
		if (nowlength == 0)
		{
			cout << "There is no direct way." << endl;
			return;
		}
		for (i = 0;i<nowlength;i++)
			prepoints[i] = nowpoints[i];
		prelength = nowlength;
	}
	//backtracking
	temppoint = end;
	int nowsubline = -1;
	bool flag = false;
//	int index;
//	int targetline;
//	int templinenum;
	int max = 9999;
	cout << path[end]+1 << endl;
	for (nowlength = path[end] - 1;nowlength >= 0;nowlength--) {
		length = sta[temppoint]->getNearbyBacknum();
		for (i = 0;i<length;i++)
		{
			if (path[sta[temppoint]->getNearbyBacksta(i)] == nowlength) {
				if (nowsubline == -1) {
					nowsubline = sta[temppoint]->getNearbyBackpath(i);
					cout << sta[temppoint]->getName() << endl;
					temppoint = sta[temppoint]->getNearbyBacksta(i);
				}
				else if (nowsubline != sta[temppoint]->getNearbyBackpath(i))
				{
					nowsubline = sta[temppoint]->getNearbyBackpath(i);
					cout << sta[temppoint]->getName() << "换乘" << subline[nowsubline]->getName() << endl;
					temppoint = sta[temppoint]->getNearbyBacksta(i);
				}
				else
				{
					cout << sta[temppoint]->getName() << endl;
					temppoint = sta[temppoint]->getNearbyBacksta(i);
				}
			//	cout << nowlength << endl;
				 //cout<<"nowsubline:"<<nowsubline<<endl;
				break;
			}
		}
	}
	cout << sta[temppoint]->getName() << endl;
	/*
	for (nowlength = distance[end] - 1;nowlength >= 0;nowlength--) {
		templinenum = sta[temppoint]->getSublinenum();
		for (j = 0;j<templinenum;j++) {
			templine = sta[temppoint]->getSubline(j);
			for (i = 0;i<subline[templine]->getStationnum();i++)
			{
				if (distance[subline[templine]->getStationNo(i)] == nowlength) {
					if (max>subline[templine]->coutPath(temppoint, subline[templine]->getStationNo(i))) {
						max = subline[templine]->coutPath(temppoint, subline[templine]->getStationNo(i));
						index = i;
						targetline = templine;
					}
				}
			}
		}
		if (max == 9999) {
			cout << "路线规划失败" << endl;
			return;
		}
		max = 9999;
		if (nowsubline == -1) {
			cout << sta[temppoint]->getName() << endl;
			printPath(temppoint, subline[targetline]->getStationNo(index));
			temppoint = subline[targetline]->getStationNo(index);
			nowsubline = targetline;
		}
		else {
			cout << sta[temppoint]->getName() << "换乘" << subline[targetline]->getName() << endl;
			printPath(temppoint, subline[targetline]->getStationNo(index));
			temppoint = subline[targetline]->getStationNo(index);
			nowsubline = targetline;
		}
	}
	cout << sta[temppoint]->getName() << endl;
	*/
}



int coutPath(int start, int end,int lineNo)
{
	int length = sta[start]->getSublinenum();
	int i, j, k;
	//int linelist[20];
	int temp,index;
	int points[20];
	int ways[20][100];
	int templength;
	length= sta[start]->getNearbynum();
	for (i = 0;i<length;i++)
		points[i] = sta[start]->getNearbysta(i), ways[i][0] = start, ways[i][1] = points[i];
	bool flag = false;

	//length = sta[start]->getNearbynum();
	/*
	for (i = 0;i<length;i++)
		linelist[i] = sta[start]->getNearbypath(i);
	*/
	for (i = 0;i < length;i++)
		if (points[i] == end&&sta[start]->getNearbypath(i) == lineNo)
			return 1;
	temp = 2;
	while (true) {
		for (i = 0;i<length;i++)
		{
			//cout << sta[points[i]]->getName() << endl;
			if (points[i] == end && temp > 2) {
				flag = true;
				break;
			}
			templength = sta[points[i]]->getNearbynum();
			index = points[i];
			for (j = 0;j<templength;j++)
			{
				if (sta[points[i]]->getNearbypath(j) == lineNo) {
					for (k = 0;k<temp;k++)
						if (ways[i][k] == sta[points[i]]->getNearbysta(j))
							break;
					if (k == temp) {
						ways[i][temp] = sta[points[i]]->getNearbysta(j), index = ways[i][temp];
						//cout << sta[points[i]]->getName() << endl;
					}
				}
			}
			points[i] = index;
		}
		if (flag)
			break;

		temp++;
		if (temp == 100) {
		//	cout << sta[start]->getName() << " " << sta[end]->getName() << " " << subline[lineNo]->getName() << endl;
			return 9999;
		}

	}
	// print path
//	for (j = 1;j<(temp - 1);j++)
	//	cout << sta[ways[i][j]]->getName() << endl;

	return temp-1;
	
	
}

