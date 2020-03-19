#define _CRT_SECURE_NO_WARNINGS
#include "closure.h"

//PPT上例子
void defaultSetting(form& sets)
{
	int attributesNum = 3;//A,B,C
	int dependenciesNum = 6;
	int leftDependencies[6][3] = {
		{1,0,0},{1,0,0},    //A
		//{1,1,0},{1,1,0},    //AB
		{0,1,0},{0,1,0},	//B
		{0,0,1},{0,0,1}		//C
	};
	int rightDependencies[6][3] = {
		{0,1,0},{0,0,1},    //A->B, A->C,		
		{1,0,0},{0,0,1},	//B->A, B->C,
		{1,0,0},{0,1,0}		//C->A, C->B
	};
	sets.setNum(3);
	for (int i = 0; i < dependenciesNum; i++)
	{
		sets.setDependencies(leftDependencies[i], rightDependencies[i]);
	}
}
//博客中例子https://blog.csdn.net/Game_Zmh/article/details/88061628
void defaultSetting2(form& sets)
{
	int attributesNum = 5;//A,B,C,D,E
	int dependenciesNum = 5;

	int leftDependencies[5][5] = {
		{1,0,0,0,0},{1,0,0,0,0},    //A
		{1,1,0,1,0},{1,1,0,1,0},    //ABD
		{0,0,0,0,1}		//E
	};
	int rightDependencies[5][5] = {
		{0,1,0,0,0},{0,0,1,0,0},    //A->B,A->C
		{0,0,1,0,0},{0,0,0,0,1}	,    //ABD->C,ABD->E
		{0,0,0,1,0}		//E->D
	};
	sets.setNum(attributesNum);
	for (int i = 0; i < dependenciesNum; i++)
	{
		sets.setDependencies(leftDependencies[i], rightDependencies[i]);
	}


}
//博客中例子https://www.cnblogs.com/wangyige/p/6786047.html
void defaultSetting3(form& sets)
{
	int attributesNum = 10;//A,B,C,D,E,F,G,H
	int dependenciesNum = 6;

	int leftDependencies[6][10] = {
		{1,1,0,1,0,0,0,0,0,0},    //ABD
		{1,1,0,0,0,0,0,0,0,0},    //AB
		{0,1,0,0,0,0,0,0,0,0},    //B
		{0,0,1,0,0,0,0,0,0,0},    //C
		{0,0,1,0,0,0,0,0,0,1},    //CJ
		{0,0,0,0,0,0,1,0,0,0}    //G

	};
	int rightDependencies[6][10] = {
		{0,0,0,0,1,0,0,0,0,0},    //ABD->E
		{0,0,0,0,0,0,1,0,0,0},    //AB->G
		{0,0,0,0,0,1,0,0,0,0},    //B->F
		{0,0,0,0,0,0,0,0,0,1},    //C->J
		{0,0,0,0,0,0,0,0,1,0},    //CJ->I
		{0,0,0,0,0,0,0,1,0,0}    //G->H

	};
	sets.setNum(attributesNum);
	for (int i = 0; i < dependenciesNum; i++)
	{
		sets.setDependencies(leftDependencies[i], rightDependencies[i]);
	}


}


int main(void)
{
	//实例对象
	form sets;

	//设置为默认情况
	defaultSetting3(sets);


	string menu = "********************MENU********************\n"\
		"i.initAttributes\ta.addDependency\ts.setClosure\nf.findClosure\t"\
		"p.printInfo\tb.basisDependencies\nq.quit\n"\
		"********************************************\n";
	char choice;

	//打印菜单，读取输入
	cout << menu;
	cin >> choice;

	while (choice != 'q')
	{
		switch (choice)
		{
		case'i':
			sets.setAttributes();
			break;
		case'a':
			sets.addDependency();
			break;
		case's':
			sets.setClosure();
			break;
		case'f':
			sets.findClosure();
			break;
		case'p':
			sets.printInfo();
			break;
		case'b':
			sets.initControlDependencies();
			sets.findBasis();
			break;
		default:
			break;
		}

		cout << menu;
		cin >> choice;

	}


	return 0;
}