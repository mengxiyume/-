#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include "resource.h"

HINSTANCE g_hRootInstance;

TCHAR g_szClassName[] = TEXT("����ɽ�����Ĺ�");
TCHAR g_szWindowName[] = TEXT("����");

void MessageProc_WM_COMMAND(HWND hWnd, WPARAM wParam, LPARAM lParam) {
    switch (HIWORD(wParam)) {
    case 0:
        switch (LOWORD(wParam)) {
        case ID_CLOSS_ALL_WND:
            //�رճ������
            PostMessage(hWnd, WM_QUIT, 0, 0);
            break;
        default:
            break;
        }
        break;
    case 1:
        //�ռ�֪ͨ����
        break;
    default:
        return;
    }
}

void MessageProc_WM_CREATE(HWND hWnd) {

}

void GetMyNewWindow() {
    srand(GetTickCount64());
    RECT wndSize = { 0 };
    wndSize.right = 200;
    wndSize.bottom = 200;

    HWND hWnd = CreateWindowEx(WS_EX_ACCEPTFILES, g_szClassName, g_szWindowName, WS_OVERLAPPEDWINDOW,
        /*CW_USEDEFAULT*/ rand() % (GetSystemMetrics(SM_CXSCREEN) - wndSize.right),
        /*CW_USEDEFAULT*/ rand() % (GetSystemMetrics(SM_CYSCREEN) - wndSize.bottom),
        wndSize.right, wndSize.bottom,    //�������ɳߴ����� 
        NULL, NULL, g_hRootInstance, NULL);;
    UpdateWindow(hWnd);
    ShowWindow(hWnd, SW_SHOW);
    HMENU hMenu = LoadMenu(g_hRootInstance, MAKEINTRESOURCE(IDR_MENU1));
    SetMenu(hWnd, hMenu);
}

LRESULT CALLBACK WndMessageProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
    switch (msgID) {
    case WM_CLOSE:
        ////�ر�
        //PostMessage(hWnd, WM_QUIT, 0, 0);
        //����֮ǰ�Ĵ��� 
        DestroyWindow(hWnd);
        //���´���,����Ķ࿪����
        GetMyNewWindow();
        return 0;
    case WM_COMMAND:
        MessageProc_WM_COMMAND(hWnd, wParam, lParam);
        return 0;
    case WM_CREATE:
        MessageProc_WM_CREATE(hWnd);
        return 0;
    default:
        return DefWindowProc(hWnd, msgID, wParam, lParam);
    }
}

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
) {
    g_hRootInstance = hInstance;

    WNDCLASSEX wcEx = { 0 };
    wcEx.cbSize = sizeof(wcEx);
    wcEx.hbrBackground = CreateSolidBrush(0xEFEFEF);
    wcEx.lpszClassName = g_szClassName;
    wcEx.hInstance = hInstance;
    wcEx.lpfnWndProc = WndMessageProc;
    wcEx.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    RegisterClassEx(&wcEx);

    GetMyNewWindow();

    MSG msg = { 0 };
    while (TRUE)
    {
        if (PeekMessage(&msg, NULL, PM_NOREMOVE, 0, 0))
        {
            //��Ϣ�ַ�
            if (GetMessage(&msg, NULL, 0, 0) == FALSE) {
                //�رհ�ť�˳�����
                break;
            }
            else
            {
                //�ַ���Ϣ
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            //��������
            continue;
        }
    }

    UnregisterClass(g_szClassName, hInstance);

    return 0;
}