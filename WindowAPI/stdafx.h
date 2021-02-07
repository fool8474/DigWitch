// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
#pragma once
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#include <SDKDDKVer.h>


#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <Windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
// C++ 런타임 헤더 파일입니다.
#include <iostream>
using namespace std;

// 자주사용하는 STL
#include <string>
#include <vector>
#include <map>

//=============================================================
//	## 내가 만든 헤더파일을 이곳에 추가한다 ##
//=============================================================
#include "commonMacroFunction.h"
#include "input.h"
#include "random.h"
#include "imageManager.h"
#include "CameraManager.h"
#include "UIManager.h"
#include "NPCManager.h"
#include "util.h"
#include "textData.h"
#include "DataManager.h"
#include "SceneManager.h"
#include "GridManager.h"
#include "ParticleManager.h"
using namespace MY_UTIL;


//=============================================================
//	## 싱글톤을 추가한다 ##
//=============================================================
#define INPUT input::getSingleton() //세미콜론 찍으면 작동안함
#define RANDOM random::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define CAMERAMANAGER cameraManager::getSingleton()
#define UIMANAGER	UIManager::getSingleton()
#define NPCMANAGER NPCManager::getSingleton()
#define DATAEXTRACTOR textData::getSingleton()
#define DATAMANAGER DataManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define GRIDMANAGER GridManager::getSingleton()
#define PARTICLEMANAGER particleManager::getSingleton()
//=============================================================
//	## 디파인문 ## (윈도우창 초기화)
//=============================================================
#define WINNAME (LPTSTR)(TEXT("파는마녀"))
#define WINSTARTX	-10
#define WINSTARTY	-10
#define WINSIZEX	1920
#define WINSIZEY	1080
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

//=============================================================
//	## 매크로함수 ## (클래스에서 동적할당된 부분 해제)
//=============================================================
#define SAFE_DELETE(p)		{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}

//=============================================================
//	## 전역변수 ##
//=============================================================
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
extern int			_mouseWheel;
