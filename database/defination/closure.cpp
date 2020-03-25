#include"closure.h"
form::form()
{
	int num = 0;

	setNum(num);
}
form::form(int num)
{
	setNum(num);
}
void initArray(int* array, int length, int initValue)
{
	for (int i = 0; i < length; i++)
	{
		*(array + i) = initValue;
	}
}
void printArray(int* array, int length)
{
	//int length = sizeof(array);
	for (int i = 0; i < length; i++)
	{
		cout << i << ": ";
		cout << *(array + i) << endl;
	}
}
//二维
void initArray2d(int* array, int M, int N, int initValue)
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			*(array + i * N + j) = initValue;
		}
	}
}
void printArray(int* array, int M, int N)
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << i << "," << j << ": " << *(array + i * N + j) << endl;
		}
	}
}

bool compareArray(int* firstArray, int* secondArray, int length)
	{
		for (int i = 0; i < length; i++)
		{
			if (firstArray[i] != secondArray[i])
			{
				return false;
			}
		}

		return true;
	}
void form::setAttributes()
{
	int num = 0;

#pragma region tips
	string tip, tip1;
	if (language == "EN")
	{
		tip = "How many attributes in total(range: 1-10)?";
		tip1 = "(hint: next step can be a. addDependencies, and you can choose p.printInfo anytime to check the state)";
	}

	if (language == "CN")
	{
		tip = "共有多少属性(范围：1-10)?";
		tip1 = "(提示：下一步为 a.添加函数依赖，在过程中你可以随时选择 p.打印现有信息 来检查状态";
	}
#pragma endregion

	cout << tip << endl;
	cin >> num;

	while (num <= 0 || num > 10)
	{
		cout << tip << endl;
		cin >> num;
	}
	setNum(num);

	if (displayTips == true)
	{
		cout << tip1 << endl;
	}


}
void form::setNum(int num)
{
	attributesNum = num;
	toOneDependenciesNum = 0;
	toOneDependenciesNum = 0;
	minimalBasesNum = 0;
	ownIsBasis = true;
	basisFound = false;
	closureFound = false;
	initAttributes();
	initClosure();
	initbasisDependencies();
	initControlDependencies();
}
void form::setDependenciesNum(int num)
{
	toOneDependenciesNum = num;
}
//改变依赖的值设定，site为'l'选择改变左边的被依赖项，'r'改变右边依赖项; i,j表示改变第i项的第j个属性值为value（0/1）
void form::setDependency(char site, int i, int j, int value = 1)
{
	if (site == 'l')
	{
		toOneLeftDependencies[i][j] = value;
	}
	if (site == 'r')
	{
		toOneRightDependencies[i] = value;
	}

}

//传入数组直接改变依赖值，若state为-1，新增依赖项，否则改变第state项
void form::setDependencies(int* leftDependency, int* rightDependency, int state)
{
	if (state == -1)
	{
		for (int i = 0; i < attributesNum; i++)
		{


			//使用分解
			if (rightDependency[i] == 1)
			{
				toOneRightDependencies[toOneDependenciesNum] = i;
				for (int j = 0; j < attributesNum; j++)
				{
					toOneLeftDependencies[toOneDependenciesNum][j] = leftDependency[j];
				}
				printAttributes(toOneLeftDependencies[toOneDependenciesNum], 's');
				cout << "->";
				printAttribute(i);
				cout << endl;
				toOneDependenciesNum++;
			}
		}

	}
	else
	{		
		for (int i = 0; i < attributesNum; i++)
		{
			if (rightDependency[i] == 1)
			{
				toOneRightDependencies[state] = i;
			}
			toOneLeftDependencies[state][i] = leftDependency[i];
			
		}
	}
}

int form::getRightDependency(int index)
{
	return toOneRightDependencies[index];
}
bool form::isValidNew(char& ch)
{
#pragma region tips
	string tip, tip1;
	if (language == "EN")
	{
		tip = " is invalid";
		tip1 = "Enter again: ";
	}

	if (language == "CN")
	{
		tip = "无效";
		tip1 = "重新输入：";
	}

#pragma endregion
	//大写字母
	int ctoc = ch - 65;
	if (ctoc >= 0 && ctoc < attributesNum)
	{
		ch = ctoc;
		return true;
	}
	//小写字母
	ctoc = ch - 97;
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

		cout << ch << tip << endl;
		printInfo();
		cout << tip1 << endl;

		return false;
	}

}
bool form::isValid(char& ch)
{
#pragma region tips
	string tip, tip1;
	if (language == "EN")
	{
		tip = " is invalid";
		tip1 = "Enter again: ";
	}

	if (language == "CN")
	{
		tip = "无效";
		tip1 = "重新输入：";
	}

#pragma endregion
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
		cout << ch << tip << endl;
		printInfo();
		cout << tip1 << endl;

		return false;
	}

}

