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
		basisDependencies[i] = 1;//��ʼ������
	}
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
				split();//ʹ��splitting rule(�ֽ���)���ұ�ת��ΪȫΪ1��
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
		cout << "after step 1:" << endl;
		printBasis();
		//��һ������ߵ����Խ��д���

		secondProcess();
		cout << "after step 2:" << endl;
		printBasis();
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
			initMaskAttributes();
			cout << "after step 1:" << endl;
			printBasis();
			//��һ������ߵ����Խ��д���
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

