#pragma once
#include <malloc.h>

#include<iostream>
#define MAXSIZE 10
#define MAXNUM 20
#define LESSINFO true //减少打印信息
using namespace std;


class form
{

private:
	int attributesNum;
	int dependenciesNum; 
	int attributes[MAXSIZE];
	int leftDetermine[MAXNUM][MAXSIZE];
	int rightDetermine[MAXNUM][MAXSIZE];	
	int closure[MAXSIZE];

public:
	string tips = "(q to quit and s to save): ";


	form();
	form(int num);
	
	void setAttributes();
	bool isValid(char &ch);
	void initAttributes(int num);
	void initClosure(int num);
	void initDependencies(int index);
	void setNum(int num);
	int addSide(char& choice, int* determine);
	void addDependency();

	void setClosure();
	void findClosure();
		
	void split()
	{

	}
	void print();
	void printAttribute(int index);
	void printAttributes(int* attributes, char choice = 'w');
	


};
