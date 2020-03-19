#pragma once
#include <malloc.h>

#include<iostream>
#define MAXSIZE 10
#define MAXNUM 30
#define LESSINFO true //���ٴ�ӡ��Ϣ
using namespace std;


class form
{

private:
	int attributesNum;
	int dependenciesNum;
	int toOneDependenciesNum;
	int attributes[MAXSIZE];
	int leftDependencies[MAXNUM][MAXSIZE];
	int rightDependencies[MAXNUM][MAXSIZE];


	//�ұ�ת��Ϊ��ֵ����
	int toOneDependency[MAXNUM][MAXSIZE];//��ά�ȣ���ࣩ��ʾ��i��������ϵ����ά��ʾ����������ϵ�еĵڼ���
	int closure[MAXSIZE];

	int basisDependencies[MAXNUM];//�洢��ȡ��С������
	int controlDependencies[MAXNUM];//�洢�趨�������Ա�õ����п��ܵ���С������
public:
	string tips = "(q to quit and s to save): ";


	form();
	form(int num);

	void setAttributes();
	bool isValid(char& ch);
	void initAttributes();
	void initClosure();
	void initDependencies(int index);
	void initbasisDependencies();
	void initControlDependencies();

	void setNum(int num);
	void setDependenciesNum(int num);
	//�ı�������ֵ�趨��siteΪ'l'ѡ��ı���ߵı������'r'�ı��ұ�������; i,j��ʾ�ı��i��ĵ�j������ֵΪvalue��0/1��
	void setDependency(char, int, int, int);
	//��������ֱ�Ӹı�����ֵ����stateΪ-1���������������ı��state��
	void setDependencies(int*, int*, int state = -1);
	int addSide(char& choice, int* determine);
	void addDependency();

	void findBasis();

	bool changeControl();

	void sendToClosure(int index);
	void setClosure();
	void findClosure();
	void findClosure(int);//��basis

	void split()
	{
		//TODO
	}
	void print();
	void printBasis();
	void printAttribute(int index);
	void printAttributes(int* attributes, char choice = 'w');



};
