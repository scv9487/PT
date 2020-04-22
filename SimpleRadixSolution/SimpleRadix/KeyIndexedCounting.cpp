

#include <iostream>
#include <string>
#include <random>

//#include "KeyIndexedCounting.h"

using namespace std;

int RandNum(int min, int max)
{
	random_device rd;
	mt19937_64 rng(rd()); // �� rd()�� ���� ��ü �����ڵ� �ƴϰ�
	// rng ������ �Ź� �ٸ� ���� ���� �ʴ´�. �õ忡 ���� �Ѱ��� (������X) ���� �̴� ���ε�, rd ��ü�� �Ź��ٲ�� ������ rd�� �õ�� ��Ƶθ� ������ �Ǵ� ��
	uniform_int_distribution<int> range(min, max);
	return range(rng);
}


class CharInfo
{
private:
	string _name;
	int _cid;
	int _svr; // ������ 1~3 ������ ����
	int _power;

public:
	CharInfo()// : _name(NULL), _cid(0), _svr(0), _power(0)
	{
		cout << "CharInfo �⺻ ������ ȣ��" << endl;
	}

	CharInfo(string name, int cid, int svr, int power): _name(name), _cid(cid), _svr(svr), _power(power)
	{
	}


	void ShowInfo()
	{
		cout << "SHOWINFO =============================="<< endl;
		cout << "name : "<< _name << endl;
		cout << "cid : " << _cid << endl;
		cout << "svr : " << _svr << endl;
		cout << "power : " << _power << endl;
	}

	int GetSvr()
	{
		return _svr;
	}

	int GetPower()
	{
		return _power;
	}

};


// Sorting �� <T> ���� �迭, Radix ��, Ű�� �д� �Լ��� �ѱ�
// ���� �Լ� �����͸� ������� �ʴ´ٸ� ��� �ɱ�?
// A: ���� �ɰ��� ������ ����µ�, Ư�� Ÿ�Կ� �������� �Լ��� �ǹ�����. ��, CharInfo��� Ư�� Ÿ���� �ƴϸ� �� sort �Լ��� ����� �Ұ��ϴ� 
// (Ȥ�� ���ÿ����� Ư���ϰ� ���ǵ� Ŭ������ ��ӹ޵��� ������ �ɸ���. �̷��� �ص� �θ� Ŭ�������� �䱸�ϴ� Ư�� �Լ��� �̸� �����ؾ��ϱ� ������ �������� ������ �Ӵ��� �����ϰ� �ڵ尡 ����������)
// ���� CharInfo��� Ÿ�Կ��� ���缭 �ۼ��ϴ��� sort �Լ� ������ � ���� �������� �������� �б⸦ �����, �� �б⸶�� ���� �ٸ� Ű�� �д� �Լ��� �� �ڵ�(���� �ߺ���)�� ¥���Ѵ�.

