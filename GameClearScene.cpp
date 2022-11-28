#include "GameClearScene.h"
#include "Input.h"
#include <DxLib.h>
#include "SceneManager.h"
#include "TitleScene.h"

void GameClearScene::Load()
{
}

void GameClearScene::Init()
{
}

void GameClearScene::Update()
{
	if (KeyTriggered(KEY_INPUT_SPACE))
	{
		SceneManager::ChangeScene<TitleScene>();
	}
}

void GameClearScene::Draw()
{
	DrawBox(0, 0, 1280, 720, 0x333333, true);
	DrawString(100, 100, "Scene: GameClear\nPress Space to Change Scene", 0xffffff);
}
