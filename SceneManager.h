#pragma once
#include "IScene.h"
#include <memory>

using namespace std;

class SceneManager final
{
public:
	template <class NextScene>
	static void ChangeScene();

	static void Init();
	static void Update();
	static void Draw();

private:
	static unique_ptr<IScene> currentScene;
	static bool sceneChanged;

private:
	SceneManager();
	~SceneManager() {};
	SceneManager(const SceneManager& o) = delete;
	SceneManager& operator=(const SceneManager& o) = delete;

};

template<class NextScene>
inline void SceneManager::ChangeScene()
{
	delete currentScene.release();
	currentScene = unique_ptr<NextScene>(new NextScene());
	currentScene->Load();
	currentScene->Init();

	sceneChanged = true;
}
