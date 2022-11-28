#include "SceneManager.h"
#include "TitleScene.h"

void SceneManager::Init()
{
	ChangeScene<TitleScene>();
}

void SceneManager::Update()
{
	sceneChanged = false;
	currentScene->Update();
}

void SceneManager::Draw()
{
	//if (!sceneChanged)
	//{
		currentScene->Draw();
	//}
}
unique_ptr<IScene> SceneManager::currentScene;
bool SceneManager::sceneChanged = false;