void form::initAttributes()
{
	initArray(attributes, attributesNum, 1);
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
		toOneLeftDependencies[index][i] = 0;
		toOneRightDependencies[index] = -1;
	}
}
void form::initMinimalBases()
{
	minimalBasesNum = 0;
	current.isValid = false;
	last.isValid = false;
}
void form::initbasisDependencies()
{
	initArray(basisDependencies, toOneDependenciesNum, 1);
}
void form::initControlDependencies()
{
	for (int i = 0; i < toOneDependenciesNum; i++)
	{
		controlDependencies[i] = 1;//初始都包括
	}
}
void form::initMaskAttributes()
{
	for (int i = 0; i < toOneDependenciesNum; i++)
	{
		for (int j = 0; j < attributesNum; j++)
		{
			maskAttributes[i][j] = 0;
		}
	}
}
void form::printAttributes(int* attributes, char choice)
{
	for (int i = 0; i < attributesNum; i++)
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
void form::printMinimaBases()
{
	//minimalBasesNum = 3;

	for (int i = 0; i < minimalBasesNum; i++)
	{
		cout << "***********************************" << endl;
		if (minimalBases[i].isValid == true)
			minimalBases[i].printResult();
	}
}
void form::printMinimaBases(minimalBase base)
{
	for (int i = 0; i < minimalBasesNum; i++)
	{
		cout << "***********************************" << endl;
		if (base.isValid == true)
			base.printResult();
	}
}
bool form::compare(minimalBase current, minimalBase exist)
{

	bool findIdentityDependency;
	for (int i = 0; i < exist.getDependenciesNum(); i++)
	{
		if (exist.isNumValid(exist.rightDependencies[i]))
		{
			findIdentityDependency = false;

			for (int j = 0; j < current.getDependenciesNum(); j++)
			{
				
					if (exist.rightDependencies[i] == current.rightDependencies[j]
						&& (compareArray(exist.leftDependencies[i], current.leftDependencies[j], current.attributesNum)))
					{
						findIdentityDependency = true;
					}
				
			}

			if (findIdentityDependency == false)
			{
				return false;
			}
		
		}
	}
	return true;
}
void form::printInfo()
{
	cout << "****************INFO*******************" << endl;
#pragma region tips

	string tip, tip1, tip2;
	if (language == "EN")
	{
		tip = "the sets has " + to_string(attributesNum) + " attributes";
		tip1 = "dependencies have " + to_string(toOneDependenciesNum) + " sets";
		tip2 = "closures are as follows: ";


	}
	if (language == "CN")
	{
		tip = "此属性集包含 " + to_string(attributesNum) + " 个属性";
		tip1 = "此依赖集包含 " + to_string(toOneDependenciesNum) + " 个函数依赖";
		tip2 = "求取闭包如下所示： ";

	}
#pragma endregion

	cout << tip << endl;
	for (int i = 0; i < attributesNum; i++)
	{
		cout << i << ": " << char(i + 65) << endl;
	}
	cout << tip1 << endl;

	for (int i = 0; i < toOneDependenciesNum; i++)
	{
		//if (toOneLeftDependencies[i][j] == 1)
		printAttributes(toOneLeftDependencies[i], 's');
		cout << "->";
		printAttribute(toOneRightDependencies[i]);
		cout << endl;

	}



	if (closureFound == true)
	{
		cout << tip2 << endl;
		for (int i = 0; i < attributesNum; i++)
		{

			if (closure[i] == 1)
				cout << i << ": " << char(i + 65) << endl;
		}
	}

	if (basisFound == true)
	{
		initControlDependencies();
		printFinalResult();
	}

	cout << "***********************************" << endl;
}
void form::printBasis()
{
#pragma region tips
	if (language == "EN")
	{
		cout << "basis: " << endl;
	}
	if (language == "CN")
	{
		cout << "最小函数依赖集有： " << endl;
	}
#pragma endregion


	for (int i = 0; i < toOneDependenciesNum; i++)
	{
		if (basisDependencies[i] == 1)
		{
			//printAttributes(toOneLeftDependencies[i], 's');
			for (int j = 0; j < attributesNum; j++)
			{
				if (maskAttributes[i][j] != -1 && toOneLeftDependencies[i][j] == 1)
				{
					cout << char(j + 65);
				}
			}
			cout << "->";
			printAttribute(toOneRightDependencies[i]);
			cout << endl;
		}
	}
}
//保存最小基至某base
void form::saveBasis(minimalBase& saveTo)
{
	basisFound = true;
	minimalBase newBase;// = minimalBases[minimalBasesNum];

	newBase.setAttributesNum(attributesNum);
	newBase.setDependenciesNum(toOneDependenciesNum);

	//cout << "basis: " << endl;
	for (int i = 0; i < toOneDependenciesNum; i++)
	{
		if (basisDependencies[i] == 1)
		{

			for (int j = 0; j < attributesNum; j++)
			{
				//左边
				if (maskAttributes[i][j] != -1 && toOneLeftDependencies[i][j] == 1)
				{
					//cout << char(j + 65);
					newBase.setLeftDependency(i, j);

				}
				
			}
			//->右边
			newBase.setRightDependency(i, toOneRightDependencies[i]);
			

		}
	}
	saveTo = newBase;
	saveTo.isValid = true;
}
bool form::saveBasis()
{
	basisFound = true;
	minimalBase newBase;// = minimalBases[minimalBasesNum];

	newBase.setAttributesNum(attributesNum);
	newBase.setDependenciesNum(toOneDependenciesNum);

	//cout << "basis: " << endl;
	for (int i = 0; i < toOneDependenciesNum; i++)
	{
		if (basisDependencies[i] == 1)
		{

			for (int j = 0; j < attributesNum; j++)
			{
				//左边
				if (maskAttributes[i][j] != -1 && toOneLeftDependencies[i][j] == 1)
				{
					//cout << char(j + 65);
					newBase.setLeftDependency(i, j);

				}				
			}
			//->右边
			newBase.setRightDependency(i, toOneRightDependencies[i]);

		}
	}
	minimalBases[minimalBasesNum] = newBase;
	minimalBasesNum++;
	if (minimalBasesNum >= BASESMAXNUM)
	{
		cout << "limited storage" << endl;
		return false;
	}
	return true;
	
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
#pragma region tips

	string tip, tip1, tip2, tip3;
	if (language == "EN")
	{
		tip = "enter attributes determine others";
		tip1 = "type: A->C【enter】";
		tip2 = tips;
		tip3 = "not Saved";
	}
	if (language == "CN")
	{
		tip = "输入函数依赖:";	
		tip1 = "输入格式：A->C【enter】";
		tip2 = tipsCN;
		tip3 = "未保存";
	}


#pragma endregion
	initDependencies(toOneDependenciesNum);
	initMinimalBases();

	string input;
	string left, right;

	int leftArray[MAXSIZE], rightArray[MAXSIZE];

	cout << tip << endl;
	if (displayTips == true)
	{
		cout << tip1 << endl;
	}
	cin >> input;
	int n;
	bool validInput = true;
	char choice;
	if ((n = input.find("->")) != string::npos)
	{
		left = input.substr(0, n);		
		right = input.substr(n + 2);
	}
	else if ((n = input.find("-")) != string::npos)
	{
		left = input.substr(0, n);
		right = input.substr(n + 1);
	}
	else
	{
		validInput = false;
	}
	int leftNum = left.length();
	int rightNum = right.length();

	if (leftNum > 0 && rightNum > 0)
	{

		initArray(leftArray, attributesNum);
		initArray(rightArray, attributesNum);
		
		for (int i = 0; i < leftNum; i++)
		{
			if (isValidNew(left[i]))
			{
				leftArray[left[i]] = 1;
			}
			else
			{
				validInput = false;
			}
		}		
		for (int i = 0; i < rightNum; i++)
		{
			if (isValidNew(right[i]))
			{
				rightArray[right[i]] = 1;
			}
			else
			{
				validInput = false;
			}
		}
	}
	else
	{
		validInput = false;
	}


	if (validInput == true)
	{
		cout << tip2 << endl;
		cin >> choice;


		if (choice == 's'|| choice == 'S')
		{
			setDependencies(leftArray, rightArray, -1);			
		}		
		else
		{
			cout << tip3 << endl;
		}
	}
	return ;
}

void form::setClosure()
{
	closureFound = false;
	char choice;
#pragma region tips
	if (language == "EN")
	{
		cout << "enter an attribut set" << tips << endl;
	}
	if (language == "CN")
	{
		cout << "输入需要寻找闭包的属性集" << tipsCN << endl;
	}
#pragma endregion



	initClosure();

	int initNum = addSide(choice, closure);

	if (choice == 's' && initNum > 0)
	{
#pragma region tips
		string tip1;
		if (language == "EN")
		{
			cout << "you choose " << initNum << " attributes" << endl;
			cout << "what you have typed is/are: " << endl;
			tip1 = "(hint: when you choose all of the attributes, next step can be f.findClosure )";
		}
		if (language == "CN")
		{
			cout << "你选择了 " << initNum << " 个属性" << endl;
			cout << "它们是: " << endl;
			tip1 = "(提示: 选择完求取闭包的初始属性后，下一步可以为 f.开始寻找闭包 )";

		}
#pragma endregion

		printAttributes(closure);
		if (displayTips == true)
		{
			cout << tip1 << endl;
		}

	}

}
void form::findClosure()
{
	closureFound = true;
	bool isConsistent = true;
	for (int i = 0; i < toOneDependenciesNum; i++)
	{
		isConsistent = true;
		for (int j = 0; j < attributesNum; j++)
		{
			if (toOneLeftDependencies[i][j] == 1 && closure[j] != 1)
			{
				isConsistent = false;
				break;
			}

		}
		if (isConsistent == true
			&& closure[toOneRightDependencies[i]] != 1)
		{
			if (language == "EN")
			{
				cout << "add:";
			}
			if (language == "CN")
			{
				cout << "新增:";
			}

			printAttribute(toOneRightDependencies[i]);
			cout << endl;
			closure[toOneRightDependencies[i]] = 1;
			findClosure();

		}
	}
	return;
}


void form::findClosure(int index)
{
	bool isConsistent = true;
	for (int i = 0; i < toOneDependenciesNum; i++)
	{
		//若将某依赖除去，则跳过
		if (basisDependencies[i] != 1)
		{
			continue;
		}


		isConsistent = true;
		for (int j = 0; j < attributesNum; j++)
		{
			if (toOneLeftDependencies[i][j] == 1 && closure[j] != 1)
			{
				isConsistent = false;
				break;
			}

		}
		if (isConsistent == true
			&& closure[toOneRightDependencies[i]] != 1)
		{	
			
			closure[toOneRightDependencies[i]] = 1;
			findClosure(index);		
			
		}
	}
	return;
}
void form::sendToClosure(int index)
{
	initClosure();

	for (int j = 0; j < attributesNum; j++)
	{
		if (toOneLeftDependencies[index][j] == 1)
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

		if (j != mask && toOneLeftDependencies[index][j] == 1)
		{
			closure[j] = 1;
		}
	}

}
bool form::printFinalResult(minimalBase& current)
{

#pragma region tips

	string tip,tip1;
	if (language == "EN")
	{
		tip= "***************PERMANENT RESULT*****************";
		tip1 = "***************OVERFLOW!*****************";

	}
	if (language == "CN")
	{
		
		tip = "***************暂时结果*****************";
		tip1 = "***************结果溢出！*****************";

	}
#pragma endregion
	bool findIdentityBase;
	current.isValid = false;
	findIdentityBase = false;

	if (last.isValid == true)
	{

		//比较是否新增的依赖集中成员包括已有的某一个依赖集中找到
		if (compare(current, last) == true)
		{
			findIdentityBase = true;
		}
	}

	if (findIdentityBase != true)
	{
		current.isValid = true;
		if (hideProcess == false)
		{
			cout << tip << endl;
			current.printDependencies();
		}		
		minimalBases[minimalBasesNum] = current;
		minimalBasesNum++;
		if (minimalBasesNum >= BASESMAXNUM)
		{
			cout << tip1 << endl;
			overFlow = true;
			return false;
		}
		last = current;
	}
	return true;
	
}
void form::printFinalResult()
{
#pragma region tips
	string tip, tip1;
	if (language == "EN")
	{
		tip = "***************FINAL RESULT*****************";
		tip1 = "---The result is incompelete for the limited storage---";

	}
	if (language == "CN")
	{

		tip = "***************最终结果*****************";
		tip1 = "---由于存储空间有限，只打印部分结果---";

	}
#pragma endregion
	int ct = 0;
	bool findIdentityBase;

	minimalBase current, exist;
	cout << tip << endl;
	for (int i = 0; i < minimalBasesNum; i++)
	{
		current.isValid = false;
		current = minimalBases[i];
		findIdentityBase = false;
		for (int j = 0; j < i; j++)
		{
			exist = minimalBases[j];
			if (exist.isValid == true)
			{

				//比较是否新增的依赖集中成员包括已有的某一个依赖集中找到
				if (compare(current, exist) == true)
				{
					findIdentityBase = true;
				}
			}
		}
		if (findIdentityBase != true)
		{
			ct++;
			cout << "***************" << ct << "*****************" << endl;
			current.isValid = true;
			current.printDependencies();
		}
	}

	if (overFlow == true)
	{
		cout <<tip1 << endl;
	}
}

//递归函数，调用之前必须初始化controlDependencies
//initControlDependencies();
bool form::findBasis()
{
#pragma region tips
	string tip, tip1, tip2;
	if (language == "EN")
	{
		tip = "after step 1:";
		tip1 = "after step 2:";
	}

	if (language == "CN")
	{
		tip = "第 1 步处理（去除冗余函数依赖）后:";
		tip1 = "第 2 步处理（去除函数依赖中右部的冗余属性）后:";
	}
	//进一步对左边的属性进行处理
#pragma endregion	
	
	//依次删除一个依赖X'->Y'，寻找新依赖集中能否推出Y'
	//若能，则可被删除；否则不能被删除

	//需要函数：获取一个依赖集所有左边attributes

	//closure   输出结果是否含有Y'
	bool basisFound = false;
	initbasisDependencies();

	for (int i = 0; i < toOneDependenciesNum; i++)
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

		
		if (hideProcess == false)
		{
			cout << tip << endl;
			printBasis();
			secondProcess();
			cout << tip1 << endl;
			printBasis();
		}
		else
		{
			secondProcess();
		}
		saveBasis(current);
		current.printResult();
		
		if (printFinalResult(current) == false)
		{
			return false;
		}
		
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
			basisFound = true;
			initMaskAttributes();

			if (hideProcess == false)
			{
				cout << tip << endl;
				printBasis();
				secondProcess();
				cout << tip1 << endl;
				printBasis();
			}
			else
			{
				secondProcess();
			}
			saveBasis(current);
			current.printResult();

			if (printFinalResult(current) == false)
			{
				return false;
			}
		}
		return true;
	}
}
bool form::changeControl()
{
	int last0Site = -1;

	//寻找除取末位 最后一个0出现的位置
	//若末位的0已是最后的依赖，则寻找上一位0，如果上一个0不存在，则退出程序，返回false
	for (int i = 0; i < toOneDependenciesNum - 1; i++)
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
	for (int i = 0; i < toOneDependenciesNum; i++)
	{
		if (i > last0Site && controlDependencies[i] !=1 )
		{
			controlDependencies[i] = 1;
		}
	}

	return true;
}


