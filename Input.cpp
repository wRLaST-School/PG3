#include "Input.h"
#include "Input.h"
#include <DxLib.h>

// 最新のキーボード情報用
char keys[256] = { 0 };

// 1ループ(フレーム)前のキーボード情報
char oldkeys[256] = { 0 };

int mouseX = 0, mouseY = 0;

int mouseState = 0, lastMouseState = 0;

void UpdateInputs()
{
	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for (int i = 0; i < 256; i++) {
		oldkeys[i] = keys[i];
	}
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);

	lastMouseState = mouseState;

	mouseState = GetMouseInput();

	GetMousePoint(&mouseX, &mouseY);
}

bool KeyTriggered(int key)
{
	return keys[key] && !oldkeys[key];
}

bool KeyPress(int key)
{
	return keys[key];
}

bool KeyReleased(int key)
{
	return !keys[key] && oldkeys[key];
}

bool AnyKeyPress()
{
	for (auto k : keys)
	{
		if (k)
		{
			return true;
		}
	}

	return false;
}

bool MouseTriggered(int button)
{
	return mouseState & button && !(lastMouseState & button);
}

bool MousePress(int button)
{
	return mouseState & button;
}

bool MouseRelease(int button)
{
	return !(mouseState & button) && lastMouseState & button;
}

int GetMouseX()
{
	return mouseX;
}

int GetMouseY()
{
	return mouseY;
}

