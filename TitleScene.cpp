#include "TitleScene.h"
#include "Input.h"
#include <DxLib.h>
#include "SceneManager.h"
#include "NewGameScene.h"

void TitleScene::Load()
{
}

void TitleScene::Init()
{
}

void TitleScene::Update()
{
	if (KeyTriggered(KEY_INPUT_SPACE))
	{
		SceneManager::ChangeScene<NewGameScene>();
	}
}

void TitleScene::Draw()
{
	DrawBox(0, 0, 1280, 720, 0xdd3333, true);
	DrawString(100, 100, "Scene: Title\nPress Space to Change Scene", 0xffffff);
}
