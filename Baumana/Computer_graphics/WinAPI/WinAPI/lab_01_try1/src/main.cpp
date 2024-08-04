#include <libmy.h>

#define ClientAreaDelimetr  5
#define MoveTo(hdc, x, y) MoveToEx(hdc, x, y, NULL)

HMENU MyMenu(HWND hWnd);
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildWndProc(HWND, UINT, WPARAM, LPARAM);

// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow)
int main(int argc, char **argv)
{
    HINSTANCE hInstance = GetModuleHandle(0); 
    const char *szAppName = "Checker3";
    HWND hwnd;
    MSG msg;
    WNDCLASSEX wndclass;
    
    
    wndclass.cbSize = sizeof(wndclass);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;

    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); // // LTGRAY_BRUSH
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    
    RegisterClassEx(&wndclass);
    

    const char *szChildClass = "EDIT MENU";
    wndclass.lpfnWndProc = ChildWndProc;
    wndclass.cbWndExtra = sizeof(WORD);
    wndclass.hIcon = NULL;
    wndclass.lpszClassName = szChildClass;
    wndclass.hIconSm = NULL;
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    
    RegisterClassEx(&wndclass);
    

    hwnd = CreateWindow(szAppName, "Checker3 Mouse Hit-Test Demo", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
    CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);
    
    while(GetMessage(&msg, NULL, 0, 0))
    {
        // printf("Get message = 0x%x\n", msg.message);      
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    
    static HMENU hMenu;

    static HWND hWndSeniorChild;
    static HWND hWndMiddleChild[3];
    static HWND hWndJuniorChild[20];
    
    static RECT userArea;
    static LPMINMAXINFO lpMMI; 

    static PAINTSTRUCT ps;
    static UINT32 uxView, uyView;
    static RECT rect;
    HPEN hPen = CreatePen(1, 1, RGB(107, 122, 131));

    if (iMsg == WM_CREATE)
    {
            hMenu = MyMenu(hWnd);


            GetClientRect(hWnd, &userArea);
            hWndSeniorChild = CreateWindowW(L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_GRAYFRAME, 0, -10, userArea.right, userArea.bottom / 4, hWnd, NULL, NULL, NULL);
            
            GetClientRect(hWndSeniorChild, &userArea);
            UINT16 u16Step = (userArea.right - userArea.left + ClientAreaDelimetr) / ClientAreaDelimetr, u16PosLeft = 0; // 5 - amount of window parts
            // // printf("USTEP %d\n", u16Step);
            // // printf("USERARE  RIGHT >> %d\n", userArea.right);
            // // printf("USERARE  BOTTOM >> %d\n", userArea.left);
            
            for (size_t i = 0; i < sizeof(hWndMiddleChild) / sizeof(hWndMiddleChild[0]); ++i)
            {
                hWndMiddleChild[i] = CreateWindow("STATIC", "", WS_CHILD | WS_VISIBLE | SS_BLACKRECT, u16PosLeft, 0,
                u16Step + i % 2 * u16Step * 2, userArea.bottom, hWndSeniorChild, NULL, NULL, NULL);
                u16PosLeft += u16Step + (i % 2 * u16Step * 2);
            }
            
            // // for (size i = 0; i < 3;)
            GetClientRect(hWndMiddleChild[0], &userArea);
            hWndJuniorChild[0] = CreateWindowW(L"BUTTON", L"Задать точку:", WS_CHILD | WS_VISIBLE, 20, 20, 120, 30, hWndMiddleChild[0], NULL, NULL, NULL);
            hWndJuniorChild[1] = CreateWindowW(L"BUTTON", L"Соединить точки", WS_CHILD | WS_VISIBLE, 20, 60, 140, 30, hWndMiddleChild[0], NULL, NULL, NULL);
            
            GetClientRect(hWndMiddleChild[1], &userArea);
            hWndJuniorChild[2] = CreateWindowW(L"BUTTON", L"Пиксель", WS_CHILD | WS_VISIBLE, 20, 20, 80, 30, hWndMiddleChild[1], NULL, NULL, NULL);
            hWndJuniorChild[3] = CreateWindowW(L"BUTTON", L"Отрезок", WS_CHILD | WS_VISIBLE, 100, 20, 80, 30, hWndMiddleChild[1], NULL, NULL, NULL);
            hWndJuniorChild[4] = CreateWindowW(L"BUTTON", L"Квадрат", WS_CHILD | WS_VISIBLE, 20, 60, 80, 30, hWndMiddleChild[1], NULL, NULL, NULL);
            hWndJuniorChild[4] = CreateWindowW(L"BUTTON", L"Квадрат", WS_CHILD | WS_VISIBLE, 100, 60, 80, 30, hWndMiddleChild[1], NULL, NULL, NULL);

            GetClientRect(hWndMiddleChild[2], &userArea);
            hWndJuniorChild[5] = CreateWindowW(L"BUTTON", L"Решить", WS_CHILD | WS_VISIBLE, 20, 20, 80, 30, hWndMiddleChild[2], NULL, NULL, NULL);
            hWndJuniorChild[6] = CreateWindowW(L"BUTTON", L"BUTTON Y", WS_CHILD | WS_VISIBLE, 20, 60, 80, 30, hWndMiddleChild[2], NULL, NULL, NULL);
            
            
            return 0; 
    }
    switch (iMsg)
    {
    
        //     // userArea.
                // hWndChild[i] = CreateWindow("button", "",
                //     WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
                //     0, 0, 200, 100,
                //     hWnd,(HMENU) 0, NULL, NULL); 

                // hWndChild[i] = CreateWindow("Button", szChildAreaName, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
                // 600, 200, 100, 30, hWnd, NULL, NULL, NULL);
                // CreateWindow("Button", szChildAreaName, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                // 200, 100, 100,  30, hWnd, NULL, NULL, NULL);
         
        case WM_PAINT:

            // GetClientRect(hWnd, &rect);
            // GetClientRect(hWndSeniorChild, &userArea);
            // static HDC hdc = BeginPaint(hWnd, &ps);  
            // static int y = userArea.bottom;
            // for (; y < rect.bottom; y += 100)
            // {
            //     MoveToEx(hdc, 0, y, NULL);
            //     LineTo (hdc, rect.right, y);
            // } 
            // for (int x = 0; x < rect.right; x += 100)
            // {
            //     MoveToEx(hdc, x, userArea.bottom, NULL);
            //     LineTo (hdc, x, y - 100);
            // }

/*MODULE : 
1) Set new start position to the middle of working area
2) Printing axis
3) 
*/
            HDC hdc;
            hdc = BeginPaint(hWnd, &ps);


// // // Определяем размеры клиентской области окна
            SetMapMode(hdc, MM_ISOTROPIC);
            SetWindowExtEx(hdc, 500, 500, NULL);
            GetClientRect(hWnd, &rect);
            GetClientRect(hWndSeniorChild, &userArea);
            SetViewportExtEx(hdc, uxView, -uyView, NULL);
            SetViewportOrgEx(hdc, rect.right / 2, rect.bottom / 2, NULL);

// Painting the step of splitting the axis
// X
            for (int i = 0; i < rect.right / 2 - 50; i += 50)
            {
                MoveToEx(hdc, i, (rect.bottom - userArea.bottom) / 2, NULL);
                LineTo(hdc, i, -(rect.bottom - userArea.bottom) / 2 );    
            }

            for (int i = 0; i > -rect.right / 2 + 50; i -= 50)
            {
                MoveToEx(hdc, i, (rect.bottom - userArea.bottom) / 2 , NULL);
                LineTo(hdc, i, -(rect.bottom - userArea.bottom) / 2 );
            }
// Y        
            for (int i = 0; i < (rect.bottom - userArea.bottom) / 2 - 50; i += 50)
            {
                MoveToEx(hdc, rect.right / 2, i, NULL);
                LineTo(hdc, -rect.right / 2, i);    
            }

            for (int i = 0; i > -rect.bottom / 2 + 50; i -= 50)
            {
                MoveToEx(hdc, rect.right / 2, i, NULL);
                LineTo(hdc, -rect.right / 2, i);  
            }


            hPen = CreatePen(1, 2, RGB(35, 40, 43));
            SelectObject(hdc, hPen);


// Painting X axis
            MoveToEx(hdc, 0, 0, NULL);
            LineTo(hdc, -rect.right / 2, 0);            
            MoveToEx(hdc, 0, 0, NULL);
            LineTo(hdc, rect.right / 2, 0);

            GetClientRect(hWndSeniorChild, &userArea);
            printf("%ld\n", userArea.bottom);
// Painting Y axis
            MoveToEx(hdc, 0, 0, NULL);
            LineTo(hdc, 0,  (rect.bottom - userArea.bottom)/ 2);
            MoveToEx(hdc, 0, 0, NULL);
            LineTo(hdc, 0, -rect.bottom / 2);




// In Windows coordinates  (left side of the window is (0, 0))       
// Painting X axis
//             MoveToEx(hdc, 0, (rect.bottom + userArea.bottom - 1) / 2, NULL);
//             LineTo(hdc, rect.right, (rect.bottom + userArea.bottom - 1) / 2);

// // Painting Y axis
//             MoveToEx(hdc, rect.right / 2, userArea.bottom, NULL);
//             LineTo(hdc, rect.right / 2, rect.bottom);


//             // Рисуем оси координат
//             MoveToEx(hdc, rect.left - 10, rect.bottom - 500, NULL); // Начало оси X
//             LineTo(hdc, rect.right - 10, rect.bottom - 500); // Ось X
//             MoveToEx(hdc, rect.left + 500, rect.bottom - 50, NULL); // Начало оси Y
//             LineTo(hdc, rect.left + 500, rect.top + 50); // Ось Y

//             // // Подписываем оси координат
//             TextOut(hdc, rect.right - 70, rect.bottom - 60, "X", 1);
//             TextOut(hdc, rect.left + 40, rect.top + 40, "Y", 1);

            EndPaint(hWnd, &ps);
            return 0;

        case WM_SIZE:
            uxView = LOWORD(lParam);
            uyView = HIWORD(lParam);
            printf("X >> %d , Y >> %d\n", uxView, uyView); 
            // // UpdateWindow(hWnd);
            // HBRUSH hBrush; 
            // hBrush =  CreateSolidBrush(RGB(0, 255, 0));
            // SetClassLongPtr(hWndSeniorChild, GCLP_HBRBACKGROUND, 0);
            // SetWindowPos(hWndSeniorChild, hWnd, 0, 0, uxView, uyView, SWP_SHOWWINDOW);
            // UpdateWindow(hWndSeniorChild);
            
            // SetWindowPos(hWndMiddleChild[0], hWndSeniorChild, 0, 0, uxView, uyView, SWP_SHOWWINDOW);
            // UpdateWindow(hWndMiddleChild[0]);
            // SetWindowPos(hWndMiddleChild[1], hWndSeniorChild, 0, 0, uxView, uyView, SWP_SHOWWINDOW);
            // UpdateWindow(hWndMiddleChild[1]);
            // SetWindowPos(hWndMiddleChild[2], hWndSeniorChild, 0, 0, uxView, uyView, SWP_SHOWWINDOW);
            // UpdateWindow(hWndMiddleChild[2]);
            

            // SetWindowPos(hWndJuniorChild[0], hWndMiddleChild[0], 0, 0, uxView, uyView, SWP_SHOWWINDOW);
            // UpdateWindow(hWndJuniorChild[0]);
            // SetWindowPos(hWndJuniorChild[1], hWndMiddleChild[0], 0, 0, uxView, uyView, SWP_SHOWWINDOW);
            // UpdateWindow(hWndJuniorChild[1]);
            // SetWindowPos(hWndJuniorChild[2], hWndMiddleChild[1], 0, 0, uxView, uyView, SWP_SHOWWINDOW);
            // UpdateWindow(hWndJuniorChild[2]);
            // SetWindowPos(hWndJuniorChild[3], hWndMiddleChild[1], 0, 0, uxView, uyView, SWP_SHOWWINDOW);
            // UpdateWindow(hWndJuniorChild[3]);
            // SetWindowPos(hWndJuniorChild[4], hWndMiddleChild[1], 0, 0, uxView, uyView, SWP_SHOWWINDOW);
            // UpdateWindow(hWndJuniorChild[4]);
            // SetWindowPos(hWndJuniorChild[5], hWndMiddleChild[2], 0, 0, uxView, uyView, SWP_SHOWWINDOW);
            // UpdateWindow(hWndJuniorChild[5]);
            // SetWindowPos(hWndJuniorChild[6], hWndMiddleChild[2], 0, 0, uxView, uyView, SWP_SHOWWINDOW);
            // UpdateWindow(hWndJuniorChild[6]);
            
            
            // MoveWindow(hWndSeniorChild, 0, 0, uxView, uyView, TRUE);
            // MoveWindow(hWndMiddleChild[0], 0, 0, uxView, uyView, TRUE);
            // MoveWindow(hWndMiddleChild[1], 0, 0, uxView, uyView, TRUE);
            // MoveWindow(hWndMiddleChild[2], 0, 0, uxView, uyView, TRUE);
            


            GetClientRect(hWnd, &userArea);
            
            printf("Width >> %ld , Height >> %ld\n", userArea.right, userArea.bottom); 
            MoveWindow(hWndSeniorChild, userArea.left, userArea.top - 10, userArea.right, userArea.bottom / 4, TRUE);
            
            // BeginPaint(hWndSeniorChild, &ps);
            // FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(COLOR_GRAYTEXT+13));
            
            
            // EndPaint(hWndSeniorChild, &ps);



  
            GetClientRect(hWndSeniorChild, &userArea);
            UINT16 u16Step, u16PosLeft;
            u16Step = (userArea.right - userArea.left + ClientAreaDelimetr) / ClientAreaDelimetr;
            u16PosLeft = 0; // 5 - amount of window parts
            // // printf("USTEP %d\n", u16Step);
            // // printf("USERARE  RIGHT >> %d\n", userArea.right);
            // // printf("USERARE  BOTTOM >> %d\n", userArea.left);



            for (size_t i = 0; i < sizeof(hWndMiddleChild) / sizeof(hWndMiddleChild[0]); ++i)
            {
                // printf("%ld\n", i);
                      
                MoveWindow(hWndMiddleChild[i], u16PosLeft, 0,
                u16Step + i % 2 * u16Step * 2, userArea.bottom - 30, TRUE);
                u16PosLeft += u16Step + (i % 2 * u16Step * 2);

                
                // BeginPaint(hWndMiddleChild[i], &ps);
                // FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(COLOR_GRAYTEXT + 13 + i));
                // EndPaint(hWndMiddleChild[i], &ps);
            }
            
            // UpdateWindow(hWndSeniorChild);
            
            
            // GetClientRect(hWndSeniorChild, &userArea);
            // UINT16 u16Step, u16PosLeft;
            // u16Step = (userArea.right - userArea.left + ClientAreaDelimetr) / ClientAreaDelimetr;
            // u16PosLeft = 0; // 5 - amount of window parts
            // printf("USTEP %d\n", u16Step);
            // printf("USERARE  RIGHT >> %d\n", userArea.right);
            // printf("USERARE  BOTTOM >> %d\n", userArea.left);
            
            // for (size_t i = 0; i < sizeof(hWndMiddleChild) / sizeof(hWndMiddleChild[0]); ++i)
            // {
            //     MoveWindow(hWndMiddleChild[i], u16PosLeft, 0,
            //     u16Step + i % 2 * u16Step * 2, userArea.bottom - 30, TRUE);
            //     u16PosLeft += u16Step + (i % 2 * u16Step * 2);
            // }
            

            // MoveWindow(hWndJuniorChild[0], 0, 0, uxView, uyView, TRUE);
        
            // MoveWindow(hWndJuniorChild[1], 0, 0, uxView, uyView, TRUE);
     
            // MoveWindow(hWndJuniorChild[2], 0, 0, uxView, uyView, TRUE);
           
            // MoveWindow(hWndJuniorChild[3], 0, 0, uxView, uyView, TRUE);
           
            // MoveWindow(hWndJuniorChild[4], 0, 0, uxView, uyView, TRUE);
           
            // MoveWindow(hWndJuniorChild[5], 0, 0, uxView, uyView, TRUE);
           
            // MoveWindow(hWndJuniorChild[6], 0, 0, uxView, uyView, TRUE);
                       
            return 0;
        case WM_GETMINMAXINFO:
            lpMMI = (LPMINMAXINFO) lParam;
            lpMMI->ptMinTrackSize.x = 1000;
            lpMMI->ptMinTrackSize.y = 500;
            return 0;

        case WM_DESTROY:
            DeleteObject(hPen);
            DestroyMenu(hMenu);
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hWnd, iMsg, wParam, lParam);
}


LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    switch (iMsg)
    {
        case WM_CREATE:
            
            return 0;
        
    }
    return DefWindowProc(hWnd, iMsg, wParam, lParam);
}



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
