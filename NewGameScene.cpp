#include "NewGameScene.h"
#include "Input.h"
#include <DxLib.h>
#include "SceneManager.h"
#include "GamePlayScene.h"

void NewGameScene::Load()
{
}

void NewGameScene::Init()
{
}

void NewGameScene::Update()
{
	if (KeyTriggered(KEY_INPUT_SPACE))
	{
		SceneManager::ChangeScene<GamePlayScene>();
	}
}

void NewGameScene::Draw()
{
	DrawBox(0, 0, 1280, 720, 0x33dd33, true);
	DrawString(100, 100, "Scene: NewGame\nPress Space to Change Scene", 0xffffff);
}