class KeyIndexedCounting
{
public:

	
	//static void Sort(T* arr, int radix, int(*funcPtr)())
	// Why? ���ڴ� �迭 �̸�(��, Ȯ���� �迭)�ΰ� �迭�� �ƴ� �����Ϳ� ������ �ϴ� �����Ϸ��� �翬�� �źθ� ����..
	// �̰�.. �Ű��������� �迭 ���� ���� []�� �ĺ��� ���ʿ� �ٿ��� �ϴ±���. �׳� �����͸� �ȳѾ��
	template<typename T>
	static void Sort(T* arr[], int arrLen, int radix, int(T::*funcPtr)()) // �迭�� �ޱ� ���� �����Ҵ��� ��� �Ű��������� []�� ������ְ� �ִ�. �����Ҵ� ������ []�� �����ٺ��� �򰥸��� �̰�;; // ��.. �����Ҵ����� �ؼ��ϱ� ����, T*�� �迭 arr�� �����ϸ鼭 arr�� ���� ���ڷ� ���� �ּҰ����� �ʱ�ȭ���״�. �� �� �´� �ؼ��ϼ��� ���� �� ����,
	// �� �׷��� arr[]��  []�� ���ôµ� �迭�� T*���� ������ ���ٰ� ������ ����. ���� �迭�� �ѱ� ���ΰ�?...�������� �迭�� �Ű������μ� ������ ���ΰ�? �迭�� ���Կ����� �����Ѱ�?
	// ���������� ��� �����ڳ� ����������������
	// ���� static void Sort(T* arr[], int arrLen, int radix, int(CharInfo::*funcPtr)()) ����� -> T* arr[] �� �Ű��������� �迭 �����Ѱ� ����. ��� �迭�μ� ������ ����� arr�� ���� ���޹޴� �迭�� �ּҰ����� �ʱ�ȭ���� ����
		// T*�� �迭�̱� ������ �ϳ��� �迭 ��Ҵ� T*�� �˸°� ��޵Ǵ� ��
	// ���� static void Sort(T** arr, int arrLen, int radix, int(CharInfo::*funcPtr)()) ����� ��
		// 'T*'�� �������� arr��. �����̴� ������ 'T*'��. �� T*�� �迭�� ������ ������ ������� �۵���.
		// �� �ΰ��� �����. ��� ���ڿ��� []�迭�� �޳�, �����ͷ� �޳Ŀ� ������ ��Ŀ�������� �۵���. ��� ���ڿ������� ����� ���� ���ڿ��� ���� ���� ���ΰ� �޶�������.
		// �� ��쿡�� ���ʿ� �޸𸮿� ����� ���ڸ� �Ű������� �ޱ� ������ ����� ���� ���ڰ� ����� ����ȴٰų� ������ ����.
		// �����ʹ� ������ �ܼ��ϱ���... ���� Ư�� �޸��� �ּҰ��� ������ �ڽ��� ������ ���� ���� ����ǰų� ������ �� ����.
	{
		cout << "SORT START!!!" << endl;
		
		// ��� ī������ ���� count �迭 ����
		//const int temp = radix + 1;
		//int count[temp]; //C++ ǥ�ؿ����� �迭�� ũ�⸦ ������Ÿ�ӿ� �����մϴ�. ���� �迭�� ũ��� �Ϲ� ������ ������ �� ������ ������ Ÿ�� ����� ���� �������� �մϴ�.
		//https://hashcode.co.kr/questions/6708/%EB%B0%B0%EC%97%B4%EC%9D%98-%ED%81%AC%EA%B8%B0%EB%A5%BC-%EB%B3%80%EC%88%98%EB%A1%9C-%EC%84%A4%EC%A0%95%ED%95%98%EA%B8%B0
		//������ ġ���ϱ� �ѵ�, �� �ȵǴ��� ���ش� ����. ���ڸ� ���߿� �޴� ������ �Լ������� ������ Ÿ�ӿ��� �ȵǴ� new �� �迭�� ���� �Ҵ��ع����� �Ѥ�
		int* countArr = new int[radix+1];
		for (int i = 0; i < radix+1; i++)
		{
			//cout << "countArr �ʱ�ȭ" << endl;
			countArr[i] = 0;
		}
		
		// �Ѱܹ��� �迭�� ���̸� �˾ƺ���
		// �������� �̰ɷ� �� ����޾Ҵµ� �ᱹ �������� ����� ���ٿ���
		// https://stackoverflow.com/questions/492384/how-to-find-the-sizeof-a-pointer-pointing-to-an-array

		//cout << sizeof(arr) << endl;
		//int intArr[10];
		//cout << sizeof(intArr) << endl; // �� ����� �ٸ���..
		// http://egloos.zum.com/Varasada/v/9171622
		// �迭 �̸��� �迭 ��ü�� ũ�⸦, �� �迭�� �����Ϳ� �־�θ� �������� ũ�⸦ ����.
		// �� ��ü�� �����ͳ� �ƴϳĸ� ������ �� ����. �׷� �迭 �̸��� �� ��ü�δ� �����Ͱ� �ƴ϶� �Ҹ���?
		
		//arr[1]->ShowInfo(); // ��.. �ڵ��ϼ��� �ȵǳ�. ���ø����� �̷�����. � ���� ������ ���� �Լ� �ڵ��ϼ��� �ȵ�.

		cout << "�Լ���... ��... funcPtr :" << funcPtr << endl; // �ƴ� �� 1�̼���

		// arr�� ���� �ϳ��� ��� counting ����
		for (int i = 0; i < arrLen; i++)
		{
			countArr[(arr[i]->*funcPtr)() + 1]++;
			//arr[i]->ShowInfo();
			//cout << (arr[i]->*funcPtr)() << endl; // (arr[i]->*funcPtr) �̰� �ѹ������� �Լ��� �����. �̷��� ������ �ȵǾ���. ���� �߿�!!!
			// arr[i]�� ��ü������ *funcPtr�� �θ��°� �ƴ϶� Ư�� ��ü�� �տ� ����� ������ �Լ��� �θ���. ��� ����.
			//cout << *funcPtr() << endl;
		}
		
		// counting �� ���� ���
		
		cout << "countArr[0]" << countArr[0] << endl;

		for (int i = 1; i < radix+1 ; i++)
		{
			//cout << "countArr ���� ���" << endl;
			countArr[i] = countArr[i] + countArr[i - 1];
			//cout << "countArr : " << countArr[i] << endl;
		}

		// Aux �迭 ���� �� �� �ֱ�
	
		//T* auxArr = new T[arrLen](); // T���� �迭�� �Ҵ��ߴ� �̾߱��� T*�� arrLen�� ��ŭ �����Ȱ� �ƴϴ�
		T** auxArr = new T*[arrLen]();
		cout << "�迭 �̸� auxArr : k" <<auxArr << endl;
		cout << "auxArr[0] : " << &auxArr[0] << endl;

		int* intArr = new int[arrLen];
		cout << "�迭 �̸� intArr : " << intArr << endl;
		cout << "intArr[0] : " << &intArr[0] << endl;

		for (int i = 0; i < arrLen; i++) // �����
		{
			cout << "Arr" << i << ":" << arr[i] << endl;
			//cout << "auxArr" << i << "Before : " << auxArr[i] << endl; // ���� 0���� ���´�. �ʱ�ȭ�� ��� �Ǵ°��� ������..
		}


		for (int i = 0; i < arrLen; i++)
		{

			// ���� countArr�� ���� ���� auxArr �� �� ����ֱ� + �ش� countArr �� 1����sj
			//auxArr[coguntArr[(arr[i]->*funcPtr)()]++] = *(arr[i]->GetSelf()); // �迭 �̸��� ������ִ°� ���� �������̳� �����Ϸ���.. ���̰�...
			// �ƴ� �� arr[i]�� (�� ��ü���ٵ�) �ȵǰ� �ѹ� ���Ƽ� ���� �Ǵ°ž�?... �� �ļ��� �� ����ص���. 
			// auxArr[countArr[(arr[i]->*funcPtr)()]] = arr[i]; //arr[i]; //arr[i];
			auxArr[countArr[(arr[i]->*funcPtr)()]] = arr[i]; //arr[i]; //arr[i];
			countArr[(arr[i]->*funcPtr)()]++;
			
			//auxArr[countArr[0]] = NULL; //arr[i];
			//cout << countArr[i] << endl;

		}

		for (int i = 0; i < arrLen; i++) // ����� 
		{
			cout << "auxArr" << i << "After : " << auxArr[i] << endl; // ���� auxArr 2�� ���� �־��µ�, �� Ȯ���� 0���� �ϰ� �ִ�. �̰� �߸���Գ�!!
		}

		for (int i = 0; i < arrLen; i++)
		{
			// aux ���� arr�� �־�����
			arr[i] = auxArr[i];
		}

		for (int i = 0; i < arrLen; i++) //����� 
		{
			cout << "Arr" << i << ":" << arr[i] << endl;
		}

	}


