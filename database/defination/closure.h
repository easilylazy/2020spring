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
	//��ӡ������Ϣ��ȫ����
	void printInfo();
	//��ӡ��С��������
	void printBasis();
	//��ӡ��index����������
	void printAttribute(int index);
	//��ӡĳ������attributes��Ϊ1��ֵ��Ӧ����ĸ����
	void printAttributes(int* attributes, char choice = 'w');
};
