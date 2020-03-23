#define _CRT_SECURE_NO_WARNINGS
#include "closure.h"
#include "example.h"

string language = "CN";
bool displayTips = true;
int main(void)
{
	//ʵ������
	form sets;
	string info = "********************INFO********************\n"\
		"Hello��Welcome to this test program for database course!\n"\
		"The program is targeted at:\n"\
		"\t1.find closure\n"\
		"\t2.find minimal dependencies\n"\
		"source code can be obtained from GitHub��https://github.com/easilylazy/2020spring/tree/master/database/defination \n"\
		"detailed idea can refer to blog��https://blog.csdn.net/cascara/article/details/104968626 \n"\
		"author: Li Ziyi   \nCode is licensed under the MIT License \n"\
		"********************************************\n";

	string infoCN = "********************��Ϣ********************\n"\
		"��ã���ӭʹ�ñ����ݿ���Գ���\n"\
		"���������ʵ�֣�\n"\
		"\t1.Ѱ�����Ահ�\n"\
		"\t2.Ѱ����С����������\n"\
		"Դ�����GitHub��վ��https://github.com/easilylazy/2020spring/tree/master/database/defination \n"\
		"����˼·�ɲο����ͣ�https://blog.csdn.net/cascara/article/details/104968626 \n"\
		"���ߣ������� \n�������� MIT License ����� \n"\
		"********************************************\n";

	string menu = "********************MENU********************\n"\
		"i.initAttributes\ta.addDependency\ts.setClosure\nf.findClosure\t"\
		"p.printInfo\tb.basisDependencies\nd.defaultExamples\nl.lessTips\tc.��������\tq.quit\n"\
		"********************************************\n";
	string menuCN = "********************Ŀ¼********************\n"\
		"i.��ʼ��\ta.��Ӻ�������\ts.�趨��ȡ�հ�������\nf.��ʼѰ�ұհ�\t"\
		"p.��ӡ������Ϣ\tb.��ʼѰ����С������\nd.����Ĭ������\nl.���ٵ���ʾ\tc.changeLanguage\tq.�˳�\n"\
		"********************************************\n";
	char choice;

	//��ӡ�˵�����ȡ����
	if (language == "EN")
	{
		cout << info;
		cout << menu;
		
	}
	if (language == "CN")
	{
		cout << infoCN;
		cout << menuCN;
	}
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
			sets.printInfo();
			break;
		case'p':
			sets.printInfo();
			break;
		case'b':
			sets.initControlDependencies();
			sets.findBasis();
			sets.printMinimaBases();
			sets.printFinalResult();
			break;
		case'c':
			language == "EN" ? language = "CN" : language = "EN";
		case'd':
			
			chooseDefault(sets);
			sets.printInfo();
			break;
		case'l':
			displayTips = false;
		default:
			break;
		}

		if (language == "EN")
		{
			cout << menu;
		}
		if (language == "CN")
		{
			cout << menuCN;
		}
		cin >> choice;

	}


	return 0;
}