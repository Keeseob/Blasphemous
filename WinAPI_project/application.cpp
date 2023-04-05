#include "application.h"
#include "sceneManager.h"
#include "time.h"
#include "keyInput.h"
#include "collisionManager.h"
#include "camera.h"

namespace BP
{
	application::application() : mHwnd(NULL), mHdc(NULL)
	{
	}
	application::~application()
	{
		//sceneManager::release();
	}

	void application::initialize(HWND hWnd)
	{
		mHwnd = hWnd;
		mHdc = GetDC(hWnd);
		mWidth = 1600;
		mHeight = 900;

		//해상도 설정을 위한 윈도우 크기 계산
		RECT rect = { 0, 0, mWidth,mHeight };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		//윈도우 크기 변경 및 출력
		SetWindowPos(mHwnd
			, nullptr, 45, 50
			, (rect.right - rect.left)
			, (rect.bottom - rect.top)
			, 0);
		ShowWindow(hWnd, true);

		mBackBuffer = CreateCompatibleBitmap(mHdc, mWidth, mHeight);
		mBackHdc = CreateCompatibleDC(mHdc);
		HBITMAP defaultBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(defaultBitmap);

		time::initialize();
		keyInput::initialize();
		sceneManager::initialize();
		camera::initialize();
	}

	void application::run()
	{
		update();
		render();
		sceneManager::destroy();
	}

	void application::update()
	{
		time::update();
		keyInput::update();
		camera::update();
		sceneManager::update();
		collisionManager::update();
	}

	void application::render()
	{
		//clear
		backgroundBlack();

		time::render(mBackHdc);
		keyInput::render(mBackHdc);
		sceneManager::render(mBackHdc);
		camera::render(mBackHdc);
		//백버퍼 이미지 생성 후, 메인 버퍼에 이미지를 생성해야 한다.
		BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHdc, 0, 0, SRCCOPY);
	}
	void application::backgroundBlack()
	{
		HBRUSH grayBrush = CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH oldbrush = (HBRUSH)SelectObject(mBackHdc, grayBrush);
		Rectangle(mBackHdc, -1, -1, 1602, 902);
		SelectObject(mBackHdc, oldbrush);
		DeleteObject(grayBrush);
	};
}