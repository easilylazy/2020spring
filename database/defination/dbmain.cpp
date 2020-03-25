#define _CRT_SECURE_NO_WARNINGS
#include "closure.h"
#include "example.h"

string language = "CN";
bool displayTips = true;
bool hideProcess = true;
bool overFlow = false;
int main(void)
{







	//实例对象
	form sets;
	string info = "********************INFO********************\n"\
		"Hello！Welcome to this test program for database course!\n"\
		"The program is targeted at:\n"\
		"\t1.find closure\n"\
		"\t2.find minimal dependencies\n"\
		"source code can be obtained from GitHub：https://github.com/easilylazy/2020spring/tree/master/database/defination \n"\
		"detailed idea can refer to blog：https://blog.csdn.net/cascara/article/details/104968626 \n"\
		"author: Li Ziyi   \nCode is licensed under the MIT License \n"\
		"********************************************\n";

	string infoCN = "********************信息********************\n"\
		"你好！欢迎使用本数据库测试程序：\n"\
		"本程序可以实现：\n"\
		"\t1.寻找属性闭包\n"\
		"\t2.寻找最小函数依赖集\n"\
		"源代码见GitHub网站：https://github.com/easilylazy/2020spring/tree/master/database/defination \n"\
		"具体思路可参考博客：https://blog.csdn.net/cascara/article/details/104968626 \n"\
		"作者：李子怡 \n本程序在 MIT License 许可下 \n"\
		"********************************************\n";

	string menu = "********************MENU********************\n"\
		"i.initAttributes\ta.addDependency\ts.setClosure\nf.findClosure\t"\
		"p.printInfo\tb.basisDependencies\nd.defaultExamples\nl.lessTips\tc.更改语言\tq.quit\n"\
		"********************************************\n";
	string menuCN = "********************目录********************\n"\
		"i.初始化\ta.添加函数依赖\ts.设定求取闭包的属性\nf.开始寻找闭包\t"\
		"p.打印现有信息\tb.开始寻找最小依赖集\nd.几个默认例子\to.显示(隐藏)过程\nl.更少(多)的提示\tc.changeLanguage\tq.退出\n"\
		"********************************************\n";
	char choice;

	//打印菜单，读取输入
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
			//sets.printMinimaBases();
			sets.printFinalResult();	
			break;
		case'c':
			language == "EN" ? language = "CN" : language = "EN";
			break;
		case'd':			
			chooseDefault(sets);
			sets.printInfo();
			break;
		case'l':
			displayTips == false ? displayTips = true : displayTips  = false;
			break;
		case'o':
			hideProcess== false ? hideProcess = true : hideProcess = false;
			break;
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