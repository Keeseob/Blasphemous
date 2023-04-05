#pragma once
#include "engine.h"

namespace BP
{
	class application
	{
	public:
		application();
		~application();

		void initialize(HWND hWnd);
		void run();
		void update();
		void render();

		HWND getHwnd() { return mHwnd; }
		HDC getHdc() { return mHdc; }
		UINT getWidth() { return mWidth; }
		UINT getHeight() { return mHeight; }

	private:
		void backgroundBlack();

	private:
		HWND mHwnd;
		HDC mHdc;

		//back buffer
		HBITMAP mBackBuffer;
		HDC mBackHdc;

		UINT mWidth;
		UINT mHeight;

		vector2 mPosition;
	};
}