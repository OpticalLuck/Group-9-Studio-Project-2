#include "SceneManager.h"
#include "SceneCity.h"
#include "SceneNPCTest.h"
#include "SceneTest.h"
#include "SceneLibrary.h"
#include "SceneHall.h"
#include "SceneTrain.h"
#include "Application.h"

SceneManager::SCENE_TYPE SceneManager::CurrentScene;
Scene* SceneManager::mainScene = nullptr;
Scene* SceneManager::SceneArr[SCENE_TOTAL];

SceneManager::SceneManager()
{
	SceneArr[SCENE_CITY] = new SceneCity();

	SceneArr[SCENE_LIBRARY] = new SceneLibrary();

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
		mainScene->Init();
	}
	mainScene->InitGL();
}

void SceneManager::Update(StopWatch* m_timer)
{
	mainScene->UpdateMousePos(Application::xoffset, Application::yoffset);
	mainScene->Update(m_timer->getElapsedTime());
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

void SceneManager::Quit()
{
}

