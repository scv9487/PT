

#include <iostream>
#include <string>
#include <random>

//#include "KeyIndexedCounting.h"

using namespace std;

int RandNum(int min, int max)
{
	random_device rd;
	mt19937_64 rng(rd()); // 이 rd()는 뭘까 대체 생성자도 아니고
	// rng 에서는 매번 다른 값을 뽑지 않는다. 시드에 따라 한개의 (여러번X) 값을 뽑는 것인데, rd 자체가 매번바뀌기 때문에 rd를 시드로 잡아두면 랜덤이 되는 것
	uniform_int_distribution<int> range(min, max);
	return range(rng);
}


class CharInfo
{
private:
	string _name;
	int _cid;
	int _svr; // 서버는 1~3 까지만 존재
	int _power;

public:
	CharInfo()// : _name(NULL), _cid(0), _svr(0), _power(0)
	{
		cout << "CharInfo 기본 생성자 호출" << endl;
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


// Sorting 시 <T> 형의 배열, Radix 값, 키를 읽는 함수를 넘김
// 만약 함수 포인터를 사용하지 않는다면 어떻게 될까?
// A: 아주 심각한 문제가 생기는데, 특정 타입에 의존적인 함수가 되버린다. 즉, CharInfo라는 특정 타입이 아니면 이 sort 함수는 사용이 불가하다 
// (혹은 소팅용으로 특수하게 정의된 클래스를 상속받도록 제한이 걸린다. 이렇게 해도 부모 클래스에서 요구하는 특정 함수를 미리 지정해야하기 때문에 유연성이 떨어질 뿐더러 과도하게 코드가 복잡해진다)
// 또한 CharInfo라는 타입에만 맞춰서 작성하더라도 sort 함수 내에서 어떤 값을 기준으로 소팅할지 분기를 만들고, 각 분기마다 서로 다른 키를 읽는 함수가 들어간 코드(거의 중복인)를 짜야한다.

class KeyIndexedCounting
{
public:

	
	//static void Sort(T* arr, int radix, int(*funcPtr)())
	// Why? 인자는 배열 이름(즉, 확실히 배열)인걸 배열이 아닌 포인터에 넣으려 하니 컴파일러가 당연히 거부를 하지..
	// 이게.. 매개변수에서 배열 전달 때는 []을 식별자 뒤쪽에 붙여야 하는구나. 그냥 포인터면 안넘어가고
	template<typename T>
	static void Sort(T* arr[], int arrLen, int radix, int(T::*funcPtr)()) // 배열을 받기 위해 정적할당인 경우 매개변수에서 []를 명시해주고 있다. 동적할당 받을땐 []가 빠지다보니 헷갈리네 이게;; // 음.. 정적할당으로 해석하기 보다, T*인 배열 arr을 선언하면서 arr을 전달 인자로 받은 주소값으로 초기화시켰다. 가 더 맞는 해석일수도 있을 것 같다,
	// 음 그래서 arr[]에  []를 빼봤는데 배열을 T*형에 넣을수 없다고 오류가 떴다. 정말 배열을 넘긴 것인가?...ㅋㅋㅋㅋ 배열을 매개변수로서 선언한 것인가? 배열의 대입연산은 가능한가?
	// 으힉ㅋㅋㅋ 배꼽 터지겠네 ㅋㅋㅋㅋㅋㅋㅋㅋ
	// 현재 static void Sort(T* arr[], int arrLen, int radix, int(CharInfo::*funcPtr)()) 실행됨 -> T* arr[] 은 매개변수에서 배열 선언한게 맞음. 대신 배열로서 포인터 상수인 arr의 값을 전달받는 배열의 주소값으로 초기화했을 뿐임
		// T*의 배열이기 때문에 하나의 배열 요소는 T*로 알맞게 취급되는 것
	// 변경 static void Sort(T** arr, int arrLen, int radix, int(CharInfo::*funcPtr)()) 실행됨 됨
		// 'T*'의 포인터인 arr임. 움직이는 단위가 'T*'임. 즉 T*의 배열과 완전히 동일한 방식으로 작동함.
		// 위 두가지 방법은. 상수 문자열을 []배열로 받냐, 포인터로 받냐와 동일한 매커니즘으로 작동함. 상수 문자열에서는 방법에 따라 문자열의 수정 가능 여부가 달라졌지만.
		// 이 경우에는 애초에 메모리에 저장된 인자를 매개변수로 받기 때문에 방법에 따라 인자가 상수로 저장된다거나 하지는 않음.
		// 포인터는 정말로 단순하구나... 그저 특정 메모리의 주소값을 가지고 자신의 데이터 형에 따라 연산되거나 역참조 할 뿐임.
	{
		cout << "SORT START!!!" << endl;
		
		// 기수 카운팅을 위한 count 배열 선언
		//const int temp = radix + 1;
		//int count[temp]; //C++ 표준에서는 배열의 크기를 컴파일타임에 결정합니다. 따라서 배열의 크기는 일반 변수로 정해질 수 없으며 컴파일 타임 상수를 통해 정해져야 합니다.
		//https://hashcode.co.kr/questions/6708/%EB%B0%B0%EC%97%B4%EC%9D%98-%ED%81%AC%EA%B8%B0%EB%A5%BC-%EB%B3%80%EC%88%98%EB%A1%9C-%EC%84%A4%EC%A0%95%ED%95%98%EA%B8%B0
		//더럽고 치사하긴 한데, 왜 안되는지 이해는 간다. 인자를 나중에 받는 입장인 함수에서느 컴파일 타임에서 안되니 new 로 배열을 동적 할당해버리자 ㅡㅡ
		int* countArr = new int[radix+1];
		for (int i = 0; i < radix+1; i++)
		{
			//cout << "countArr 초기화" << endl;
			countArr[i] = 0;
		}
		
		// 넘겨받은 배열의 길이를 알아보자
		// 저번에도 이걸로 좀 고통받았는데 결국 직접적인 방법은 없다였음
		// https://stackoverflow.com/questions/492384/how-to-find-the-sizeof-a-pointer-pointing-to-an-array

		//cout << sizeof(arr) << endl;
		//int intArr[10];
		//cout << sizeof(intArr) << endl; // 왜 취급이 다를까..
		// http://egloos.zum.com/Varasada/v/9171622
		// 배열 이름은 배열 전체의 크기를, 그 배열을 포인터에 넣어두면 포인터의 크기를 연산.
		// 형 자체가 포인터냐 아니냐를 따지는 것 같음. 그럼 배열 이름은 그 자체로는 포인터가 아니란 소린데?
		
		//arr[1]->ShowInfo(); // 음.. 자동완성이 안되네. 템플릿에서 이러더라. 어떤 형이 들어올지 몰라서 함수 자동완성이 안됨.

		cout << "함수야... 너... funcPtr :" << funcPtr << endl; // 아니 왜 1이세요

		// arr의 값을 하나씩 세어서 counting 증가
		for (int i = 0; i < arrLen; i++)
		{
			countArr[(arr[i]->*funcPtr)() + 1]++;
			//arr[i]->ShowInfo();
			//cout << (arr[i]->*funcPtr)() << endl; // (arr[i]->*funcPtr) 이걸 한뭉텅이의 함수로 취급함. 이러니 실행이 안되었지. 아주 중요!!!
			// arr[i]이 주체적으로 *funcPtr을 부르는게 아니라 특정 객체가 앞에 내장된 형태의 함수를 부른다. 라고 보자.
			//cout << *funcPtr() << endl;
		}
		
		// counting 의 누적 계산
		
		cout << "countArr[0]" << countArr[0] << endl;

		for (int i = 1; i < radix+1 ; i++)
		{
			//cout << "countArr 누적 계산" << endl;
			countArr[i] = countArr[i] + countArr[i - 1];
			//cout << "countArr : " << countArr[i] << endl;
		}

		// Aux 배열 생성 및 값 넣기
	
		//T* auxArr = new T[arrLen](); // T형의 배열을 할당했단 이야기지 T*가 arrLen개 만큼 생성된게 아니다
		T** auxArr = new T*[arrLen]();
		cout << "배열 이름 auxArr : k" <<auxArr << endl;
		cout << "auxArr[0] : " << &auxArr[0] << endl;

		int* intArr = new int[arrLen];
		cout << "배열 이름 intArr : " << intArr << endl;
		cout << "intArr[0] : " << &intArr[0] << endl;

		for (int i = 0; i < arrLen; i++) // 디버그
		{
			cout << "Arr" << i << ":" << arr[i] << endl;
			//cout << "auxArr" << i << "Before : " << auxArr[i] << endl; // 전부 0으로 나온다. 초기화가 어디서 되는거지 싶은데..
		}


		for (int i = 0; i < arrLen; i++)
		{

			// 현재 countArr의 값에 맞춰 auxArr 에 값 집어넣기 + 해당 countArr 값 1증가sj
			//auxArr[coguntArr[(arr[i]->*funcPtr)()]++] = *(arr[i]->GetSelf()); // 배열 이름을 안잡아주는건 무슨 깡패짓이냐 컴파일러야.. 아이고...
			// 아니 왜 arr[i]는 (애 객체일텐데) 안되고 한번 꼬아서 가면 되는거야?... 이 꼼수는 좀 기억해두자. 
			// auxArr[countArr[(arr[i]->*funcPtr)()]] = arr[i]; //arr[i]; //arr[i];
			auxArr[countArr[(arr[i]->*funcPtr)()]] = arr[i]; //arr[i]; //arr[i];
			countArr[(arr[i]->*funcPtr)()]++;
			
			//auxArr[countArr[0]] = NULL; //arr[i];
			//cout << countArr[i] << endl;

		}

		for (int i = 0; i < arrLen; i++) // 디버그 
		{
			cout << "auxArr" << i << "After : " << auxArr[i] << endl; // 나는 auxArr 2에 값을 넣었는데, 값 확인은 0에서 하고 있다. 이게 잘못됭넜네!!
		}

		for (int i = 0; i < arrLen; i++)
		{
			// aux 값을 arr로 넣어주자
			arr[i] = auxArr[i];
		}

		for (int i = 0; i < arrLen; i++) //디버그 
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
//	// 일단 모두 1서버로 생성.. 전투력 기준으로 줄세워보자
//	
//
//	//charinfo* ci1 = new charinfo("간장게장", 0, 2, 2160);
//	//charinfo* ci2 = new charinfo("양념게장", 1, 1, 4506);
//	//charinfo* ci3 = new charinfo("한방주님", 2, 0, 9998);
//	//charinfo* ci4 = new charinfo("또라이몽", 3, 2, 7549);
//
//	const int Radix = 10000; // 기수란 숫자의 자리수입니다. 예를 들면 숫자 42는 4와 2의 두개의 자리수를 가지고 이것이 기수가 됩니다. 
//		// 기수정렬은 이러한 자리수의 값에 따라 정렬을 하기 때문에 기수정렬이라는 이름을 얻었습니다. 
//		// 기수가 가질 수 있는 경우에 수를 Radix로 보는 것인데. 서버가 1~3까지만 있으면 radix는 3인것 (count[radix+1]이 되겠지)
//
//	const int arrLen = 10;
//	CharInfo* arr[arrLen]; // 포인터 배열. 배열의 길이는 인자로 넘기지 않고, sorting 함수측에서 파악
//	// const int가 아니라 int 로 값을 넘기면 에러가 난다. 배열의 크기는 상수로 지정되어야 한다.
//	
//	for (int i = 0; i < arrLen; i++)
//	{
//		arr[i] = new CharInfo("이름없음", i, RandNum(0,2), RandNum(0, 10000));
//		arr[i]->ShowInfo();
//	}
//
//	// 배열의 각 포인터에 객체의 주소를 넣어둠
//
//	// 아래 표현은 전부 정상 작동한다
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
//	//KeyIndexedCounting::Sort<CharInfo>(arr, arrLen, 3, &CharInfo::GetSvr); // 앞에 &안붙이면 에러난다. ::로 함수가 어디 소속인지 알려줘야 한다. // 맴버함수는 이름이 주소로 출력되지 않는다 1로 나온다 그냥. 구글링 해봐도 정상적인 방법으로는 없다는 듯.
//	KeyIndexedCounting::Sort<CharInfo>(arr, arrLen, Radix, &CharInfo::GetPower);
//	cout << "AFTER====================== 전투력 소팅!" << endl;
//	
//	for (int i = 0; i < arrLen; i++)
//	{
//		arr[i]->ShowInfo();
//	}
//
//	cout << "AFTER====================== 서버 소팅!" << endl;
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

	// string 이 문자 몇개로 이뤄져 있는지는 그냥 함수 쓰면 됨

	for (int j = strArr[0].length(); j>0 ; j--)
	{
		cout << j << endl;
		
		const int radix = 256;

		int countArr[radix + 1] = {0,};

		// 각 스트링을 순회하며 j 번째 요소를 카운팅
		for (int k = 0; k < arrLen; k++)
		{
			countArr[strArr[k].at(j-1) + 1]++;
		}
		
		// 카운팅 누적 계산
		for (int i = 1 ; i < radix +1 ; i++)
		{
			countArr[i] = countArr[i - 1] + countArr[i];
			cout << i << "번째 누적" << countArr[i] << endl;
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

	// 동일한 길이의 문자열을 여러개 받는다

	const int LEN = 5;
	const int STR_COUNT = 1000;

	string strArr[STR_COUNT];

	for (int i = 0; i < STR_COUNT; i++)
	{
		// char 배열 생성
		char cArr[LEN];
		for (int j = 0; j < LEN; j++)
		{
			if (j != LEN - 1)
			{
				// 만약 마지막 배열 요소가 아니라면 랜덤한 값을 넣는다
				cArr[j] = RandNum('a', 'z');
			}
			else
			{
				// 배열 마지막 요소의 값은 0으로 지정
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


	// 오름차순일지, 내림차순일지는 소팅 함수 호출시 인자로 지정할 수 있다
	// string 배열을 받아 소팅시킨다


	return 0;
}