#pragma once
#include "Scene.h"
#include "timer.h"
class SceneManager
{
public:
	enum SCENE_TYPE
	{
		SCENE_CITY,
		SCENE_LIBRARY,
		SCENE_TEST,
		SCENE_NPCTEST,
		SCENE_HALL,
		SCENE_TOTAL
	};

	SceneManager();
	~SceneManager();

	void Init(SCENE_TYPE NextScene);
	void Update(StopWatch* m_timer);
	void Render();
	static void ChangeScene(SCENE_TYPE NextScene);
	void Quit();

private:
	static Scene* SceneArr[SCENE_TOTAL];
	static Scene* mainScene;
	static SCENE_TYPE CurrentScene;
};

