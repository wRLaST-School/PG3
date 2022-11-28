#include "GamePlayScene.h"
#include "Input.h"
#include <DxLib.h>
#include "SceneManager.h"
#include "GameClearScene.h"

void GamePlayScene::Load()
{
}

void GamePlayScene::Init()
{
}

void GamePlayScene::Update()
{
	if (KeyTriggered(KEY_INPUT_SPACE))
	{
		SceneManager::ChangeScene<GameClearScene>();
	}
}

void GamePlayScene::Draw()
{
	DrawBox(0, 0, 1280, 720, 0x3333dd, true);
	DrawString(100, 100, "Scene: GamePlay\nPress Space to Change Scene", 0xffffff);
}
