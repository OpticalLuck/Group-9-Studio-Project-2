#pragma once
#include "Scene.h"
#include "timer.h"
class SceneManager
{
public:
	enum SCENE_TYPE
	{
		SCENE_MAINMENU,
		SCENE_CITY,
		SCENE_LIBRARY,
		SCENE_HALL,
		SCENE_STADIUM,

		SCENE_TEST,
		SCENE_NPCTEST,
		SCENE_TRAIN,
		SCENE_TOTAL
	};

	SceneManager();
	~SceneManager();

	void Init(SCENE_TYPE NextScene);
	void Update(StopWatch* m_timer);
	void Render();
	static void ChangeScene(SCENE_TYPE NextScene);
	static bool getQuestStatus(SCENE_TYPE NextScene);
	static SCENE_TYPE getCurrentSceneType();
	static Scene* getCurrentScene();
	void Quit();

private:
	static Scene* SceneArr[SCENE_TOTAL];
	static Scene* mainScene;
	static SCENE_TYPE CurrentScene;
};

