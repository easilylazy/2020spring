#include"closure.h"
form::form()
{
	int num = 1;

	setNum(num);
}
form::form(int num)
{
	setNum(num);
}

void form::setAttributes()
{
	int num = 0;

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
	ownIsBasis = true;
	initAttributes();
	initClosure();
	initbasisDependencies();
	initControlDependencies();
}
void form::setDependenciesNum(int num)
{
	dependenciesNum = num;
}
//改变依赖的值设定，site为'l'选择改变左边的被依赖项，'r'改变右边依赖项; i,j表示改变第i项的第j个属性值为value（0/1）
void form::setDependency(char site, int i, int j, int value = 1)
{
	if (site == 'l')
	{
		leftDependencies[i][j] = value;
	}
	if (site == 'r')
	{
		rightDependencies[i][j] = value;
	}

}

//传入数组直接改变依赖值，若state为-1，新增依赖项，否则改变第state项
void form::setDependencies(int* leftDependency, int* rightDependency, int state)
{
	if (state == -1)
	{
		for (int i = 0; i < attributesNum; i++)
		{
			leftDependencies[dependenciesNum][i] = leftDependency[i];
			rightDependencies[dependenciesNum][i] = rightDependency[i];
		}
		dependenciesNum++;

	}
	else
	{
		for (int i = 0; i < attributesNum; i++)
		{
			leftDependencies[state][i] = leftDependency[i];
			rightDependencies[state][i] = rightDependency[i];
		}
	}
}

int form::getRightDependency(int index)
{
	for (int j = 0; j < attributesNum; j++)
	{
		if (rightDependencies[index][j] == 1)
		{
			return j;//目标值
		}
	}
	return -1;
}

bool form::isValid(char& ch)
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
		printInfo();
		return false;
	}

}

void form::initAttributes()
{

	for (int i = 0; i < attributesNum; i++)
	{
		attributes[i] = 1;
	}
}


