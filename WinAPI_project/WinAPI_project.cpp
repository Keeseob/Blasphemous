﻿//수정: 0223
// WinAPI_project.cpp : 애플리케이션에 대한 진입점을 정의합니다.

#include "framework.h"
#include "WinAPI_project.h"
#include "application.h"
#include "sceneManager.h" 
#include "bpResources.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

BP::application bp_application; //bp_application객체를 전역 변수 선언

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance, LPCWSTR name, WNDPROC proc);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK subWindow(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// SAL
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(217); //추가
	// 1. 윈도우의 정보를 담고있는 클래스를 정의(메모리에 등록)해주어야한다.
	// 2. CreateWindow함수를 통해서 메모리상에 윈도우를 할당해준다.
	// 3. ShowWindow함수를 통해서 화면에 보여준다.
	// 4. 윈도우 클래스를 정의할떄 등록된 메서지 처리함수를
	// 순회하면서 들어오는 메세지를 처리해준다.

	// TODO: 여기에 코드를 입력합니다.
	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINAPIPROJECT, szWindowClass, MAX_LOADSTRING);
	// main 윈도우 정보 등록
	MyRegisterClass(hInstance, szWindowClass, WndProc);

	//tile window
	MyRegisterClass(hInstance, L"subWindow", subWindow);

	//윈도우 생성
	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// 단축키 테이블 정보 불러오기
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIPROJECT));

	MSG msg;

	// 기본 메시지 루프입니다:
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message) // 윈도우 종료 메세지가 들어 왔을 때, 반복문 종료
			{
				break;
			}
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // 윈도우 메세지가 있을 때 실행
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else // 윈도우 관련 메세지가 없을 경우 항상 게임 실행
		{
			bp_application.run();
		}
	}
	BP::sceneManager::release();
	BP::bpResources::release();

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
// 
ATOM MyRegisterClass(HINSTANCE hInstance, LPCWSTR name, WNDPROC proc)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = proc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIPROJECT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINAPIPROJECT);
	wcex.lpszClassName = name;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, L"Blasphemous", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 1600, 900, nullptr, nullptr, hInstance, nullptr);


	HWND hWnd2 = CreateWindowW(L"subWindow", szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 500, 500, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	ShowWindow(hWnd2, nCmdShow);
	UpdateWindow(hWnd2);

	bp_application.initialize(hWnd);

	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
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

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
