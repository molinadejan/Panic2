#include "GameManager.h"

GameManager::GameManager()
	:input(new InputManager())
{ }

GameManager::~GameManager()
{
	delete input;
}

void GameManager::Init()
{
	screenW = GetSystemMetrics(SM_CXSCREEN);
	screenH = GetSystemMetrics(SM_CYSCREEN);

	image = new Image(L"images/cat.png");

	imageW = image->GetWidth();
	imageH = image->GetHeight();

	RECT rect = { 0, 0, imageW, imageH };
	player = new Player(200, 200, rect);

	// 초기 열린 영역
	opened.push_back({ 200, 200 });
	opened.push_back({ 200, 300 });
	opened.push_back({ 300, 300 });
	opened.push_back({ 300, 200 });
}

void GameManager::Update()
{
	DWORD newTime = GetTickCount();
	static DWORD oldTime = newTime;

	if (newTime - oldTime < 16)
		return;

	oldTime = newTime;

	if (input->GetKeyDown())
		player->MovePlayer(0, 1, opened);
	else if (input->GetKeyUp())
		player->MovePlayer(0, -1, opened);

	if (input->GetKeyLeft())
		player->MovePlayer(-1, 0, opened);
	else if (input->GetKeyRight())
		player->MovePlayer(1, 0, opened);
}

void GameManager::DrawCover(Graphics * graphic)
{
	SolidBrush brush(Color(255, 0, 0, 0));
	graphic->FillRectangle(&brush, 0, 0, imageW, imageH);
}

void GameManager::DrawOpenedImage(Graphics * graphic)
{
	Point *points = new Point[opened.size()];

	for (int i = 0; i < opened.size(); ++i)
		points[i] = opened[i];

	GraphicsPath path;

	path.AddPolygon(points, opened.size());
	Region region(&path);

	graphic->SetClip(&region);

	graphic->DrawImage(image, 0, 0, imageW, imageH);

	Pen pen(Color(255, 0, 255, 255));
	graphic->DrawPath(&pen, &path);

	graphic->ResetClip();

	delete[] points;
}

void GameManager::DrawGame(Graphics *graphic)
{
	DrawCover(graphic);
	DrawOpenedImage(graphic);
	player->DrawPlayer(graphic);
}

void GameManager::Draw(HWND hWnd, HDC hdc)
{
	HDC memDC;
	HBITMAP oldBit, newBit;

	memDC = CreateCompatibleDC(hdc);

	newBit = CreateCompatibleBitmap(hdc, imageW, imageH);
	oldBit = (HBITMAP)SelectObject(memDC, newBit);

	Graphics *graphic = new Graphics(memDC);

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
