#include "example.h"

void chooseDefault(form& sets)
{

	int chooseExample = 0;

	string exampleTip = "Which example do you want to test? (range: 0-3)";
	string exampleTipCN = "你想测试哪个例子? (范围: 0-3)";

	if (language == "EN")
	{
		cout << exampleTip;
	}
	if (language == "CN")
	{
		cout << exampleTipCN;
	}
	cin >> chooseExample;

	switch (chooseExample)
	{
	case 0:
		defaultSetting(sets);
		break;
	case 1:
		defaultSetting1(sets);
		break;
	case  2:
		defaultSetting2(sets);
		break;
	case  3:
		defaultSetting3(sets);
		break;
	default:
		cout << "0 or 1 or 2 or 3" << endl;
		break;
	}
}



//PPT上例子
void defaultSetting(form& sets)
{
#pragma region tips
	string tip;
	if (language == "EN")
	{
		tip = "this example was DIY";
	}
	if (language == "CN")
	{
		tip = "本例来源：自设";
	}
	cout << tip << endl;
#pragma endregion

	int attributesNum = 4;//A,B,C,D
	int dependenciesNum = 12;
	int leftDependencies[12][4] = {
		{1,0,0,0},{1,0,0,0},{1,0,0,0},    //A
		//{1,1,0},{1,1,0},    //AB
		{0,1,0,0},{0,1,0,0},{0,1,0,0},	//B
		{0,0,1,0},{0,0,1,0}	,{0,0,1,0}	,	//C
		{0,0,0,1},{0,0,0,1},{0,0,0,1}		//D
	};
	int rightDependencies[12][4] = {
		{0,1,0,0},{0,0,1,0},{0,0,0,1},    //A->B, A->C,	A->D	
		{1,0,0,0},{0,0,1,0},{0,0,0,1},	//B->A, B->C, B->D
		{1,0,0,0},{0,1,0,0}	,{0,0,0,1},	//C->A, C->B,C->D
		{1,0,0,0},{0,1,0,0}	,{0,0,1,0}	//D->A, D->B, D->C

	};
	sets.setNum(4);
	for (int i = 0; i < dependenciesNum; i++)
	{
		sets.setDependencies(leftDependencies[i], rightDependencies[i]);
	}
}
void defaultSetting1(form& sets)
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
#pragma region tips
	string tip;
	if (language == "EN")
	{
		tip = "this example was taken from website: https://blog.csdn.net/Game_Zmh/article/details/88061628";
	}
	if (language == "CN")
	{
		tip = "本例来源：https://blog.csdn.net/Game_Zmh/article/details/88061628";
	}
	cout << tip << endl;
#pragma endregion

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
#pragma region tips
	string tip;
	if (language == "EN")
	{
		tip = "this example was taken from website: https://www.cnblogs.com/wangyige/p/6786047.html";
	}
	if (language == "CN")
	{
		tip = "本例来源：https://www.cnblogs.com/wangyige/p/6786047.html";
	}
	cout << tip << endl;
#pragma endregion
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
