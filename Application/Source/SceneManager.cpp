#include "SceneManager.h"
#include "SceneCity.h"
#include "SceneLibrary.h"
#include "SceneHall.h"
#include "SceneTrain.h"
#include "Application.h"
#include "SceneStadium.h"
#include "MainMenu.h"

//TO BE REMOVED
#include "SceneTest.h"
#include "SceneNPCTest.h"

SceneManager::SCENE_TYPE SceneManager::CurrentScene;
Scene* SceneManager::mainScene = nullptr;
Scene* SceneManager::SceneArr[SCENE_TOTAL];

SceneManager::SceneManager()
{
	SceneArr[SCENE_MAINMENU] = new MainMenu();

	SceneArr[SCENE_CITY] = new SceneCity();

	SceneArr[SCENE_LIBRARY] = new SceneLibrary();

	SceneArr[SCENE_HALL] = new SceneHall();
	
	SceneArr[SCENE_STADIUM] = new SceneStadium();

	SceneArr[SCENE_NPCTEST] = new SceneNPCTest();

	SceneArr[SCENE_TEST] = new SceneTest();

	SceneArr[SCENE_HALL] = new SceneHall();

	SceneArr[SCENE_TRAIN] = new SceneTrain();
}

SceneManager::~SceneManager()
{
	for (int i = 0; i < SCENE_TOTAL; i++)
	{
		delete SceneArr[i];
	}
}

void SceneManager::Init(SCENE_TYPE NextScene)
{
	mainScene = SceneArr[NextScene];
	CurrentScene = NextScene;
	if (!mainScene->isInit)
	{
		std::cout << "INIT SCENE" << std::endl;
		mainScene->Init();
	}
	mainScene->InitGL();
}

void SceneManager::Update(StopWatch* m_timer)
{
	mainScene->UpdateMousePos(Application::xoffset, Application::yoffset);
	mainScene->Update(m_timer->getElapsedTime());

	if (SceneArr[SCENE_TEST]->getQuestStatus() == true)
	{
		SceneArr[SCENE_HALL]->setQuestStatus(true);
	}

}

void SceneManager::Render()
{
	mainScene->Render();
}

void SceneManager::ChangeScene(SCENE_TYPE NextScene)
{
	if (CurrentScene != NextScene)
	{
		mainScene->Exit();
		CurrentScene = NextScene;
		mainScene = SceneArr[NextScene];
		if (!mainScene->isInit)
		{
			mainScene->Init();
		}
		mainScene->InitGL();
	}
}

bool SceneManager::getQuestStatus(SCENE_TYPE NextScene)
{
	return SceneArr[NextScene]->getQuestStatus();
}

SceneManager::SCENE_TYPE SceneManager::getCurrentSceneType()
{
	return CurrentScene;
}

Scene* SceneManager::getCurrentScene()
{
	return mainScene;
}

void SceneManager::Quit()
{
}

