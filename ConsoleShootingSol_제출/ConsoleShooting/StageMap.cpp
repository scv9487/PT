
#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include "StageMap.h"
#include "EnemyUnit.h"
#include "json/json.h"

using namespace std;
extern EnemyUnit enemyArr[ENEMY_COUNT];

void LoadStageMap(int mapNum)
{
	wstring mapFileName;
	mapFileName = _T("Stage") + to_wstring(mapNum) + _T(".txt");

	HANDLE hFile = CreateFileW(mapFileName.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		cout << "CreateFile에서 오류 발생" << endl;
	}

	char charArr[1000];

	int retVal;
	DWORD bytesRead;

	retVal = ReadFile(hFile, charArr, 1000, &bytesRead, 0);
	if (retVal != true)
	{
		cout << "파일 읽기 실패" << endl;
	}

	charArr[bytesRead] = '\0';
	string str = charArr; // Jsoncpp를 활용하기 위해 string으로 취급

	Json::Reader jsonReader;
	Json::Value root;
	bool parsingRet = jsonReader.parse(str, root);

	for (size_t i = 0; i < ENEMY_COUNT; i++) // 적 유닛 배열을 순회하며 읽어온 Json 데이터로 위치 지정 및 초기 세팅
	{
		enemyArr[i].posX = root[i]["posX"].asUInt();
		enemyArr[i].posY = root[i]["posY"].asUInt();
		enemyArr[i].hp = ENEMY_HP;
		enemyArr[i].isAlive = true;
	}
}