void form::findClosure(char choice, int index)
{
	bool isConsistent = true;
	for (int i = 0; i < toOneDependenciesNum; i++)
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
			if (toOneLeftDependencies[i][j] == 1 && closure[j] != 1)
			{
				isConsistent = false;
				break;
			}

		}

		if (isConsistent == true
			&& closure[toOneRightDependencies[i]] != 1)
		{

			closure[toOneRightDependencies[i]] = 1;
			findClosure(choice, index);

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

	for (int i = 0; i < toOneDependenciesNum; i++)
	{
		if (basisDependencies[i] == 1)
		{
			for (int j = 0; j < attributesNum; j++)
			{
				//确保该属性尚未被本次处理过程处理
				if (maskAttributes[i][j] != -1 && toOneLeftDependencies[i][j] == 1)
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

void minimalBase::printDependencies()
{
	for (int i = 0; i < dependenciesNum; i++)
	{
		int rightValue = rightDependencies[i];

		if (isNumValid(rightValue))
		{
			printAttributes(leftDependencies[i], 's');
			cout << "->";
			cout << char(rightValue + 65) << endl;
		}

	}
}
void minimalBase::printAttributes(int* attributes, char choice)
{
	for (int i = 0; i < attributesNum; i++)
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
bool minimalBase::isNumValid(int value)
{


	//输入数组索引值
	int ctoi = value;
	if (ctoi >= 0 && ctoi < attributesNum)
	{
		return true;
	}
	else
	{
		return false;
	}

}
