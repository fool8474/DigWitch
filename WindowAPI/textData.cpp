#include "stdafx.h"
#include "textData.h"

textData::textData()
{
}

textData::~textData()
{
}

HRESULT textData::init()
{
	return S_OK;
}

void textData::release()
{
}

//Save
void textData::txtSave(const char* saveFileName, vector<string> vStr)
{
	HANDLE file;

	char str[128];
	DWORD write;

	strncpy_s(str, 128, vectorArrayCombine(vStr), 126);

	file = CreateFile(saveFileName, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, 128, &write, NULL);

	CloseHandle(file);
}

char* textData::vectorArrayCombine(vector<string> vArray)
{
	char str[128];

	ZeroMemory(str, sizeof(str));
	for (int i = 0; i < vArray.size(); i++)
	{
		strncat_s(str, 128, vArray[i].c_str(), 126);
		if (i + 1 < vArray.size()) strcat(str, ",");
	}

	return str;
}


// 행, 열의 결과로 Return된다.
vector<vector<string>> textData::txtLoad(const char* loadFileName)
{
	HANDLE file;

	char str[10000] = { 0, };
	DWORD read;

	file = CreateFile(loadFileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 10000, &read, NULL);

	CloseHandle(file);

	return charArraySeparationSub(charArraySeparation(str));
}

vector<string> textData::charArraySeparation(char charArray[])
{
	vector<string> vArray;

	char* temp;
	const char* separator = "\n";
	char* token;

	token = strtok(charArray, separator);
	vArray.push_back(token);

	while (NULL != (token = strtok(NULL, separator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}

vector<vector<string>> textData::charArraySeparationSub(vector<string> stringVec)
{
	vector<vector<string>> vvArray;
	for (int i = 0; i < stringVec.size(); i++)
	{
		string subString;

		vector<string> vArray;

		size_t previous = 0, current;
		current = stringVec[i].find(',');
		while (current != string::npos)
		{
			subString = stringVec[i].substr(previous, current - previous);
			if (subString.size() > 0 && subString[subString.size() - 1] == '\r')
			{
				subString.erase(subString.end() - 1);
			}
			vArray.push_back(subString);
			previous = current + 1;
			current = stringVec[i].find(',', previous);
		}

		subString = stringVec[i].substr(previous, current - previous);
		if (subString.size() > 0 && subString[subString.size() - 1] == '\r')
		{
			subString.erase(subString.end() - 1);
		}
		vArray.push_back(subString);
		vvArray.push_back(vArray);
	}

	vvArray.erase(vvArray.begin());
	return vvArray;
}