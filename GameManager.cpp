#include "GameManager.h"

#include "MyUtil.h"

#include <ctime>

GameManager::GameManager()
	:input(new InputManager())
{ }

GameManager::~GameManager()
{
	delete player;

	for (int i = 0; i < enemies.size(); ++i)
		delete enemies[i];

	delete input;
}

void GameManager::Init()
{
	// 화면의 가로, 세로 크기를 가져옵니다.
	screenW = GetSystemMetrics(SM_CXSCREEN);
	screenH = GetSystemMetrics(SM_CYSCREEN);

	// 배경 이미지 파일을 불러옵니다.
	image = new Image(L"images/cat.png");

	// 이미지 파일의 가로, 세로 크기를 가져옵니다.
	imageW = image->GetWidth();
	imageH = image->GetHeight();

	// 이미지 파일의 영역을 설정합니다.
	RECT rect = { 0, 0, imageW, imageH };

	Point start;
	OpenRandomArea(start);

	// 플레이어를 생성합니다, 초기 위치를 설정합니다.
	player = new Player(start.X, start.Y, rect);

	for (int i = 0; i < 10; ++i)
	{
		Enemy* newEnemy = new Enemy(start.X + 100, start.Y + 100, rect);
		enemies.push_back(newEnemy);
	}
}

void GameManager::Update()
{
	// 업데이트 주기를 조절합니다.

	DWORD newTime = GetTickCount();
	static DWORD oldTime = newTime;

	if (newTime - oldTime < 16)
		return;

	oldTime = newTime;

	// 플레이어의 입력값을 가져옵니다.
	int dirX = input->GetHorizontal();
	int dirY = input->GetVertical();
	bool space = input->GetKeySpace();
	
	if (space)	// 닫힌 영역을 경로를 그리면서 지나갑니다.
		player->MoveWithSpace(dirX, dirY, opened);
	else if (dirX == 0 && dirY == 0)	// 경로를 따라 되돌아 갑니다.
		player->MoveBack();
	else // 열린 영역 경로위에서 이동합니다.
		player->MoveWithoutSpace(dirX, dirY, opened);

	// 적 이동
	for (Enemy* &enemy : enemies)
		enemy->Move(opened);
}

const int MOVE_AMOUNT = 4;

void GameManager::OpenRandomArea(Point& start)
{
	srand((unsigned int)time(NULL));

	int randW = imageW / MOVE_AMOUNT + 4;
	int randH = imageH / MOVE_AMOUNT + 4;

	int startX = (rand() % (randW / 2)) * MOVE_AMOUNT;
	int startY = (rand() % (randH / 2)) * MOVE_AMOUNT;

	int endX = startX + (rand() % (randW / 4)) * MOVE_AMOUNT + MOVE_AMOUNT;
	int endY = startY + (rand() % (randH / 4)) * MOVE_AMOUNT + MOVE_AMOUNT;

	start = {startX, startY};

	// 초기 열린 영역을 설정합니다.
	// 시계방향으로 저장합니다.
	opened.push_back({ startX, startY });
	opened.push_back({ endX, startY});
	opened.push_back({ endX, endY });
	opened.push_back({ startX, endY });
}

// 닫힌 영역을 그립니다.
void GameManager::DrawClosed(Graphics * graphic)
{
	SolidBrush brush(Color(255, 0, 0, 0));
	graphic->FillRectangle(&brush, 0, 0, imageW, imageH);
}

// 열린 영역을 그립니다. 폴리곤 모양으로 클리핑 합니다.
void GameManager::DrawOpened(Graphics * graphic)
{
	Point *points = new Point[opened.size()];

	for (int i = 0; i < opened.size(); ++i)
		points[i] = opened[i];

	GraphicsPath path;

	path.AddPolygon(points, (int)opened.size());
	Region region(&path);

	graphic->SetClip(&region);

	graphic->DrawImage(image, 0, 0, imageW, imageH);

	Pen pen(Color(255, 0, 255, 255));
	graphic->DrawPath(&pen, &path);

	graphic->ResetClip();

	delete[] points;
}

// 게임 플레이를 그립니다.
void GameManager::DrawGame(Graphics *graphic)
{
	DrawClosed(graphic);
	DrawOpened(graphic);
	player->DrawPlayer(graphic);

	for (Enemy* &enemy : enemies)
		enemy->DrawEnemy(graphic);
}

// 게임전체를 그립니다. 더블 버퍼링을 사용합니다.
void GameManager::Draw(HWND hWnd, HDC hdc)
{
	HDC memDC;
	HBITMAP oldBit, newBit;

	memDC = CreateCompatibleDC(hdc);

	newBit = CreateCompatibleBitmap(hdc, imageW, imageH);
	oldBit = (HBITMAP)SelectObject(memDC, newBit);

	Graphics *graphic = new Graphics(memDC);

	// 픽셀 흐려짐 방지
	graphic->SetCompositingQuality(CompositingQuality::CompositingQualityAssumeLinear);
	graphic->SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);
	graphic->SetInterpolationMode(InterpolationMode::InterpolationModeHighQualityBicubic);
	graphic->SetPixelOffsetMode(PixelOffsetMode::PixelOffsetModeHighQuality);

	DrawGame(graphic);

	delete graphic;

	BitBlt(hdc, 0, 0, imageW, imageH, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBit);
	DeleteObject(newBit);

	DeleteDC(memDC);
}