	template<typename T>
	static void SortB(T num)
	{
		cout << "SORT" << endl;

	}


	static void SortC(int num)
	{
		cout << "SORT C" << endl;
	}

};


template<typename T>
static void SortD(T num)
{
	cout << "SORT D" << endl;

}
//
//int main()
//{
//	int intArr[10];
//	cout << intArr << endl;
//	cout << &intArr[0] << endl;
//
//	cout << "KeyIndexedCounting" << endl;
//
//	// �ϴ� ��� 1������ ����.. ������ �������� �ټ�������
//	
//
//	//charinfo* ci1 = new charinfo("�������", 0, 2, 2160);
//	//charinfo* ci2 = new charinfo("������", 1, 1, 4506);
//	//charinfo* ci3 = new charinfo("�ѹ��ִ�", 2, 0, 9998);
//	//charinfo* ci4 = new charinfo("�Ƕ��̸�", 3, 2, 7549);
//
//	const int Radix = 10000; // ����� ������ �ڸ����Դϴ�. ���� ��� ���� 42�� 4�� 2�� �ΰ��� �ڸ����� ������ �̰��� ����� �˴ϴ�. 
//		// ��������� �̷��� �ڸ����� ���� ���� ������ �ϱ� ������ ��������̶�� �̸��� ������ϴ�. 
//		// ����� ���� �� �ִ� ��쿡 ���� Radix�� ���� ���ε�. ������ 1~3������ ������ radix�� 3�ΰ� (count[radix+1]�� �ǰ���)
//
//	const int arrLen = 10;
//	CharInfo* arr[arrLen]; // ������ �迭. �迭�� ���̴� ���ڷ� �ѱ��� �ʰ�, sorting �Լ������� �ľ�
//	// const int�� �ƴ϶� int �� ���� �ѱ�� ������ ����. �迭�� ũ��� ����� �����Ǿ�� �Ѵ�.
//	
//	for (int i = 0; i < arrLen; i++)
//	{
//		arr[i] = new CharInfo("�̸�����", i, RandNum(0,2), RandNum(0, 10000));
//		arr[i]->ShowInfo();
//	}
//
//	// �迭�� �� �����Ϳ� ��ü�� �ּҸ� �־��
//
//	// �Ʒ� ǥ���� ���� ���� �۵��Ѵ�
//	//SortD<int>(10);
//	//KeyIndexedCounting::SortC(10);
//	//KeyIndexedCounting::SortB<int>(10);
//
//	cout << "BEFORE======================"<< endl;
//
//
//	//arr[0]->ShowInfo();
//	//arr[1]->ShowInfo();
//
//	//arr[2]->ShowInfo();
//	//arr[3]->ShowInfo();
//
//
//
//
//	//KeyIndexedCounting::Sort<CharInfo>(arr, arrLen, 3, &CharInfo::GetSvr); // �տ� &�Ⱥ��̸� ��������. ::�� �Լ��� ��� �Ҽ����� �˷���� �Ѵ�. // �ɹ��Լ��� �̸��� �ּҷ� ��µ��� �ʴ´� 1�� ���´� �׳�. ���۸� �غ��� �������� ������δ� ���ٴ� ��.
//	KeyIndexedCounting::Sort<CharInfo>(arr, arrLen, Radix, &CharInfo::GetPower);
//	cout << "AFTER====================== ������ ����!" << endl;
//	
//	for (int i = 0; i < arrLen; i++)
//	{
//		arr[i]->ShowInfo();
//	}
//
//	cout << "AFTER====================== ���� ����!" << endl;
//
//	KeyIndexedCounting::Sort<CharInfo>(arr, arrLen, 3, &CharInfo::GetSvr);
//
//	for (int i = 0; i < arrLen; i++)
//	{
//		arr[i]->ShowInfo();
//	}
//
//
//	return 0;
//}


