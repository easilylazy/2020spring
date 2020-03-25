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
//��ά
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
		tip = "���ж�������(��Χ��1-10)?";
		tip1 = "(��ʾ����һ��Ϊ a.��Ӻ����������ڹ������������ʱѡ�� p.��ӡ������Ϣ �����״̬";
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
//�ı�������ֵ�趨��siteΪ'l'ѡ��ı���ߵı������'r'�ı��ұ�������; i,j��ʾ�ı��i��ĵ�j������ֵΪvalue��0/1��
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

//��������ֱ�Ӹı�����ֵ����stateΪ-1���������������ı��state��
void form::setDependencies(int* leftDependency, int* rightDependency, int state)
{
	if (state == -1)
	{
		for (int i = 0; i < attributesNum; i++)
		{


			//ʹ�÷ֽ�
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
		tip = "��Ч";
		tip1 = "�������룺";
	}

#pragma endregion
	//��д��ĸ
	int ctoc = ch - 65;
	if (ctoc >= 0 && ctoc < attributesNum)
	{
		ch = ctoc;
		return true;
	}
	//Сд��ĸ
	ctoc = ch - 97;
	if (ctoc >= 0 && ctoc < attributesNum)
	{
		ch = ctoc;
		return true;
	}

	//������������ֵ
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
		tip = "��Ч";
		tip1 = "�������룺";
	}

#pragma endregion
	//������ĸ
	int ctoc = ch - 65;
	if (ctoc >= 0 && ctoc < attributesNum)
	{
		ch = ctoc;
		return true;
	}

	//������������ֵ
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
		controlDependencies[i] = 1;//��ʼ������
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
		tip = "�����Լ����� " + to_string(attributesNum) + " ������";
		tip1 = "������������ " + to_string(toOneDependenciesNum) + " ����������";
		tip2 = "��ȡ�հ�������ʾ�� ";

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
		cout << "��С�����������У� " << endl;
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
//������С����ĳbase
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
				//���
				if (maskAttributes[i][j] != -1 && toOneLeftDependencies[i][j] == 1)
				{
					//cout << char(j + 65);
					newBase.setLeftDependency(i, j);

				}
				
			}
			//->�ұ�
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
				//���
				if (maskAttributes[i][j] != -1 && toOneLeftDependencies[i][j] == 1)
				{
					//cout << char(j + 65);
					newBase.setLeftDependency(i, j);

				}				
			}
			//->�ұ�
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
		tip1 = "type: A->C��enter��";
		tip2 = tips;
		tip3 = "not Saved";
	}
	if (language == "CN")
	{
		tip = "���뺯������:";	
		tip1 = "�����ʽ��A->C��enter��";
		tip2 = tipsCN;
		tip3 = "δ����";
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
		cout << "������ҪѰ�ұհ������Լ�" << tipsCN << endl;
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
			cout << "��ѡ���� " << initNum << " ������" << endl;
			cout << "������: " << endl;
			tip1 = "(��ʾ: ѡ������ȡ�հ��ĳ�ʼ���Ժ���һ������Ϊ f.��ʼѰ�ұհ� )";

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
				cout << "����:";
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
		//����ĳ������ȥ��������
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
//����ĳɾȥ��index�����ĵ�mask����,�����������Դ���closure���ٱ���֮�����հ��ܷ񸲸�ɾ������
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
		
		tip = "***************��ʱ���*****************";
		tip1 = "***************��������*****************";

	}
#pragma endregion
	bool findIdentityBase;
	current.isValid = false;
	findIdentityBase = false;

	if (last.isValid == true)
	{

		//�Ƚ��Ƿ��������������г�Ա�������е�ĳһ�����������ҵ�
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

		tip = "***************���ս��*****************";
		tip1 = "---���ڴ洢�ռ����ޣ�ֻ��ӡ���ֽ��---";

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

				//�Ƚ��Ƿ��������������г�Ա�������е�ĳһ�����������ҵ�
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

//�ݹ麯��������֮ǰ�����ʼ��controlDependencies
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
		tip = "�� 1 ������ȥ�����ຯ����������:";
		tip1 = "�� 2 ������ȥ�������������Ҳ����������ԣ���:";
	}
	//��һ������ߵ����Խ��д���
#pragma endregion	
	
	//����ɾ��һ������X'->Y'��Ѱ�������������ܷ��Ƴ�Y'
	//���ܣ���ɱ�ɾ���������ܱ�ɾ��

	//��Ҫ��������ȡһ���������������attributes

	//closure   �������Ƿ���Y'
	bool basisFound = false;
	initbasisDependencies();

	for (int i = 0; i < toOneDependenciesNum; i++)
	{
		int targetValue = 0;

		//�����ڿ��Գ�ȥ��������

		if (controlDependencies[i] != 1)
		{
			continue;
		}
		//�����ȥ�������������
		basisDependencies[i] = 0;

		targetValue = getRightDependency(i);


		sendToClosure(i);//����ɾ������������ߵ�X'����closure
		findClosure(targetValue);//��Ŀ��ֵ���루meaningless��

		//�õ��ıհ��в���Y'
		if (closure[targetValue] != 1)
		{
			basisDependencies[i] = 1;//���������ɳ�ȥ
		}
		else
		{
			basisFound = true;
		}
	}

	if (basisFound == true)
	{
		//һ���ҵ�һ��������������С��
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
	//�����пɸı��ֵ���ݹ��ȡ�µĿ��ܣ�����return
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

	//Ѱ�ҳ�ȡĩλ ���һ��0���ֵ�λ��
	//��ĩλ��0����������������Ѱ����һλ0�������һ��0�����ڣ����˳����򣬷���false
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

	//��ĩλ��0��Ϊ-1
	controlDependencies[last0Site] = -1;

	//����-1��ĵĿ��Ʊ���Ϊ-1������1������ǰ���ֵ
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
			//��������ɾȥ
			if (index == i)
			{
				continue;
			}
		}
		//����ĳ������ȥ��������
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
//��Ҫ�ڱ�����ǰ��ʼ��maskAttributes
void form::secondProcess()
{
	// ����ȡ��һ������ҵ���basisDependency����˵�����
	// ��ɾȥһ�����Ժ�
		// ͨ��maskAttributes[][]ʵ��
		// ��maskAttributes[i][j] = -1���ɱ�ɾȥ��

		// ������Ա�ɾȥ����������հ�ʱ���ǣ�
		// ��maskAttributes[i][j] = 1�����ɱ�ɾȥ���������֤����
		// ��maskAttributes[i][j] = 0����ʼֵ��

	// ��ͨ��������������ʣ�µ������õ�������ԣ����ɾȥ

	for (int i = 0; i < toOneDependenciesNum; i++)
	{
		if (basisDependencies[i] == 1)
		{
			for (int j = 0; j < attributesNum; j++)
			{
				//ȷ����������δ�����δ�����̴���
				if (maskAttributes[i][j] != -1 && toOneLeftDependencies[i][j] == 1)
				{

					//closure Ҫ���趨Ϊ�������������������
					sendToClosure(i, j);
					//���д���
					findClosure('s', i);

					//�ж��Ƿ�õ�ɾȥ��j����
					if (closure[j] == 1)
					{
						maskAttributes[i][j] = -1; //���ҵ����ɱ�ɾȥ
					}
					else
					{
						maskAttributes[i][j] = 1; //���ҵ������ɱ�ɾȥ
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


	//������������ֵ
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
