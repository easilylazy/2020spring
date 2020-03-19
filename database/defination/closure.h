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
	//属性用数组储存（存在置为1）
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

	//命令行读取输入属性个数
	void setAttributes();
	//判断输入属性值（数字/大写字母）是否合法
	bool isValid(char& ch);
	//初始化存储属性数组（存在置1）
	void initAttributes();
	//初始化闭包集（置0）
	void initClosure();
	//初始化序号为index的依赖（置0）
	void initDependencies(int index);
	//初始化最小依赖集（置1）
	void initbasisDependencies();
	//初始化控制依赖集（置1）
	void initControlDependencies();
	//初始化掩码属性集（置0）
	void initMaskAttributes();

	//更新属性个数，其他全部初始化
	void setNum(int num);
	//更新依赖集个数
	void setDependenciesNum(int num);
	//改变依赖的值设定，site为'l'选择改变左边的被依赖项，'r'改变右边依赖项; i,j表示改变第i项的第j个属性值为value（0/1）
	void setDependency(char, int, int, int);
	//传入数组直接改变依赖值，若state为-1，新增依赖项，否则改变第state项
	void setDependencies(int*, int*, int state = -1);
	//获取第index个函数依赖的右部（默认经过了分解，只有一个值）
	int getRightDependency(int index);
	//命令行获取输入，添加新的依赖（被addDependency()调用）
	int addSide(char& choice, int* determine);
	//命令行获取输入，添加新的依赖
	void addDependency();
	//设定闭包的初始值，即定义需要求取的属性
	void setClosure();
	//寻找某属性在某函数依赖集下的闭包
	void findClosure();


	//寻找某函数依赖集的basis/最小依赖集
	void findBasis();
	//将第index依赖的所有属性传入closure
	//再便于之后计算属性在其他函数依赖下的闭包能否覆盖index的右部属性，若能，则可删去该函数依赖//
	void sendToClosure(int index);
	//寻找某属性在某函数依赖集下的闭包
	//特别：求basis时，跳过某个假设除去的依赖
	void findClosure(int);
	//求最小依赖集的第二个步骤
	void secondProcess();
	//改变控制依赖集，被 findBasis() 调用
	bool changeControl();
	//寻找某属性在某函数依赖集下的闭包
	//特别： 计算除第index依赖以外剩下的依赖的闭包
	void findClosure(char choice, int index);
	//除了某删去第index依赖的第mask属性,将其他的属性传入closure
	//再便于之后计算其他属性在其他函数依赖下的闭包能否覆盖删除属性，若能，则可删去该函数依赖下中左部的该属性
	void sendToClosure(int index, int mask);


	void split()
	{
		//可以获取右部多于1的输入，并将其分解转化为全为1
		//例：
		//X->A1,A2,A3
		//转化为
		//X->A1
		//X->A2
		//X->A3
		//TODO
	}
	//打印基本信息（全部）
	void printInfo();
	//打印最小函数依赖
	void printBasis();
	//打印第index个属性名称
	void printAttribute(int index);
	//打印某个数组attributes中为1的值对应的字母名称
	void printAttributes(int* attributes, char choice = 'w');
};
