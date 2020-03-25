#pragma once
#include <malloc.h>
#include <string>
#include<iostream>
//属性个数限制
#define MAXSIZE 15
//依赖个数限制
#define MAXNUM 50
////减少打印信息
//#define hideProcess false

#define BASESMAXNUM 100


using namespace std;

//英文
extern string language;
//提示
extern bool displayTips;
//过程
extern bool hideProcess;
//溢出
extern bool overFlow;
void initArray(int* array,int length,int initValue = 0);
void printArray(int* array, int length);
void initArray2d(int* array, int M, int N, int initValue = 0);
void printArray(int* array, int M, int N);
bool compareArray(int* firstArray, int* secondArray, int length);
class minimalBase
{
private:
	int dependenciesNum;
	int finalDependenciesNum;
	int attributesNum;
	
	int leftDependencies[MAXNUM][MAXSIZE];
	int rightDependencies[MAXNUM];

public:
	bool isValid;//若记录的最小依赖集已存在相同的，则为false
#pragma region 构函
	minimalBase()
	{
		isValid = false;//change  origin true
		dependenciesNum = 0;
		finalDependenciesNum = 0;
		attributesNum = 0;
		//initLeft
		initArray(rightDependencies, MAXNUM, -1);
		initArray2d((int*)leftDependencies, MAXNUM, MAXSIZE);


		//initRight();
	}
#pragma endregion

#pragma region 设定
	//设定属性值总数
	inline void setAttributesNum(int num)
	{
		attributesNum = num;
	}
	//设定依赖集总数
	inline void setDependenciesNum(int num)
	{
		dependenciesNum = num;
	}
	//设定依赖集内容
	inline void setLeftDependency(int i, int j)
	{
		leftDependencies[i][j] = 1;
	}
	//设定依赖集内容
	inline void setRightDependency(int index, int value)
	{
		rightDependencies[index] = value;
	}
#pragma endregion

#pragma region 取值
	inline int getDependenciesNum()
	{
		return dependenciesNum;
	}
#pragma endregion

#pragma region 去重
	//若依赖右部的内容已被前部包含(平凡依赖)，则去除该依赖（右部设为-1）
	void dropTrivival()
	{
		for (int i = 0; i < dependenciesNum; i++)
		{
			int rightValue = rightDependencies[i];
			if (rightValue >= 0
				&& rightValue < dependenciesNum
				&& leftDependencies[i][rightValue] == 1)
			{
				rightDependencies[i] = -1;
			}
			else if (rightValue >= 0
				&& rightValue < dependenciesNum
				&& leftDependencies[i][rightValue] != 1)
			{
				finalDependenciesNum++;
			}
		}
	}
	//若依赖右部的内容已被前部包含，则去除该依赖（右部设为-1）
	void dropRepeated()
	{
		bool passCheck;
		for (int i = 0; i < dependenciesNum; i++)
		{
			
			//每个有效的依赖与之前的所有依赖比较，检查是否有完全重复的，若有，右部设为-1，依赖数目减1

			if (isNumValid(rightDependencies[i]))
			{
				

				for (int j = 0; j < i; j++)
				{
					//先比较右部
					if (rightDependencies[i] == rightDependencies[j])
					{
						passCheck = false;
						//若右部相同，比较左部数组是否完全相同
						for (int k = 0; k < attributesNum; k++)
						{
							int currentValue = leftDependencies[i][k];
							int pastValue = leftDependencies[j][k];
							if (currentValue != pastValue)
							{
								//只要有一个不相同，那就通过检测
								passCheck = true;
								//break;
							}
						}

						if (passCheck != true)
						{
							rightDependencies[i] = -1;
							finalDependenciesNum--;
						}
					}
				
				}			
			}		
		}
	}
#pragma endregion

#pragma region 打印
	void printResult()
	{

#pragma region tips
		string tip1, tip2;
		if (language == "EN")
		{
			tip1 = "after drop trivival: ";
			tip2 = "after drop repeated: ";
		}
		if (language=="CN")
		{
			tip1 = "去除平凡依赖后: ";
			tip2 = "去除重复依赖后: ";
		}
#pragma endregion

		if (hideProcess == false)
		{
			//printDependencies();
			dropTrivival();
			cout << tip1 << endl;
			printDependencies();
			dropRepeated();
			cout << tip2 << endl;
			printDependencies();
		}
		else
		{
			dropTrivival();
			dropRepeated();
		}


	}
	void printDependencies();
	void printAttributes(int* attributes, char choice);
	bool isNumValid(int);
#pragma endregion


