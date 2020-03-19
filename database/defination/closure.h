#pragma once
#include <malloc.h>

#include<iostream>
//属性个数限制
#define MAXSIZE 10
//依赖个数限制
#define MAXNUM 30
//减少打印信息
#define LESSINFO true 
using namespace std;


class form
{

private:
	//属性值总个数
	int attributesNum;
	//依赖函数总个数
	int dependenciesNum;
	//右部全都转化为单值的依赖个数（暂未使用）
	int toOneDependenciesNum;
	//属性值用数组储存（存在置为1）
	int attributes[MAXSIZE];
	//储存依赖某一项的左部X，对应右部Y,有X->Y
	int leftDependencies[MAXNUM][MAXSIZE];
	//储存依赖某一项的右部Y，对应左部,有X->Y
	int rightDependencies[MAXNUM][MAXSIZE];


	//右边转化为单值储存（暂未使用）
	//总维度（左侧）表示第i组依赖关系，二维表示该组依赖关系中的第几个
	int toOneDependency[MAXNUM][MAXSIZE];

	//储存求得某函数依赖集关于某属性集的闭包结果
	int closure[MAXSIZE];

	//存储获取最小依赖集
	int basisDependencies[MAXNUM];
	//存储设定依赖项以便得到所有可能的最小依赖集
	int controlDependencies[MAXNUM];
	//存储可被删去的左部单个属性
	int maskAttributes[MAXNUM][MAXSIZE];

	//最小依赖集是本身
	bool ownIsBasis;
public:
	//提示语
	string tips = "(q to quit and s to save): ";

	//构造函数，默认
	form();
	//传入属性个数
	form(int num);

	void setAttributes();
	bool isValid(char& ch);
	void initAttributes();
	void initClosure();
	void initDependencies(int index);
	void initbasisDependencies();
	void initControlDependencies();
	void initMaskAttributes();

	void setNum(int num);
	void setDependenciesNum(int num);
	//改变依赖的值设定，site为'l'选择改变左边的被依赖项，'r'改变右边依赖项; i,j表示改变第i项的第j个属性值为value（0/1）
	void setDependency(char, int, int, int);
	//传入数组直接改变依赖值，若state为-1，新增依赖项，否则改变第state项
	void setDependencies(int*, int*, int state = -1);
	//获取第index个函数依赖的右部（默认经过了分解，只有一个值）
	int getRightDependency(int index);
	int addSide(char& choice, int* determine);
	void addDependency();



	void findBasis();

	bool changeControl();

	void findClosure(char choice, int index);

	void secondProcess();


	void sendToClosure(int index, int mask);
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
