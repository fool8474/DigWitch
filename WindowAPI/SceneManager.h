#pragma once
#include "singletonBase.h"

class Scene;

class SceneManager : public singletonBase <SceneManager>
{
private:
	typedef map<string, Scene*> mSceneList;
	typedef map<string, Scene*>::iterator miSceneList;

private:
	mSceneList _mSceneList;			//������ ��(ȭ��)���� ��Ƶ� ��
	Scene* _currentScene;		//�����

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

