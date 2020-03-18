#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<time.h>
#include<iostream>
#include"time.h"
#include"Complex_p.h"
#include"ds.h"
#include"matricx.h"
#include"sort.h"
#include "closure.h"

using namespace std;
class B;


int& change(int* m, int site);
int& change(int& m);
int& change(int& m)
{
	return m;
}
int& change(int* m, int site)
{
	return m[site];
}

class A
{
private:
	int a;	
public:	
	A(int a) :a(a)
	{
		cout << "constructor of A"<<endl;
		cout << "set a to " <<a<< endl;
	}	
	
	
	A()
	{
		cout << "constructor of A" << endl;
		a = 0;
		cout << "set a to 0" << endl;
	}
	~A()
	{
		cout << "a is " << a << endl;
		cout << "destructor of A" << endl;
	}
	A(const A& t) 
	{
		*this = t;

		cout << "copy constructor of A" << endl;
	}
	/*
	void process(B t)
	{
		cout << "process B from A" << endl;
		//t.change(aa);
	}
	*/
	int getValue()
	{
		cout << "a is " << a << endl;
		return a;
	}
	
};
class B:public A
{
public:
	A ac;
	friend class C;
	B()
	{
		cout << "constructor of B" << endl;
		b = 0;
		ac=A(2);
		cout << "set b to 0" << endl;
	}
	B(int b) :b(b), ac(b-4)
	{
		cout << "constructor of B" << endl;
		cout << "set b to " << b << endl;
	}
	B(const B& t):ac(t.ac)
	{
		b = t.b;

		cout << "copy constructor of B" << endl;
	}
	~B()
	{
		cout << "b is " << b << endl;
		cout << "destructor of B" << endl;
	}
	void change(int t)
	{
		b = t;
		cout << "change b to " << b << endl;
	}
	int getValue()
	{
		cout << "b is " << b << endl;
		return b;
	}
private:
	int b;
	static int s;
};
int B::s = 3;
B create(int s)
{
	B temp(s);
	return temp;
}

class C
{
public:
	static int c7;
	C(int a=4) :c(a),c4(a){}

	int getValue()const;
	int getValue();
	void change(int t)
	{
		c = t;	
		m.b = t;		
	}	
	void tr(int t,B s)
	{
		c = t;	
	}
	void tll(int m)
	{
		d = m;
	}
	void showd()
	{
		cout << "d is	" << d << endl;
	}
	friend void strong(C&t);
	
private:
	B m;
	
	static int c1, c2, c3;
	
	const int c4;
	int c;
	static void add()
	{
		c3 = c1 + c2;
	}
protected:
	int d;
};
void strong(C&t)
{
	t.c = 50;
}
int C::c1 = 1;
int C::c2 = 2;
int C::c3 = 3;
int C::c7 = 10;
int C::getValue()const
{
	return c4;
}
int C::getValue()
{
	return c;
}
void getOperands(Complex& c1, Complex& c2);
int Input(int& n, int& t)
{
	char s[100];
	cout << "go on?(q to quit)" << endl;
	cin >> s;
	if (*s == 'q')
		return 0;
	cout << "which number to transfer:";
	cin >> n;
	cout << "in which form?";
	cin >> t;
	return 1;
}
int Input(int& i, int& j, MElemType& e)
{
	char s[100];
	cout << "go on?(q to quit)" << endl;
	cin >> s;
	if (*s == 'q')
		return 0;
	cout << "row:";
	cin >> i;
	cout << "colomn:";
	cin >> j;
	cout << "value:";
	cin >> e;
	return 1;
}
int main(void)
{	
	form te(5);
	string menu = "********************MENU********************\n"\
		"i.initAttributes\ta.addDetermine\ts.setClosure\nf.findClosure\t"\
		"p.printInfo\tq.quit\n"\
		"********************************************\n";
	char choice;

	cout << menu;
	cin >> choice;

	while (choice != 'q')
	{
		switch (choice)
		{
		case'i':
			te.setAttributes();
			break;
		case'a':
			te.addDependency();
			break;
		case's':
			te.setClosure();
			break;
		case'f':
			te.findClosure();
			break;
		case'p':
			te.print();
			break;
		default:
			break;
		}

		cout << menu;
		cin >> choice;

	}


	return 0;


	te.print();
	//te.isValid('2');
	//te.isValid('5');
	
	te.addDependency();
	te.addDependency();
	te.addDependency();
	te.addDependency();

	te.print();
	te.setClosure();
	te.print();
	te.findClosure();
	te.print();
	return 0;











	Complex c1(3,40), c2(5,60), c3(7,80),c(0,0);
	
	c = c1 + c2 +c3;

	c.display();
	return 0;


















	int* num,n;
	double start, finish, dtime;
	list test = { NULL,NULL,0 };//链表初始化
	BiTree t=NULL,h = NULL;//排序二叉树初始化
	cout << "how many num do you want to sort（0 to quit):" << endl;
	cin >> n;
	
	
	while (n > 0)
	{
		num = (int*)malloc(sizeof(int) * (n+1));//空出0号位

		generate(num, n);
		//display(num, n);
		start = clock();
		selectionSort(num, n);
		finish = clock();
		//display(num, n，1);
		dtime = finish - start;
		printf("\t 选择排序运行时间=%gms\n", dtime * 100. );

		start = clock();
		generate(h,num, n);
		//display(num, n);
		finish = clock();
		//selectionSort(num, n);
		

		mrootTree(h);
		InOrderThreading(t, h);
		cout << "another way:" << endl;
		InOrderTraverse_thr(t);
		//InOrderTraverse(h);
		//display(num, n，1);
		dtime = finish - start;
		printf("\t 二叉排序运行时间=%gms\n", dtime * 100.);

		/*
		
		
		
		
		generate(num, n);
		//display(num, n);
		start = clock();
		quickSort(num+1, n);//快速排序直接传后面移位数组
		finish = clock();
		//display(num, n,1);
		dtime = finish - start;
		printf("\t 快速排序运行时间=%gms\n", dtime * 100.);

		generate(test, num, n);
		start = clock();
		quickSort(test.first, n);
		finish = clock();
		dtime = finish - start;
		printf("\t 快速排序(链表）运行时间=%gms\n", dtime * 100.);


		generate(num, n);
		//display(num, n);
		start = clock();
		heapSort(num , n);
		finish = clock();
		//display(num, n,1);
		dtime = finish - start;
		printf("\t 堆排序运行时间=%gms\n", dtime * 100.);		
		*/
		free(num);

		cout << "how many num do you want to sort（0 to quit):" << endl;
		cin >> n;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*
	while (n > 0)
	{
		num = (int*)malloc(sizeof(int) * (n + 1));


		
		//cout << "after sort:" << endl;
		//display(test, num, n, 1);
	
		/*cout << "in all:" << endl;
		linklist temp = FIRST;
		int i = 0;
		while (temp != NULL)
		{
			cout << ++i << ":" << temp->m << endl;
			temp = temp->next;
		}
		
		

		cout << "how many num do you want to sort（0 to quit):" << endl;
		cin >> n;
		

		
	}
	
	*/
	
	
	
	
}
