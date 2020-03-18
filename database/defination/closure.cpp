#include"closure.h"
form::form()
{
	int num = 1;
	attributesNum = num;
	dependenciesNum = 0;
	
	//attributes = new int(num);
	initAttributes(num);
}
form::form(int num)
{
	attributesNum = num;
	dependenciesNum = 0;

	initAttributes(num);
}

void form::setAttributes()
{
	int num=0;

	cout << "How many attributes in total(1-10)?" << endl;
	cin >> num;

	while (num <= 0 || num > 10)
	{
		cout << "How many attributes in total(1-10)?" << endl;
		cin >> num;
	}

	setNum(num);
	
}
void form::setNum(int num)
{
	attributesNum = num;
	dependenciesNum = 0;
	initAttributes(num);
}


bool form::isValid(char &ch)
{
		//输入字母
	int ctoc = ch - 65;
	if (ctoc >= 0 && ctoc < attributesNum)
	{
		ch = ctoc;
		return true;
	}

		//输入数组索引值
	int ctoi = ch - 48;
	if (ctoi >= 0 && ctoi < attributesNum)
	{
		ch = ctoi;
		return true;
	}
	else
	{
		cout << ch << " is invalid" << endl;
		print();
		return false;
	}
		
}

void form::initAttributes(int num)
{

	for (int i = 0; i < num; i++)
	{
		attributes[i] = 1;
	}
}


void form::initClosure(int num)
{
	for (int i = 0; i < attributesNum; i++)
	{
		closure[i] = 0;
	}
}

void form::initDependencies(int index)
{
	for (int i = 0; i < attributesNum; i++)
	{
		leftDetermine[index][i] = 0;
		rightDetermine[index][i] = 0;
	}
}
void form::printAttributes(int* attributes,char choice)
{
	for (int i = 0; i < MAXSIZE; i++)
	{
		if (attributes[i] == 1)
		{
			if (choice == 's')
			{
				cout << char(i + 65);
			}
			else
				cout << i << ": " << char(i + 65) << endl;
		}
	}
}
void form::print()
{
	//sizeof(attributes)/ sizeof(int) 
	cout << "the sets has " << attributesNum << " attributes" << endl;

	for (int i = 0; i < attributesNum; i++)
	{
		cout << i << ": " << char(i+65)<<endl;
	}
	cout << "determination have " << dependenciesNum << " sets" << endl;

	for (int i = 0; i < dependenciesNum; i++)
	{
//if (leftDetermine[i][j] == 1)
			printAttributes(leftDetermine[i], 's');
			cout << "->";
			printAttributes(rightDetermine[i], 's');
			cout << endl;

	}

	cout << "closure: " << endl;
	for (int i = 0; i < attributesNum; i++)
	{

		if(closure[i]==1)
			cout << i << ": " << char(i + 65) << endl;
	}

	/*for (int i = 0; i < sizeof(attributes); i++)
	{
		cout << attributes[i] << endl;
	}*/
}
void form::printAttribute(int index)
{
	cout << char(index + 65);
}
int form::addSide(char& choice, int* determine)
{
	int ct = 0;

	cin >> choice;
	while (choice != 'q' && choice != 's')
	{
		if (isValid(choice))
		{

			if (determine[choice] != 1)
			{
				determine[choice] = 1;
				ct++;
			}
		}
		cin >> choice;

	}

	return ct;
}
void form::addDependency()
{
	initDependencies(dependenciesNum);
	char choice;
	

	cout << "enter attributes determine others" << tips << endl;

	int leftNum = addSide(choice, leftDetermine[dependenciesNum]);

	if (choice == 's' && leftNum > 0)
	{

		if (LESSINFO == false)
		{
			cout << "you add " << leftNum << " attributes" << endl;
			cout << "what you have typed is/are: " << endl;
			printAttributes(leftDetermine[dependenciesNum]);
		}	

		cout << "enter attributes determined by above" << tips << endl;

		int rightNum = addSide(choice, rightDetermine[dependenciesNum]);

		if (choice == 's' && rightNum > 0)
		{
			if (LESSINFO == false)
			{
				cout << "you add " << rightNum << " attributes" << endl;
				cout << "what you have typed is/are: " << endl;
				printAttributes(rightDetermine[dependenciesNum]);
			}		
			

			if (rightNum > 1)
			{
				split();//使用splitting rule(分解率)将右边转化为全为1项
			}

		}

	}

	if (choice == 'q')
	{
		return;
	}

	cout << "the total is: " << endl;
	printAttributes(leftDetermine[dependenciesNum], 's');
	cout << "->";
	printAttributes(rightDetermine[dependenciesNum], 's');
	cout << "\nDo you want to save" << tips << endl;
	cin >> choice;
	if (choice == 's')
	{
		//this->leftDetermine
		dependenciesNum++;
	}

}

void form::	setClosure()
{
	char choice;
	cout << "enter an attribut set" << tips << endl;

	initClosure(attributesNum);

	int initNum = addSide(choice, closure);

	if (choice == 's' && initNum > 0)
	{
		cout << "you choose " << initNum << " attributes" << endl;
		cout << "what you have typed is/are: " << endl;
		printAttributes(closure);
	}

}
void form::findClosure()
{
	bool isConsistent = true;
	for (int i = 0; i < dependenciesNum; i++)
	{
		isConsistent = true;
		for (int j = 0; j < attributesNum; j++)
		{
			if (leftDetermine[i][j] == 1 && closure[j] != 1)
			{
				isConsistent = false;
				break;
			}
			
		}
		if (isConsistent == true)
		{
			for (int j = 0; j < attributesNum; j++)
			{
				if (rightDetermine[i][j] == 1 && closure[j] != 1)
				{
					cout << "add ";
					printAttribute(j);
					cout << endl;
					closure[j] = 1;
					findClosure();
				}
			}
		}
		
	}
	return;
}