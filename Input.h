#pragma once

//毎フレーム呼んでね
void UpdateInputs();

bool KeyTriggered(int key);
bool KeyPress(int key);
bool KeyReleased(int key);
bool AnyKeyPress();

bool MouseTriggered(int button);
bool MousePress(int button);
bool MouseRelease(int button);

int GetMouseX();
int GetMouseY();

