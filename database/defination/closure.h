#pragma once
#include <malloc.h>

#include<iostream>
//���Ը�������
#define MAXSIZE 10
//������������
#define MAXNUM 30
//���ٴ�ӡ��Ϣ
#define LESSINFO true 
using namespace std;


class form
{

private:
	//����ֵ�ܸ���
	int attributesNum;
	//���������ܸ���
	int dependenciesNum;
	//�Ҳ�ȫ��ת��Ϊ��ֵ��������������δʹ�ã�
	int toOneDependenciesNum;
	//����ֵ�����鴢�棨������Ϊ1��
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

	//�洢��ȡ��С������
	int basisDependencies[MAXNUM];
	//�洢�趨�������Ա�õ����п��ܵ���С������
	int controlDependencies[MAXNUM];
	//�洢�ɱ�ɾȥ���󲿵�������
	int maskAttributes[MAXNUM][MAXSIZE];

	//��С�������Ǳ���
	bool ownIsBasis;
public:
	//��ʾ��
	string tips = "(q to quit and s to save): ";

	//���캯����Ĭ��
	form();
	//�������Ը���
	form(int num);

	void setAttributes();
	bool isValid(char& ch);
	void initAttributes();
	void initClosure();
	void initDependencies(int index);
	void initbasisDependencies();
	void initControlDependencies();
	void initMaskAttributes();

	void setNum(int num);
	void setDependenciesNum(int num);
	//�ı�������ֵ�趨��siteΪ'l'ѡ��ı���ߵı������'r'�ı��ұ�������; i,j��ʾ�ı��i��ĵ�j������ֵΪvalue��0/1��
	void setDependency(char, int, int, int);
	//��������ֱ�Ӹı�����ֵ����stateΪ-1���������������ı��state��
	void setDependencies(int*, int*, int state = -1);
	//��ȡ��index�������������Ҳ���Ĭ�Ͼ����˷ֽ⣬ֻ��һ��ֵ��
	int getRightDependency(int index);
	int addSide(char& choice, int* determine);
	void addDependency();



	void findBasis();

	bool changeControl();

	void findClosure(char choice, int index);

	void secondProcess();


	void sendToClosure(int index, int mask);
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
