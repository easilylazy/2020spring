#pragma once
#include <malloc.h>
#include <string>
#include<iostream>
//���Ը�������
#define MAXSIZE 10
//������������
#define MAXNUM 30
//���ٴ�ӡ��Ϣ
#define LESSINFO true 


using namespace std;

//Ӣ��
extern string language;
//��ʾ
extern bool displayTips;
void initArray(int* array,int length,int initValue = 0);
void printArray(int* array, int length);
void initArray2d(int* array, int M, int N, int initValue = 0);
void printArray(int* array, int M, int N);
bool compareArray(int* firstArray, int* secondArray, int length);
class minimalBase
{
private:
	int dependenciesNum;
	int finalDependenciesNum;
	int attributesNum;
	
	int leftDependencies[MAXNUM][MAXSIZE];
	int rightDependencies[MAXNUM];

public:
	bool isValid;//����¼����С�������Ѵ�����ͬ�ģ���Ϊfalse
#pragma region ����
	minimalBase()
	{
		isValid = true;
		dependenciesNum = 0;
		finalDependenciesNum = 0;
		attributesNum = 0;
		//initLeft
		initArray(rightDependencies, MAXNUM, -1);
		initArray2d((int*)leftDependencies, MAXNUM, MAXSIZE);


		//initRight();
	}
#pragma endregion

#pragma region �趨
	//�趨����ֵ����
	inline void setAttributesNum(int num)
	{
		attributesNum = num;
	}
	//�趨����������
	inline void setDependenciesNum(int num)
	{
		dependenciesNum = num;
	}
	//�趨����������
	inline void setLeftDependency(int i, int j)
	{
		leftDependencies[i][j] = 1;
	}
	//�趨����������
	inline void setRightDependency(int index, int value)
	{
		rightDependencies[index] = value;
	}
#pragma endregion

#pragma region ȡֵ
	inline int getDependenciesNum()
	{
		return dependenciesNum;
	}
#pragma endregion

#pragma region ȥ��
	//�������Ҳ��������ѱ�ǰ������(ƽ������)����ȥ�����������Ҳ���Ϊ-1��
	void dropTrivival()
	{
		for (int i = 0; i < dependenciesNum; i++)
		{
			int rightValue = rightDependencies[i];
			if (rightValue >= 0
				&& rightValue < dependenciesNum
				&& leftDependencies[i][rightValue] == 1)
			{
				rightDependencies[i] = -1;
			}
			else if (rightValue >= 0
				&& rightValue < dependenciesNum
				&& leftDependencies[i][rightValue] != 1)
			{
				finalDependenciesNum++;
			}
		}
	}
	//�������Ҳ��������ѱ�ǰ����������ȥ�����������Ҳ���Ϊ-1��
	void dropRepeated()
	{
		bool passCheck;
		for (int i = 0; i < dependenciesNum; i++)
		{
			
			//ÿ����Ч��������֮ǰ�����������Ƚϣ�����Ƿ�����ȫ�ظ��ģ����У��Ҳ���Ϊ-1��������Ŀ��1

			if (isNumValid(rightDependencies[i]))
			{
				

				for (int j = 0; j < i; j++)
				{
					//�ȱȽ��Ҳ�
					if (rightDependencies[i] == rightDependencies[j])
					{
						passCheck = false;
						//���Ҳ���ͬ���Ƚ��������Ƿ���ȫ��ͬ
						for (int k = 0; k < attributesNum; k++)
						{
							int currentValue = leftDependencies[i][k];
							int pastValue = leftDependencies[j][k];
							if (currentValue != pastValue)
							{
								//ֻҪ��һ������ͬ���Ǿ�ͨ�����
								passCheck = true;
								//break;
							}
						}

						if (passCheck != true)
						{
							rightDependencies[i] = -1;
							finalDependenciesNum--;
						}
					}
				
				}

			
			}
		
			


			
		}
	}
#pragma endregion

#pragma region ��ӡ
	void printResult()
	{

#pragma region tips
		string tip1, tip2;
		if (language == "EN")
		{
			tip1 = "after drop trivival: ";
			tip2 = "after drop repeated: ";
		}
		if (language=="CN")
		{
			tip1 = "ȥ��ƽ��������: ";
			tip2 = "ȥ���ظ�������: ";
		}
#pragma endregion


		printDependencies();
		dropTrivival();
		cout <<tip1 << endl;
		printDependencies();
		dropRepeated();
		cout << tip2 << endl;
		printDependencies();
	}
	void printDependencies();
	void printAttributes(int* attributes, char choice);
	bool isNumValid(int);
#pragma endregion


	friend void initArray(int* array, int length, int initvalue);
	friend void initArray2d(int* array, int M, int N, int initValue);
	friend void printArray(int* array, int length);
	friend void printArray(int* array, int M, int N);

	friend class form;
};
class form
{

private:
	//��С����������
	int minimalBasesNum;
	//�洢��С����������
	minimalBase minimalBases[MAXSIZE];
	//����ֵ�ܸ���
	int attributesNum;
	//���������ܸ���
	int dependenciesNum; 
	//�Ҳ�ȫ��ת��Ϊ��ֵ��������������δʹ�ã�
	int toOneDependenciesNum;
	//���������鴢�棨������Ϊ1��
	int attributes[MAXSIZE];
	//��������ĳһ�����X����Ӧ�Ҳ�Y,��X->Y
	int leftDependencies[MAXNUM][MAXSIZE];
	//��������ĳһ����Ҳ�Y����Ӧ��,��X->Y
	int rightDependencies[MAXNUM][MAXSIZE];	


