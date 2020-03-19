#pragma once
#include <malloc.h>

#include<iostream>
#define MAXSIZE 10
#define MAXNUM 30
#define LESSINFO true //减少打印信息
using namespace std;


class form
{

private:
	int attributesNum;
	int dependenciesNum;
	int toOneDependenciesNum;
	int attributes[MAXSIZE];
	int leftDependencies[MAXNUM][MAXSIZE];
	int rightDependencies[MAXNUM][MAXSIZE];


	//右边转化为单值储存
	int toOneDependency[MAXNUM][MAXSIZE];//总维度（左侧）表示第i组依赖关系，二维表示该组依赖关系中的第几个
	int closure[MAXSIZE];

	int basisDependencies[MAXNUM];//存储获取最小依赖集
	int controlDependencies[MAXNUM];//存储设定依赖项以便得到所有可能的最小依赖集
public:
	string tips = "(q to quit and s to save): ";


	form();
	form(int num);

	void setAttributes();
	bool isValid(char& ch);
	void initAttributes();
	void initClosure();
	void initDependencies(int index);
	void initbasisDependencies();
	void initControlDependencies();

	void setNum(int num);
	void setDependenciesNum(int num);
	//改变依赖的值设定，site为'l'选择改变左边的被依赖项，'r'改变右边依赖项; i,j表示改变第i项的第j个属性值为value（0/1）
	void setDependency(char, int, int, int);
	//传入数组直接改变依赖值，若state为-1，新增依赖项，否则改变第state项
	void setDependencies(int*, int*, int state = -1);
	int addSide(char& choice, int* determine);
	void addDependency();

	void findBasis();

	bool changeControl();

	void sendToClosure(int index);
	void setClosure();
	void findClosure();
	void findClosure(int);//求basis

	void split()
	{
		//TODO
	}
	void print();
	void printBasis();
	void printAttribute(int index);
	void printAttributes(int* attributes, char choice = 'w');



};
