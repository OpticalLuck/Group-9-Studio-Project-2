#include "SceneManager.h"
#include "SceneCity.h"
#include "SceneLibrary.h"
#include "SceneHall.h"
#include "SceneTrain.h"
#include "Application.h"
#include "SceneStadium.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "shader.hpp"

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

	SceneArr[SCENE_TRAIN] = new SceneTrain();

	SceneArr[SCENE_GAMEOVER] = new GameOver();

}

SceneManager::~SceneManager()
{
	delete static_cast<MainMenu*>(SceneArr[SCENE_MAINMENU]);
	delete static_cast<SceneCity*>(SceneArr[SCENE_CITY]);
	delete static_cast<SceneLibrary*>(SceneArr[SCENE_LIBRARY]);
	delete static_cast<SceneHall*>(SceneArr[SCENE_HALL]);
	delete static_cast<SceneStadium*>(SceneArr[SCENE_STADIUM]);
	delete static_cast<SceneTrain*>(SceneArr[SCENE_TRAIN]);
	delete static_cast<GameOver*>(SceneArr[SCENE_GAMEOVER]);

	Shader::Destroy();
	TextureList::Destroy();
	MeshList::Destroy();
	TextData::Destroy();
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

	if (SceneArr[SCENE_STADIUM]->getQuestStatus() == true && SceneArr[SCENE_LIBRARY]->getQuestStatus() == true && SceneArr[SCENE_CITY]->getQuestStatus() == true)
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


		if (getCurrentSceneType() == SCENE_MAINMENU || getCurrentSceneType() == SCENE_GAMEOVER)
		{
			if (Application::Cursor_Off)
			Application::EnableCursor();
		}
		else
		{
			if(!Application::Cursor_Off)
				Application::DisableCursor();
		}
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

