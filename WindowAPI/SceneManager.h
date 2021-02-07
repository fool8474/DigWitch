#pragma once
#include "singletonBase.h"

class Scene;

class SceneManager : public singletonBase <SceneManager>
{
private:
	typedef map<string, Scene*> mSceneList;
	typedef map<string, Scene*>::iterator miSceneList;

private:
	mSceneList _mSceneList;			//각각의 씬(화면)들을 담아둘 맵
	Scene* _currentScene;		//현재씬

public:
	HRESULT init();
	void release();
	void update();
	void render();

	Scene* addScene(string sceneName, Scene* scene);
	HRESULT loadScene(string sceneName);

	SceneManager() : _currentScene(NULL) {}
	~SceneManager() {}
};

