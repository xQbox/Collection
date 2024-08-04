#include <libmy.h>
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#define ClientAreaDelimetr 5

HMENU MyMenu(HWND hWnd)
{
    HMENU  hMenu = CreateMenu();


    HMENU hMenuPopup = CreateMenu();

    AppendMenuW(hMenuPopup, MF_POPUP, IDM_CREATE, L"Создать");
    AppendMenuW(hMenuPopup, MF_POPUP, IDM_OPEN, L"Открыть");
    AppendMenuW(hMenuPopup, MF_POPUP, IDM_SAVE, L"Сохранить");
    AppendMenuW(hMenuPopup, MF_POPUP, IDM_SAVEAS, L"Сохранить как...");
    AppendMenuW(hMenuPopup, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenuPopup, MF_POPUP, IDM_RECENT, L"Последние");
    AppendMenuW(hMenuPopup, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenuPopup, MF_POPUP, IDM_EXIT, L"Выход");

    AppendMenuW(hMenu, MF_POPUP, (UINT) hMenuPopup, L"Файл");


    hMenuPopup = CreateMenu();

    AppendMenuW(hMenuPopup, MF_POPUP, IDM_UNDO, L"Отменить");
    AppendMenuW(hMenuPopup, MF_POPUP, IDM_DELETE, L"Удалить");
    AppendMenuW(hMenuPopup, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenuPopup, MF_POPUP, IDM_CUT, L"Вырезать");
    AppendMenuW(hMenuPopup, MF_POPUP, IDM_COPY, L"Скопировать");
    AppendMenuW(hMenuPopup, MF_POPUP, IDM_PASTE, L"Вставить");

    AppendMenuW(hMenu, MF_POPUP, (UINT) hMenuPopup, L"Изменить");
    

    hMenuPopup = CreateMenu();

    AppendMenuW(hMenuPopup, MF_POPUP, IDM_AUTHOR, L"Об авторе");
    AppendMenuW(hMenuPopup, MF_POPUP, IDM_TASK, L"О задаче");

    AppendMenuW(hMenu, MF_POPUP, (UINT) hMenuPopup, L"О программе");


    AppendMenuW(hMenu, MF_POPUP, IDM_INFO, L"Справка");


    SetMenu(hWnd, hMenu);
    return hMenu;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    static HMENU hMenu;
    static HWND hWndSeniorChild;
    static HWND hWndPaintArea; 
    // static HWND hWndMiddleChild[3];
    static HWND hWndJuniorChild[8];

    static HWND hWndSmallerButton, hWndBiggerButton;

    static RECT userArea, userChildArea;
    static LPMINMAXINFO lpMMI; 

    static UINT32 uxView, uyView;
    HPEN hPen;

    static BOOL bClickedFlag;


    switch (iMsg)
    {
        case WM_CREATE:        
            hMenu = MyMenu(hWnd);
            GetClientRect(hWnd, &userArea);
            hWndSeniorChild = CreateWindowW(L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_BLACKFRAME, 0, 0, userArea.right / 5, userArea.bottom, hWnd, NULL, NULL, NULL);
            hWndPaintArea = CreateWindowW(L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_BLACKFRAME, userArea.right / 5, 0, userArea.right - userArea.right / 5, userArea.bottom, hWnd, NULL, NULL, NULL);

            GetClientRect(hWndSeniorChild, &userChildArea);
            
            UINT16 u16Step, u16PosLeft;
            u16Step = (userChildArea.bottom - userChildArea.top + ClientAreaDelimetr) / ClientAreaDelimetr;
            u16PosLeft = 0; 

            // for (size_t i = 0; i < sizeof(hWndMiddleChild) / sizeof(hWndMiddleChild[0]); ++i)
            // {
            //     hWndMiddleChild[i] = CreateWindowW(L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_BLACKRECT, userChildArea.left, u16PosLeft, userChildArea.right,  u16Step + (i % 2 * u16Step * 2), 
            //     hWndSeniorChild, NULL, NULL, NULL);
            //     u16PosLeft += u16Step + (i % 2 * u16Step * 2);
            // }
            

            GetClientRect(hWndPaintArea, &userChildArea);


            hWndSmallerButton = CreateWindowW(L"button", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, userChildArea.right - 100, userChildArea.bottom - 100, 50, 50, hWndPaintArea, (HMENU) IDC_BUTTONSMALLER, NULL, NULL);
            hWndBiggerButton = CreateWindowW(L"button", L"", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW, userChildArea.right - 180, userChildArea.bottom - 100, 50, 50, hWndPaintArea, (HMENU) IDC_BUTTONBIGGER, NULL, NULL); 


            GetClientRect(hWndMiddleChild[0], &userChildArea);
            hWndJuniorChild[0] = CreateWindowW(L"BUTTON", L"Задать точку:", WS_CHILD | WS_VISIBLE, 10, 20, 120, 30, hWndMiddleChild[0], (HMENU) IDC_BUTTONPOINT, NULL, NULL);
            hWndJuniorChild[1] = CreateWindowW(L"BUTTON", L"Соединить точки", WS_CHILD | WS_VISIBLE, 10, 60, 120, 30, hWndMiddleChild[0], (HMENU) IDC_BUTTONCONNECT, NULL, NULL);
            
            GetClientRect(hWndMiddleChild[1], &userChildArea);
            hWndJuniorChild[2] = CreateWindowW(L"BUTTON", L"Пиксель", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 20, 80, 30, hWndMiddleChild[1], (HMENU) IDC_BUTTONPIXEL, NULL, NULL);
            hWndJuniorChild[3] = CreateWindowW(L"BUTTON", L"Отрезок", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 10, 60, 80, 30, hWndMiddleChild[1], (HMENU) IDC_BUTTONSEGMENT, NULL, NULL);
            hWndJuniorChild[4] = CreateWindowW(L"BUTTON", L"Квадрат", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 10, 100, 80, 30, hWndMiddleChild[1], (HMENU) IDC_BUTTONSQUARE, NULL, NULL);
            hWndJuniorChild[5] = CreateWindowW(L"BUTTON", L"Квадрат", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 10, 140, 80, 30, hWndMiddleChild[1], (HMENU) IDC_BUTTONRECTANGLE, NULL, NULL);

            GetClientRect(hWndMiddleChild[2], &userChildArea);
            hWndJuniorChild[6] = CreateWindowW(L"BUTTON", L"Решить", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 100, 20, 80, 30, hWndMiddleChild[2], (HMENU) IDC_BUTTONSOLVE, NULL, NULL);
            hWndJuniorChild[7] = CreateWindowW(L"BUTTON", L"Применить", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 100, 60, 80, 30, hWndMiddleChild[2], (HMENU) IDC_BUTTONAPPLY, NULL, NULL);
            
            return 0;



        case WM_SIZE:
            uxView = LOWORD(lParam);
            uyView = HIWORD(lParam);

            GetClientRect(hWnd, &userArea);

            
            MoveWindow(hWndSeniorChild, userArea.left, userArea.top, userArea.right / 5, userArea.bottom, TRUE);
            MoveWindow(hWndPaintArea, userArea.right / 5, userArea.top, userArea.right - userArea.right / 5, userArea.bottom, TRUE);
            
    
            GetClientRect(hWndSeniorChild, &userChildArea);
            u16Step = (userChildArea.bottom - userChildArea.top + ClientAreaDelimetr) / ClientAreaDelimetr;
            u16PosLeft = 0; 

            for (size_t i = 0; i < sizeof(hWndMiddleChild) / sizeof(hWndMiddleChild[0]); ++i)
            {
                MoveWindow(hWndMiddleChild[i], userChildArea.left, u16PosLeft, userChildArea.right,  u16Step + (i % 2 * u16Step * 2), TRUE);
                u16PosLeft += u16Step + (i % 2 * u16Step * 2);
            }
            
            GetClientRect(hWndPaintArea, &userChildArea);


            MoveWindow(hWndSmallerButton, userChildArea.right - 100, userChildArea.bottom - 100, 50, 50, TRUE);
            MoveWindow(hWndBiggerButton, userChildArea.right - 180, userChildArea.bottom - 100, 50, 50, TRUE);

            return 0;
        case WM_GETMINMAXINFO:
            lpMMI = (LPMINMAXINFO) lParam;
            lpMMI->ptMinTrackSize.x = 700;
            lpMMI->ptMinTrackSize.y = 600;

        case WM_PAINT:
            HDC hdc;
            PAINTSTRUCT ps;
            
            GetClientRect(hWndPaintArea, &userChildArea);
            hdc = BeginPaint(hWndPaintArea, &ps);

// // Определяем размеры клиентской области окна
            SetMapMode(hdc, MM_ISOTROPIC);
            SetWindowExtEx(hdc, userChildArea.right, userArea.bottom, NULL);
            SetViewportExtEx(hdc, uxView, -uyView, NULL);
            SetViewportOrgEx(hdc, userChildArea.right / 2, userChildArea.bottom / 2, NULL);
            
            GetClientRect(hWnd, &userArea);
          

            hPen = CreatePen(PS_SOLID, 2, RGB(35, 40, 43));
            SelectObject(hdc, hPen);
// X    
            MoveToEx(hdc, 0, 0, NULL);
            LineTo(hdc, userArea.right, 0);
            MoveToEx(hdc, 0, 0, NULL);
            LineTo(hdc, - userArea.right, 0);

// Y
            MoveToEx(hdc, 0, 0, NULL);
            LineTo(hdc, 0, -userArea.bottom);
            MoveToEx(hdc, 0, 0, NULL);
            LineTo(hdc, 0, userArea.bottom);

            
            hPen = CreatePen(PS_SOLID, 1, RGB(35, 40, 43));
            SelectObject(hdc, hPen);

// Painting the step of splitting the axis
// X
            for (int i = 0; i < userChildArea.right / 2; i += 40)
            {
                MoveToEx(hdc, i, userChildArea.bottom , NULL);
                LineTo(hdc, i,  -userChildArea.bottom);    
            }

            for (int i = 0; i > -userChildArea.right / 2; i -= 40)
            {
                MoveToEx(hdc, i, userChildArea.bottom , NULL);
                LineTo(hdc, i, -userChildArea.bottom );
            }
// Y        
            for (int i = 0; i <  userChildArea.bottom / 2; i += 40)
            {
                MoveToEx(hdc, userArea.right, i, NULL);
                LineTo(hdc, -userArea.right, i);    
            }

            for (int i = 0; i > -userChildArea.bottom / 2; i -= 40)
            {
                MoveToEx(hdc, userArea.right, i, NULL);
                LineTo(hdc, -userArea.right, i);  
            }
            
            GetClientRect(hWndPaintArea, &userChildArea);
            
            
            SetTextColor(hdc, RGB(255, 0, 0));
            TextOutW(hdc, userChildArea.right / 2 - 10, -5, L"X", strlen("X"));
            TextOutW(hdc, 2, userChildArea.bottom / 2, L"Y", strlen("Y"));
            

            EndPaint(hWnd, &ps);
            
            InvalidateRect(hWndPaintArea, NULL, TRUE);

        case WM_MOUSEMOVE:
            if (!bClickedFlag)
            {return 0;}
            hdc = GetDC(hWndPaintArea);
        
            GetClientRect(hWndPaintArea, &userChildArea);
            IntersectClipRect(hdc, userChildArea.left, userChildArea.top, userChildArea.right, userChildArea.bottom);
            
            GetClientRect(hWndBiggerButton, &userChildArea);
            InvalidateRect(hWndBiggerButton, &userChildArea, TRUE);
            
            GetClientRect(hWndSmallerButton, &userChildArea);
            InvalidateRect(hWndSmallerButton, &userChildArea, TRUE);


            GetClientRect(hWndSeniorChild, &userChildArea);
            hPen = CreatePen(PS_SOLID, 1, RGB(255, 0 ,0));
            SelectObject(hdc, hPen);
            MoveToEx(hdc, uxView - userChildArea.right, uyView, NULL);
            
            uxView = LOWORD(lParam);
            uyView = HIWORD(lParam);
            LineTo(hdc, uxView - userChildArea.right, uyView);

    
            ReleaseDC(hWndPaintArea, hdc);
            return 0;

        case WM_LBUTTONDOWN:
            bClickedFlag = true;
            
            uxView = LOWORD(lParam);
            uyView = HIWORD(lParam);
            
            printf("uxVIEW --->%d\n", uxView);
            printf("uyVIEW --->%d\n", uyView);
            return 0;
        case WM_LBUTTONUP:

            bClickedFlag = false;
            return 0;
        
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDC_BUTTONPOINT:
                {
                    printf("toptotp\n");
                }
                break;
                case IDC_BUTTONCONNECT:
                {
                    printf("toptotp\n");
                }
                break;
                case IDC_BUTTONPIXEL:
                {
                    printf("toptotp\n");
                }
                break;
                case IDC_BUTTONSEGMENT:
                {
                    printf("toptotp\n");
                }
                break;
            }
            printf("HERE\n");
            return 0;

        case WM_DESTROY:
            if (hPen)
                DeleteObject(hPen);
            DeleteObject(hMenu);
            return 0;
    }

    return DefWindowProc(hWnd, iMsg, wParam, lParam);
}



int main(int argc, char **argv)
{
    HINSTANCE hInstance = GetModuleHandle(0);
    const char *szAppName = "Lab_01";
    HWND hWnd;
    MSG msg;
    WNDCLASSEX wndClass;

    memset(&wndClass, 0, sizeof(WNDCLASSEX));
    
    wndClass.cbSize = sizeof(wndClass);
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;

    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); // // LTGRAY_BRUSH
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = szAppName;
    wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    
    RegisterClassEx(&wndClass);

    hWnd = CreateWindowW(L"Lab_01", L"Lab_01", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
    CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    EnableTheming(true);
    ShowWindow(hWnd, SW_SHOWDEFAULT);
    UpdateWindow(hWnd);

    BOOL bRC;
    
    while ((bRC = GetMessage(&msg, NULL, 0, 0)))
    {
        if (bRC == -1) PostQuitMessage(0);
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}