	//�ұ�ת��Ϊ��ֵ���棨��δʹ�ã�
	//��ά�ȣ���ࣩ��ʾ��i��������ϵ����ά��ʾ����������ϵ�еĵڼ���
	int toOneDependency[MAXNUM][MAXSIZE];

	//�������ĳ��������������ĳ���Լ��ıհ����
	int closure[MAXSIZE];

	//�Ѿ�Ѱ����ɱհ�
	bool closureFound;

	//�洢��ȡ��С������
	int basisDependencies[MAXNUM];
	//�洢�趨�������Ա�õ����п��ܵ���С������
	int controlDependencies[MAXNUM];
	//�洢�ɱ�ɾȥ���󲿵�������
	int maskAttributes[MAXNUM][MAXSIZE];

	//��С�������Ǳ���
	bool ownIsBasis;
	//�Ѿ�Ѱ�������С������
	bool basisFound;
public:
	//��ʾ��
	string tips = "(q to quit and s to save): ";
	string tipsCN = "(���� s ����/���� q �������˳�): ";

	//���캯����Ĭ��
	form();
	//�������Ը���
	form(int num);

#pragma region ��ʼ��
	//�����ж�ȡ�������Ը���
	void setAttributes();
	//�ж���������ֵ������/��д��ĸ���Ƿ�Ϸ�
	bool isValid(char& ch);
	//��ʼ���洢�������飨������1��
	void initAttributes();
	//��ʼ���հ�������0��
	void initClosure();
	//��ʼ�����Ϊindex����������0��
	void initDependencies(int index);
	//��ʼ����С����������1��
	void initbasisDependencies();
	//��ʼ����������������1��
	void initControlDependencies();
	//��ʼ���������Լ�����0��
	void initMaskAttributes();
#pragma endregion

	
#pragma region ��������
	//�������Ը���������ȫ����ʼ��
	void setNum(int num);
	//��������������
	void setDependenciesNum(int num);
	//�ı�������ֵ�趨��siteΪ'l'ѡ��ı���ߵı������'r'�ı��ұ�������; i,j��ʾ�ı��i��ĵ�j������ֵΪvalue��0/1��
	void setDependency(char, int, int, int);
	//��������ֱ�Ӹı�����ֵ����stateΪ-1���������������ı��state��
	void setDependencies(int*, int*, int state = -1);
	//��ȡ��index�������������Ҳ���Ĭ�Ͼ����˷ֽ⣬ֻ��һ��ֵ��
	int getRightDependency(int index);
	//�����л�ȡ���룬����µ���������addDependency()���ã�
	int addSide(char& choice, int* determine);
	//�����л�ȡ���룬����µ�����
	void addDependency();
	//�趨�հ��ĳ�ʼֵ����������Ҫ��ȡ������
	void setClosure();
	//Ѱ��ĳ������ĳ�����������µıհ�
	void findClosure();
#pragma endregion
	

#pragma region Ѱ��������
	//Ѱ��ĳ������������basis/��С������
	void findBasis();
	//����index�������������Դ���closure
	//�ٱ���֮������������������������µıհ��ܷ񸲸�index���Ҳ����ԣ����ܣ����ɾȥ�ú�������//
	void sendToClosure(int index);
	//Ѱ��ĳ������ĳ�����������µıհ�
	//�ر���basisʱ������ĳ�������ȥ������
	void findClosure(int);
	//����С�������ĵڶ�������
	void secondProcess();
	//�ı�������������� findBasis() ����
	bool changeControl();
	//Ѱ��ĳ������ĳ�����������µıհ�
	//�ر� �������index��������ʣ�µ������ıհ�
	void findClosure(char choice, int index);
	//����ĳɾȥ��index�����ĵ�mask����,�����������Դ���closure
	//�ٱ���֮����������������������������µıհ��ܷ񸲸�ɾ�����ԣ����ܣ����ɾȥ�ú������������󲿵ĸ�����
	void sendToClosure(int index, int mask);
#pragma endregion

	//ֻ��ӡ��ǰ�治��ȫ��ͬ��������
	void printFinalResult();
	//�Ƚ����������У���ȫһ������true�����򷵻�false
	friend bool compareArray(int* firstArray, int* secondArray, int length);

	//�Ƚ����������У����current�е��������ݱ�exist��������ȫһ������true�����򷵻�false
	bool compare(minimalBase current, minimalBase exist);

#pragma region ��ӡ��Ϣ
	//��ӡ������Ϣ��ȫ����
	void printInfo();
	//��ӡ��С��������
	void printBasis();
	//���ҵ�����С����������������minimalBases��
	void saveBasis();
	//��ӡ��index����������
	void printAttribute(int index);
	//��ӡĳ������attributes��Ϊ1��ֵ��Ӧ����ĸ����
	void printAttributes(int* attributes, char choice = 'w');

	void printMinimaBases();
#pragma endregion

	
		
	void split()
	{
		//���Ի�ȡ�Ҳ�����1�����룬������ֽ�ת��ΪȫΪ1
		//����
		//X->A1,A2,A3
		//ת��Ϊ
		//X->A1
		//X->A2
		//X->A3
		//TODO
	}
	friend class minimalBase;

};
