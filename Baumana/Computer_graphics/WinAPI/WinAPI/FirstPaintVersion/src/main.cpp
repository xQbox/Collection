#include <iostream>
#include <Windows.h>

void MyMenu(HWND hwnd)
{
    HMENU  hMenu = CreateMenu();
    AppendMenu(hMenu, MF_POPUP, 2, "Close");

    SetMenu(hwnd, hMenu);
}

// user interactions
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    printf("iMessage: 0x%x, \nwParam: 0x%x, \nlParam: 0x%lx, \n", iMessage, wParam, lParam);
    
    static bool button_clicked_flag = 0;
    static int cur_x, cur_y;
    static HPEN hPen;

    if (iMessage == WM_CREATE)
    {
        MyMenu(hwnd);
        hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
        return 0;
    }
    
    if (iMessage == WM_DESTROY)  // 0x0002
    {
        DeleteObject(hPen);
        PostQuitMessage(0);   // added in message queue quitinfo 
        return 0;
    }

    if (iMessage == WM_KEYUP)
    {    
        static int colour;
        int key = wParam;
        if (key >= 'A' && key <= 'Z')
        {
            if (key == 'R') colour = RGB(0xff, 0, 0);
            if (key == 'G') colour = RGB(0, 0xff, 0);
            if (key == 'Y') colour = RGB(0xff, 0xff, 0);
            if (key == 'W') colour = RGB(0xff, 0xff, 0xff);
            if (key == 'B') colour = RGB(0, 0, 0xff);
            if (key == 'P') colour = RGB(0xff, 0, 0xff);
            if (key == 'T') colour = RGB(0, 0xff, 0xff);
        }
        static int width;
        if (key  >= '0' && key <= '9')
        {
            width = key - '0';
        }

        DeleteObject(hPen);
        hPen = CreatePen(PS_SOLID, width, colour);
        
        return 0;
    }

    if (iMessage == WM_LBUTTONDOWN)
    {
        button_clicked_flag = 1;
        
        cur_x = LOWORD(lParam);
        cur_y = HIWORD(lParam);

        return 0;
    }

    if (iMessage == WM_MOUSEMOVE)
    {
        if (!button_clicked_flag)
            return 0;

// device context descriptor
        HDC hdc = GetDC(hwnd);

// Style , width, colour
// Active Stylus
        SelectObject(hdc, hPen);

// Move stylus to last clicked button position
        MoveToEx(hdc, cur_x, cur_y, 0);

// Current Mouse position 
        cur_x = LOWORD(lParam);
        cur_y = HIWORD(lParam);

// SetPixel(hdc, cur_x, cur_y, RGB(0, 0, 0));
// Print line from last postion to new position
        LineTo(hdc, cur_x, cur_y);

// Output string (with x and y position on Window applicacion)
        char str[50];
        sprintf(str, "x = %-5d, y = %-5d", cur_x, cur_y);

// to print exactly sign of number use %-5d for minus and %+5d for plus
// Print info every hdc and about str
        TextOut(hdc, 0, 0, str, strlen(str));
        ReleaseDC(hwnd, hdc);
        return 0;
    }

    if (iMessage == WM_LBUTTONUP)
    {
        button_clicked_flag = 0;
        return 0;
    }
    return DefWindowProc(hwnd, iMessage, wParam, lParam);
}

// int  WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
int main(int argc, char **argv)
{
// При нуле возвращает дескриптор текущего приложения
// библиотеки , если она была загружена до этого 
// Получение дескриптора ранее загруженной библиотеки (имя дин. библиотеки в виде строки)
    HINSTANCE hInstance = GetModuleHandle(0); 
    WNDCLASSEX wnd_class;
    const char *wnd_class_name = "my window";

    memset(&wnd_class, 0, sizeof(wnd_class));
    
    wnd_class.cbSize = sizeof(wnd_class);
    wnd_class.hbrBackground = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
    wnd_class.lpfnWndProc = WndProc;
    // wnd_class.lpfnWndProc = DefWindowProc;
    wnd_class.hInstance = hInstance;
    wnd_class.lpszClassName = wnd_class_name;
    wnd_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    wnd_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wnd_class.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&wnd_class); // register class for application
    
    const char *title = "Paint"; 
// Window descriptor
// name, 0, 0, 
// X - long from left side of monitor to window, 
// Y - long from up side of monitor to window
// Size of window
    HWND hwnd = CreateWindow(wnd_class_name, title, WS_OVERLAPPEDWINDOW, 200, 100, 600, 400, 0, 0, hInstance, 0);

    ShowWindow(hwnd, SW_SHOWDEFAULT); // smtms iShow here 
   
   
    MSG msg;
    int status;
    // queue messages
    // main handle
    while (1)
    { 
        status = GetMessage(&msg, 0, 0, 0);          // all message for window applicacion 
        printf("Get message = 0x%x\n", msg.message);      
        printf("status -> 0x%d\n", status);
        if (msg.message == WM_QUIT) break;
        
        DispatchMessage(&msg); // or WndProc with args
    }
    
    printf("exit code : %d\n ", msg.wParam); // returning code in wParam
// In PostQuitMessage 
    return msg.wParam; 
}
 
