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
	dependenciesNum = 0;
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
	dependenciesNum = num;
}
//�ı�������ֵ�趨��siteΪ'l'ѡ��ı���ߵı������'r'�ı��ұ�������; i,j��ʾ�ı��i��ĵ�j������ֵΪvalue��0/1��
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

//��������ֱ�Ӹı�����ֵ����stateΪ-1���������������ı��state��
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
			return j;//Ŀ��ֵ
		}
	}
	return -1;
}

bool form::isValid(char& ch)
{
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
#pragma region tips
		string tip;
		if (language == "EN")
		{
			tip = " is invalid";
		}

		if (language == "CN")
		{
			tip = "��Ч";
		}
		cout << ch << tip << endl;
		printInfo();
		if (language == "EN")
		{
			tip = "Enter again: ";
		}

		if (language == "CN")
		{
			tip = "�������룺";
		}
		cout << tip << endl;
#pragma endregion


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
		leftDependencies[index][i] = 0;
		rightDependencies[index][i] = 0;
	}
}
void form::initbasisDependencies()
{
	initArray(basisDependencies, dependenciesNum, 1);
}
void form::initControlDependencies()
{
	for (int i = 0; i < dependenciesNum; i++)
	{
		controlDependencies[i] = 1;//��ʼ������
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
void form::printInfo()
{
	cout << "****************INFO*******************" << endl;
#pragma region tips

	string tip, tip1, tip2;
	if (language == "EN")
	{
		tip = "the sets has " + to_string(attributesNum) + " attributes";
		tip1 = "dependencies have " + to_string(dependenciesNum) + " sets";
		tip2 = "closures are as follows: ";


	}
	if (language == "CN")
	{
		tip = "�����Լ����� " + to_string(attributesNum) + " ������";
		tip1 = "������������ " + to_string(dependenciesNum) + " ����������";
		tip2 = "��ȡ�հ�������ʾ�� ";

	}
#pragma endregion

	cout << tip << endl;
	for (int i = 0; i < attributesNum; i++)
	{
		cout << i << ": " << char(i + 65) << endl;
	}
	cout << tip1 << endl;

	for (int i = 0; i < dependenciesNum; i++)
	{
		//if (leftDependencies[i][j] == 1)
		printAttributes(leftDependencies[i], 's');
		cout << "->";
		printAttributes(rightDependencies[i], 's');
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
		printBasis();
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


void form::saveBasis()
{
	basisFound = true;
	minimalBase newBase;// = minimalBases[minimalBasesNum];

	newBase.setAttributesNum(attributesNum);
	newBase.setDependenciesNum(dependenciesNum);

	//cout << "basis: " << endl;
	for (int i = 0; i < dependenciesNum; i++)
	{
		if (basisDependencies[i] == 1)
		{

			for (int j = 0; j < attributesNum; j++)
			{
				//���
				if (maskAttributes[i][j] != -1 && leftDependencies[i][j] == 1)
				{
					//cout << char(j + 65);
					newBase.setLeftDependency(i, j);

				}
				//->�ұ�
				if (rightDependencies[i][j] == 1)
				{
					//cout << char(j + 65);

					newBase.setRightDependency(i, j);
				}
			}

		}
	}
	minimalBases[minimalBasesNum] = newBase;
	minimalBasesNum++;
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

#pragma region tips
	if (language == "EN")
	{
		cout << "enter attributes determine others" << tips << endl;
	}
	if (language == "CN")
	{
		cout << "���뺯�������󲿵ĸ������ԣ����뵥���������ƣ�����س�����������һ����\nȫ���������" << tipsCN << endl;
	}

	if (LESSINFO != true)
	{
		if (language == "EN")
		{
			cout << "type: A��enter��C��enter��" << tips << endl;

		}
		if (language == "CN")
		{
			cout << "�����ʽ��A��enter��C��enter��" << tipsCN << endl;
		}
	}

#pragma endregion



	int leftNum = addSide(choice, leftDependencies[dependenciesNum]);

	if (choice == 's' && leftNum > 0)
	{

		if (LESSINFO == false)
		{
#pragma region tips
			if (language == "EN")
			{
				cout << "you add " << leftNum << " attributes" << endl;
				cout << "what you have typed is/are: " << endl;
			}
			if (language == "CN")
			{
				cout << "�������� " << leftNum << " ������" << endl;
				cout << "������: " << endl;
			}
#pragma endregion
			printAttributes(leftDependencies[dependenciesNum]);
		}
#pragma region tips
		if (language == "EN")
		{
			cout << "enter attributes depending on above" << tips << endl;
		}
		if (language == "CN")
		{
			cout << "�����������������Եĵ������ԣ�ʹ�÷ֽⶨ�ɣ�" << tipsCN << endl;
		}
#pragma endregion


		int rightNum = addSide(choice, rightDependencies[dependenciesNum]);

		if (choice == 's' && rightNum > 0)
		{
			if (LESSINFO == false)
			{

				printAttributes(rightDependencies[dependenciesNum]);
			}


			if (rightNum > 1)
			{
				split();//ʹ��splitting rule(�ֽ���)���ұ�ת��ΪȫΪ1��
			}

		}

	}

	if (choice == 'q')
	{
		return;
	}
#pragma region tips
	string tip2, tip3;
	if (language == "EN")
	{
		cout << "the total is: " << endl;
		printAttributes(leftDependencies[dependenciesNum], 's');
		cout << "->";
		printAttributes(rightDependencies[dependenciesNum], 's');
		cout << "\nDo you want to save" << tips << endl;
		tip2 = "��if you feel tired of adding dependencies, you can try d.defaultExamples to test first��";

		tip3 = "(hint: when you add all of the dependencies, next step can be s.setClosure, as the preparation for f.findClosure\n"\
			"or b.basisDependencies )";
	}
	if (language == "CN")
	{
		cout << "��������Ϊ: " << endl;
		printAttributes(leftDependencies[dependenciesNum], 's');
		cout << "->";
		printAttributes(rightDependencies[dependenciesNum], 's');
		cout << "\n�Ƿ񱣴棿���������� s��" << tipsCN << endl;
		tip2 = "������������뷱�������Գ��� d.����Ĭ������ �Ȳ���һ�£�";
		tip3 = "(��ʾ: ����꺯������������һ������Ϊ s.�趨��ȡ�հ�������, ��Ϊ f.��ʼѰ�ұհ� ��׼�� \n"\
			"������ b.��ʼѰ����С������ )";

	}
#pragma endregion

	cin >> choice;
	if (choice == 's')
	{
		//this->leftDependencies
		dependenciesNum++;
	}
	if (dependenciesNum == 1)
	{
		cout << tip2 << endl;
	}
	if (displayTips == true)
	{
		cout << tip3 << endl;
	}



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
					if (language == "EN")
					{
						cout << "add:";
					}
					if (language == "CN")
					{
						cout << "����:";
					}

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
		//����ĳ������ȥ��������
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
//����ĳɾȥ��index�����ĵ�mask����,�����������Դ���closure���ٱ���֮�����հ��ܷ񸲸�ɾ������
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
//�ݹ麯��������֮ǰ�����ʼ��controlDependencies
//initControlDependencies();
void form::findBasis()
{
	//����ɾ��һ������X'->Y'��Ѱ�������������ܷ��Ƴ�Y'
	//���ܣ���ɱ�ɾ���������ܱ�ɾ��

	//��Ҫ��������ȡһ���������������attributes

	//closure   �������Ƿ���Y'
	bool basisFound = false;
	initbasisDependencies();

	for (int i = 0; i < dependenciesNum; i++)
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

#pragma region tips
		if (language == "EN")
		{
			cout << "after step 1:" << endl;
		}

		if (language == "CN")
		{
			cout << "�� 1 ������ȥ�����ຯ����������:" << endl;
		}
		printBasis();
		//��һ������ߵ����Խ��д���
#pragma endregion	
		secondProcess();
#pragma region tips
		if (language == "EN")
		{
			cout << "after step 2:" << endl;
		}

		if (language == "CN")
		{
			cout << "�� 2 ������ȥ�������������Ҳ����������ԣ���:" << endl;
		}
		printBasis();
#pragma endregion


		saveBasis();



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
#pragma region ��ʾ
			if (language == "EN")
			{
				cout << "after step 1:" << endl;
			}
			if (language == "CN")
			{
				cout << "��1����:" << endl;
			}
#pragma endregion


			printBasis();
			//��һ������ߵ����Խ��д���
			secondProcess();
#pragma region ��ʾ
			if (language == "EN")
			{
				cout << "after step 2:" << endl;
			}
			if (language == "CN")
			{
				cout << "��2����:" << endl;
			}
#pragma endregion
			printBasis();
			saveBasis();
		}
		return;
	}
}
bool form::changeControl()
{
	int last0Site = -1;

	//Ѱ�ҳ�ȡĩλ ���һ��0���ֵ�λ��
	//��ĩλ��0�����������ԣ���Ѱ����һλ0�������һ��0�����ڣ����˳����򣬷���false
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

	//��ĩλ��0��Ϊ-1
	controlDependencies[last0Site] = -1;

	//����-1��ĵĿ��Ʊ���Ϊ-1������1������ǰ���ֵ
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
					//����ӡ����
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

	for (int i = 0; i < dependenciesNum; i++)
	{
		if (basisDependencies[i] == 1)
		{
			for (int j = 0; j < attributesNum; j++)
			{
				//ȷ����������δ�����δ�����̴���
				if (maskAttributes[i][j] != -1 && leftDependencies[i][j] == 1)
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