	friend void initArray(int* array, int length, int initvalue);
	friend void initArray2d(int* array, int M, int N, int initValue);
	friend void printArray(int* array, int length);
	friend void printArray(int* array, int M, int N);

	friend class form;
};
class form
{

private:
	//最小依赖集个数
	int minimalBasesNum;
	//存储最小依赖集数据
	minimalBase minimalBases[BASESMAXNUM];
	minimalBase current;
	minimalBase last;


	//属性值总个数
	int attributesNum;
	//右部全都转化为单值的依赖个数（暂未使用）
	int toOneDependenciesNum;
	//属性用数组储存（存在置为1）
	int attributes[MAXSIZE];
	//储存依赖某一项的左部X，对应右部Y,有X->Y
	int toOneLeftDependencies[MAXNUM][MAXSIZE];
	//储存依赖某一项的右部Y，对应左部,有X->Y
	int toOneRightDependencies[MAXNUM];

	//右边转化为单值储存（暂未使用）
	//总维度（左侧）表示第i组依赖关系，二维表示该组依赖关系中的第几个
	int toOneDependency[MAXNUM][MAXSIZE];

	//储存求得某函数依赖集关于某属性集的闭包结果
	int closure[MAXSIZE];

	//已经寻找完成闭包
	bool closureFound;

	//存储获取最小依赖集
	int basisDependencies[MAXNUM];
	//存储设定依赖项以便得到所有可能的最小依赖集
	int controlDependencies[MAXNUM];
	//存储可被删去的左部单个属性
	int maskAttributes[MAXNUM][MAXSIZE];

	//最小依赖集是本身
	bool ownIsBasis;
	//已经寻找完成最小依赖集
	bool basisFound;
public:
	//提示语
	string tips = "(q to quit and s to save): ";
	string tipsCN = "(输入 s 保存/输入 q 不保存退出): ";

	//构造函数，默认
	form();
	//传入属性个数
	form(int num);

#pragma region 初始化
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
	void initMinimalBases();
	//初始化最小依赖集（置1）
	void initbasisDependencies();
	//初始化控制依赖集（置1）
	void initControlDependencies();
	//初始化掩码属性集（置0）
	void initMaskAttributes();
#pragma endregion

	
#pragma region 输入依赖
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
	bool isValidNew(char& ch);
	//命令行获取输入，添加新的依赖（被addDependency()调用）
	int addSide(char& choice, int* determine);
	//命令行获取输入，添加新的依赖
	void addDependency();
	//设定闭包的初始值，即定义需要求取的属性
	void setClosure();
	//寻找某属性在某函数依赖集下的闭包
	void findClosure();
#pragma endregion
	

#pragma region 寻找依赖集
	//寻找某函数依赖集的basis/最小依赖集
	bool findBasis();
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
	
#pragma endregion

	bool printFinalResult(minimalBase& current);
	//只打印和前面不完全相同的依赖集
	void printFinalResult();
	//比较两个数组中，完全一样返回true，否则返回false
	friend bool compareArray(int* firstArray, int* secondArray, int length);

	//比较两个数组中，如果current中的所有内容被exist包含，完全一样返回true，否则返回false
	bool compare(minimalBase current, minimalBase exist);

#pragma region 打印信息
	//打印基本信息（全部）
	void printInfo();
	//打印最小函数依赖
	void printBasis();
	//将找到的最小函数依赖集保存至saveTo
	void saveBasis(minimalBase& saveTo);
	//将找到的最小函数依赖集保存至minimalBases中
	bool saveBasis();
	//打印第index个属性名称
	void printAttribute(int index);
	//打印某个数组attributes中为1的值对应的字母名称
	void printAttributes(int* attributes, char choice = 'w');

	void printMinimaBases();
	void printMinimaBases(minimalBase base);
#pragma endregion

	
		
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
	friend class minimalBase;

};
