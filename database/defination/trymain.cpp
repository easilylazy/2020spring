#define _CRT_SECURE_NO_WARNINGS
#include "closure.h"


void defaultSetting(form& de)
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
	de.setNum(3);
	for (int i = 0; i < dependenciesNum; i++)
	{
		de.setDependencies(leftDependencies[i], rightDependencies[i]);
	}


}


int main(void)
{
	form te(3);

	//设置为默认情况
	defaultSetting(te);

	string menu = "********************MENU********************\n"\
		"i.initAttributes\ta.addDependency\ts.setClosure\nf.findClosure\t"\
		"p.printInfo\tb.basisDependencies\nq.quit\n"\
		"********************************************\n";
	char choice;

	cout << menu;
	cin >> choice;

	while (choice != 'q')
	{
		switch (choice)
		{
		case'i':
			te.setAttributes();
			break;
		case'a':
			te.addDependency();
			break;
		case's':
			te.setClosure();
			break;
		case'f':
			te.findClosure();
			break;
		case'p':
			te.print();
			break;
		case'b':
			te.findBasis();
			break;
		default:
			break;
		}

		cout << menu;
		cin >> choice;

	}


	return 0;
}