void form::initClosure()
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
		leftDependencies[index][i] = 0;
		rightDependencies[index][i] = 0;
	}
}
void form::initbasisDependencies()
{
	for (int i = 0; i < dependenciesNum; i++)
	{
		basisDependencies[i] = 1;//初始都包括
	}
}
void form::initControlDependencies()
{
	for (int i = 0; i < dependenciesNum; i++)
	{
		controlDependencies[i] = 1;//初始都包括
	}
}
void form::initMaskAttributes()
{
	for (int i = 0; i < dependenciesNum; i++)
	{
		for (int j = 0; j < attributesNum; j++)
		{
			maskAttributes[i][j] = 0;
		}
	}
}
void form::printAttributes(int* attributes, char choice)
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
void form::printInfo()
{
	//sizeof(attributes)/ sizeof(int) 
	cout << "the sets has " << attributesNum << " attributes" << endl;

	for (int i = 0; i < attributesNum; i++)
	{
		cout << i << ": " << char(i + 65) << endl;
	}
	cout << "determination have " << dependenciesNum << " sets" << endl;

	for (int i = 0; i < dependenciesNum; i++)
	{
		//if (leftDependencies[i][j] == 1)
		printAttributes(leftDependencies[i], 's');
		cout << "->";
		printAttributes(rightDependencies[i], 's');
		cout << endl;

	}

	cout << "closure: " << endl;
	for (int i = 0; i < attributesNum; i++)
	{

		if (closure[i] == 1)
			cout << i << ": " << char(i + 65) << endl;
	}

	printBasis();
	/*for (int i = 0; i < sizeof(attributes); i++)
	{
		cout << attributes[i] << endl;
	}*/
}
void form::printBasis()
{
	cout << "basis: " << endl;
	for (int i = 0; i < dependenciesNum; i++)
	{
		if (basisDependencies[i] == 1)
		{
			//printAttributes(leftDependencies[i], 's');
			for (int j = 0; j < attributesNum; j++)
			{
				if (maskAttributes[i][j] != -1 && leftDependencies[i][j] == 1)
				{
					cout << char(j + 65);
				}
			}
			cout << "->";
			printAttributes(rightDependencies[i], 's');
			cout << endl;
		}
	}
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

	int leftNum = addSide(choice, leftDependencies[dependenciesNum]);

	if (choice == 's' && leftNum > 0)
	{

		if (LESSINFO == false)
		{
			cout << "you add " << leftNum << " attributes" << endl;
			cout << "what you have typed is/are: " << endl;
			printAttributes(leftDependencies[dependenciesNum]);
		}

		cout << "enter attributes depending on above" << tips << endl;

		int rightNum = addSide(choice, rightDependencies[dependenciesNum]);

		if (choice == 's' && rightNum > 0)
		{
			if (LESSINFO == false)
			{
				cout << "you add " << rightNum << " attributes" << endl;
				cout << "what you have typed is/are: " << endl;
				printAttributes(rightDependencies[dependenciesNum]);
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
	printAttributes(leftDependencies[dependenciesNum], 's');
	cout << "->";
	printAttributes(rightDependencies[dependenciesNum], 's');
	cout << "\nDo you want to save" << tips << endl;
	cin >> choice;
	if (choice == 's')
	{
		//this->leftDependencies
		dependenciesNum++;
	}

}

void form::setClosure()
{
	char choice;
	cout << "enter an attribut set" << tips << endl;

	initClosure();

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
			if (leftDependencies[i][j] == 1 && closure[j] != 1)
			{
				isConsistent = false;
				break;
			}

		}
		if (isConsistent == true)
		{
			for (int j = 0; j < attributesNum; j++)
			{
				if (rightDependencies[i][j] == 1 && closure[j] != 1)
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


void form::findClosure(int index)
{
	bool isConsistent = true;
	for (int i = 0; i < dependenciesNum; i++)
	{
		//若将某依赖除去，则跳过
		if (basisDependencies[i] != 1)
		{
			continue;
		}


		isConsistent = true;
		for (int j = 0; j < attributesNum; j++)
		{
			if (leftDependencies[i][j] == 1 && closure[j] != 1)
			{
				isConsistent = false;
				break;
			}

		}
		if (isConsistent == true)
		{
			for (int j = 0; j < attributesNum; j++)
			{
				if (rightDependencies[i][j] == 1 && closure[j] != 1)
				{
					//不打印过程
					/*cout << "add ";
					printAttribute(j);
					cout << endl;*/
					closure[j] = 1;
					findClosure(index);
				}
			}
		}
	}
	return;
}
void form::sendToClosure(int index)
{
	initClosure();

	for (int j = 0; j < attributesNum; j++)
	{
		if (leftDependencies[index][j] == 1)
		{
			closure[j] = 1;
		}
	}
}
//除了某删去第index依赖的第mask属性,将其他的属性传入closure，再便于之后计算闭包能否覆盖删除属性
void form::sendToClosure(int index, int mask)
{
	initClosure();



	for (int j = 0; j < attributesNum; j++)
	{

		if (j != mask && leftDependencies[index][j] == 1)
		{
			closure[j] = 1;
		}
	}

}
//递归函数，调用之前必须初始化controlDependencies
//initControlDependencies();
void form::findBasis()
{
	//依次删除一个依赖X'->Y'，寻找新依赖集中能否推出Y'
	//若能，则可被删除；否则不能被删除

	//需要函数：获取一个依赖集所有左边attributes

	//closure   输出结果是否含有Y'
	bool basisFound = false;
	initbasisDependencies();

	for (int i = 0; i < dependenciesNum; i++)
	{
		int targetValue = 0;

		//必须在可以除去的依赖中

		if (controlDependencies[i] != 1)
		{
			continue;
		}
		//假设除去该依赖，检查结果
		basisDependencies[i] = 0;

		targetValue = getRightDependency(i);


		sendToClosure(i);//将除删除的依赖的左边的X'传给closure
		findClosure(targetValue);//将目标值传入（meaningless）

		//得到的闭包中不含Y'
		if (closure[targetValue] != 1)
		{
			basisDependencies[i] = 1;//该依赖不可除去
		}
		else
		{
			basisFound = true;
		}
	}

	if (basisFound == true)
	{
		//一旦找到一个，自身不再是最小的
		ownIsBasis = false;
		cout << "\r";
		initMaskAttributes();
		cout << "after step 1:" << endl;
		printBasis();
		//进一步对左边的属性进行处理

		secondProcess();
		cout << "after step 2:" << endl;
		printBasis();
	}
	//若仍有可改变的值，递归获取新的可能，否则return
	if (changeControl() == true)
	{
		findBasis();
	}
	else
	{
		if (ownIsBasis == true)
		{
			initMaskAttributes();
			cout << "after step 1:" << endl;
			printBasis();
			//进一步对左边的属性进行处理
			secondProcess();
			cout << "after step 2:" << endl;
			printBasis();

		}
		return;
	}
}
bool form::changeControl()
{
	int last0Site = -1;

	//寻找除取末位 最后一个0出现的位置
	//若末位的0已是最后的属性，则寻找上一位0，如果上一个0不存在，则退出程序，返回false
	for (int i = 0; i < attributesNum - 1; i++)
	{
		if (i > last0Site && basisDependencies[i] == 0)
		{
			last0Site = i;
		}
	}

	if (last0Site == -1)
	{
		return false;
	}

	//将末位的0置为-1
	controlDependencies[last0Site] = -1;

	//将置-1后的的控制变量为-1的项置1，保留前面的值
	for (int i = 0; i < attributesNum; i++)
	{
		if (i > last0Site && controlDependencies[i] == -1)
		{
			controlDependencies[i] = 1;
		}
	}

	return true;
}


void form::findClosure(char choice, int index)
{
	bool isConsistent = true;
	for (int i = 0; i < dependenciesNum; i++)
	{
		if (choice == 's')
		{
			//将该依赖删去
			if (index == i)
			{
				continue;
			}
		}
		//若将某依赖除去，则跳过
		if (basisDependencies[i] != 1)
		{
			continue;
		}


		isConsistent = true;
		for (int j = 0; j < attributesNum; j++)
		{
			if (leftDependencies[i][j] == 1 && closure[j] != 1)
			{
				isConsistent = false;
				break;
			}

		}
		if (isConsistent == true)
		{
			for (int j = 0; j < attributesNum; j++)
			{
				if (rightDependencies[i][j] == 1 && closure[j] != 1)
				{
					//不打印过程
					/*cout << "add ";
					printAttribute(j);
					cout << endl;*/
					closure[j] = 1;
					findClosure(choice, index);
				}
			}
		}
	}
	return;
}
//需要在被调用前初始化maskAttributes
void form::secondProcess()
{
	// 依次取上一步完成找到的basisDependency的左端的属性
	// 若删去一个属性后
		// 通过maskAttributes[][]实现
		// 若maskAttributes[i][j] = -1（可被删去）

		// 则该属性被删去（不被计算闭包时考虑）
		// 若maskAttributes[i][j] = 1（不可被删去，被处理后证明）
		// 若maskAttributes[i][j] = 0（初始值）

	// 能通过除该依赖以外剩下的依赖得到这个属性，则可删去

	for (int i = 0; i < dependenciesNum; i++)
	{
		if (basisDependencies[i] == 1)
		{
			for (int j = 0; j < attributesNum; j++)
			{
				//确保该属性尚未被本次处理过程处理
				if (maskAttributes[i][j] != -1 && leftDependencies[i][j] == 1)
				{

					//closure 要被设定为除本依赖外的其他依赖
					sendToClosure(i, j);
					//进行处理
					findClosure('s', i);

					//判断是否得到删去的j属性
					if (closure[j] == 1)
					{
						maskAttributes[i][j] = -1; //能找到，可被删去
					}
					else
					{
						maskAttributes[i][j] = 1; //能找到，不可被删去
					}
				}
			}
		}
	}

}

