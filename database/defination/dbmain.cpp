#define _CRT_SECURE_NO_WARNINGS
#include "closure.h"
#include "example.h"

int main(void)
{
	//ʵ������
	form sets;

	//����ΪĬ�����
	defaultSetting3(sets);

	
	string menu = "********************MENU********************\n"\
		"i.initAttributes\ta.addDependency\ts.setClosure\nf.findClosure\t"\
		"p.printInfo\tb.basisDependencies\nq.quit\n"\
		"********************************************\n";
	char choice;

	//��ӡ�˵�����ȡ����
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