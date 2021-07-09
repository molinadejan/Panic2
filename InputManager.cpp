#include "InputManager.h"
#include <windows.h>

void InputManager::CheckKeyboardInput()
{
	is_key_up    = false;
	is_key_down  = false;
	is_key_left  = false;
	is_key_right = false;
	is_key_space = false;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		is_key_space = true;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		is_key_left = true;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		is_key_right = true;

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		is_key_down = true;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		is_key_up = true;
}

void InputManager::Update()
{
	DWORD newTime = GetTickCount();
	static DWORD oldTime = newTime;

	if (newTime - oldTime < 16)
		return;

	oldTime = newTime;

	CheckKeyboardInput();
}
