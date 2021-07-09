#pragma once

#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "framework.h"

#include "InputManager.h"
#include "Player.h"

#include <vector>

using namespace Gdiplus;
using std::vector;

class GameManager
{
private:

	// �Է� ����
	InputManager* input;

	// ��� �̹���, Ŀ��
	Image *image;

	// �÷��̾�
	Player *player;

	// ��ũ�� ũ��
	int screenW, screenH;

	// ��� �̹��� ũ��
	int imageW, imageH;

	vector<Point> opened;

	void DrawCover(Graphics *graphic);
	void DrawOpenedImage(Graphics *graphic);
	void DrawGame(Graphics *graphic);

public:
	GameManager();
	~GameManager();

	InputManager* Input() const { return input; }

	void Init();
	void Update();
	void Draw(HWND hWnd, HDC hdc);
};



#endif // !__GAMEMANAGER_H__