class stringForRadixSort : string 
{

};



void LSDSort(string strArr[], int arrLen, bool isDescending)
{
	cout << "LSD SORT!" << endl;

	for (int i = 0; i < arrLen; i++)
	{
		cout << strArr[i] << endl;
	}

	// string �� ���� ��� �̷��� �ִ����� �׳� �Լ� ���� ��

	for (int j = strArr[0].length(); j>0 ; j--)
	{
		cout << j << endl;
		
		const int radix = 256;

		int countArr[radix + 1] = {0,};

		// �� ��Ʈ���� ��ȸ�ϸ� j ��° ��Ҹ� ī����
		for (int k = 0; k < arrLen; k++)
		{
			countArr[strArr[k].at(j-1) + 1]++;
		}
		
		// ī���� ���� ���
		for (int i = 1 ; i < radix +1 ; i++)
		{
			countArr[i] = countArr[i - 1] + countArr[i];
			cout << i << "��° ����" << countArr[i] << endl;
		}

		string* auxStrArr = new string[arrLen];


		for (int k = 0; k < arrLen; k++)
		{
			auxStrArr[countArr[strArr[k].at(j-1)]++] = strArr[k];
		}

		for (int k = 0; k < arrLen; k++)
		{
			cout << auxStrArr[k] << endl;
		}


	
	}

	cout << (int)'a' << endl;

	
}



int main()
{

	cout << "LSD.cpp" << endl;

	// ������ ������ ���ڿ��� ������ �޴´�

	const int LEN = 5;
	const int STR_COUNT = 1000;

	string strArr[STR_COUNT];

	for (int i = 0; i < STR_COUNT; i++)
	{
		// char �迭 ����
		char cArr[LEN];
		for (int j = 0; j < LEN; j++)
		{
			if (j != LEN - 1)
			{
				// ���� ������ �迭 ��Ұ� �ƴ϶�� ������ ���� �ִ´�
				cArr[j] = RandNum('a', 'z');
			}
			else
			{
				// �迭 ������ ����� ���� 0���� ����
				cArr[j] = 0;
			}
		}
		strArr[i] = cArr;
	}


	strArr[0].at(0) = 'a';
	strArr[0].at(1) = 'a';

	strArr[0].at(2) = 'a';
	strArr[0][3] = 'b';
		
	for (int i = 0; i < STR_COUNT; i++)
	{
		cout << strArr[i] << endl;
	}

	LSDSort(strArr, STR_COUNT, 1);


	// ������������, �������������� ���� �Լ� ȣ��� ���ڷ� ������ �� �ִ�
	// string �迭�� �޾� ���ý�Ų��


	return 0;
}