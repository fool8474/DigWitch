#pragma once
#include "singletonBase.h"
#include <vector>
#include <string>
#include <sstream>

class textData : public singletonBase<textData>
{
public:
    textData();
    ~textData();

    HRESULT init();
    void release();

    void txtSave(const char* saveFileName, vector<string> vStr);
    vector<vector<string>> txtLoad(const char* loadFileName);
private:
    char* vectorArrayCombine(vector<string> vArray);
    vector<string> charArraySeparation(char charArray[]);
    vector<vector<string>> charArraySeparationSub(vector<string> stringVec);
};