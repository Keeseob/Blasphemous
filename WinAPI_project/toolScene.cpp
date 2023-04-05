#include "toolScene.h"

namespace BP
{
	toolScene::toolScene()
	{
	}
	toolScene::~toolScene()
	{
	}

	void toolScene::initialize()
	{
		scene::initialize();
	}

	void toolScene::update()
	{
		scene::update();
	}

	void toolScene::render(HDC hdc)
	{
		scene::render(hdc);
	}

	void toolScene::release()
	{
		scene::release();
	}

	void toolScene::onEnter()
	{
	}
	void toolScene::onExit()
	{
	}
}

LRESULT CALLBACK subWindow(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		//case IDM_ABOUT:
		//	DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		//	break;
		//case IDM_EXIT:
		//	DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps); // Device Context(그리기 관련 핸들)
		//// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}