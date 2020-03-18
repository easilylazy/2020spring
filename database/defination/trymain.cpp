#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<time.h>
#include<iostream>
#include "closure.h"

using namespace std;
int main(void)
{	
	form te(5);
	string menu = "********************MENU********************\n"\
		"i.initAttributes\ta.addDetermine\ts.setClosure\nf.findClosure\t"\
		"p.printInfo\tq.quit\n"\
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
		default:
			break;
		}

		cout << menu;
		cin >> choice;

	}


	return 0;
	
}
