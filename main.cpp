#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h> /* <tchar.h> defines the TCHAR macro, which resolves ultimately to wchar_t if the UNICODE symbol is defined in your project,
otherwise it resolves to char. If you always build with UNICODE enabled, you don't need TCHAR and can just use wchar_t directly. */
#include <windows.h> /* Windows desktop programs require <windows.h> */

/*  Declare Windows procedure  */
/* In addition to the WinMain function, every Windows desktop application must also have a window-procedure function.
This function is typically named WndProc but you can name it whatever you like. WndProc has the following syntax.
-----------------------------------------------------------------------------------------------------------------
In this function, you write code to handle messages that the application receives from Windows when events occur.
For example, if a user chooses an OK button in your application, Windows will send a message to you and you can
write code inside your WndProc function that does whatever work is appropriate. It's called handling an event.
You only handle the events that are relevant for your application. */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
/*  the name of the application  */
TCHAR szClassName[ ] = _T("ReznorWindowClass");

/* Just as every C application and C++ application must have a main function as its starting point,
every Windows desktop application must have a WinMain function. */
int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

/* In the WinMain function, you populate a structure of type WNDCLASSEX.
The structure contains information about the window, for example,
the application icon, the background color of the window, the name to display in the title bar,
and importantly, a function pointer to your window procedure.
The following example shows a typical WNDCLASSEX structure. */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_WINDOW;

    /* Register the window class, and if it fails quit the program */
/* Register the WNDCLASSEX with Windows so that it knows about your window and how to send messages to it.
Use the RegisterClassEx function and pass the window class structure as an argument.
The _T macro is used because we use the TCHAR type. */
    if (!RegisterClassEx (&wincl))
    {
        MessageBox(NULL,
        _T("Call to RegisterClassEx failed!"),
        _T("Windows Desktop Guided Tour"),
        MB_ICONINFORMATION | MB_OK);

        return 1;
    }

    /* The class is registered, let's create the program*/
/* This function returns an HWND, which is a handle to a window.
A handle is somewhat like a pointer that Windows uses to keep track of open windows.
For more information, see Windows Data Types. */
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname = the name of the application */
           _T("rezno[R]'s first C++ Win32 program"),       /* Title Text = the text that appears in the title bar */
           WS_OVERLAPPEDWINDOW, /* default window = the type of window to create */
           CW_USEDEFAULT,       /* Windows decides the position = initial position (x) */
           CW_USEDEFAULT,       /* where the window ends up on the screen = initial position (y) */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop = the parent of this window */
           NULL,                /* No menu = this application does not have a menu bar */
           hThisInstance,       /* Program Instance handler = the first parameter from WinMain */
           NULL                 /* No Window Creation data */
           );

    if (!hwnd)
    {
        MessageBox(NULL,
        _T("Call to CreateWindowEx failed!"),
        _T("Windows Desktop Guided Tour"),
        MB_ICONINFORMATION | MB_OK);

        return 1;
    }

    /* Make the window visible on the screen */
/* At this point, the window has been created, but we still need to tell Windows to make it visible. That's what this code does: */
    ShowWindow (hwnd, nCmdShow);
    UpdateWindow(hwnd);
    // hwnd: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain

/* The displayed window doesn't have much content because you haven't yet implemented the WndProc function.
In other words, the application isn't yet handling the messages that Windows is now sending to it.
To handle the messages, we first add a message loop to listen for the messages that Windows sends.
When the application receives a message, this loop dispatches it to your WndProc function to be handled.
The message loop resembles the following code. */
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */
/* To enable the WndProc function to handle the messages that the application receives, implement a switch statement.
One important message to handle is the WM_PAINT message. The application receives the WM_PAINT message when part of its displayed window must be updated.
The event can occur when a user moves a window in front of your window, then moves it away again, and your application doesn't know when these events occur.
Only Windows knows, so it notifies you with WM_PAINT. When the window is first displayed, all of it must be updated.
To handle a WM_PAINT message, first call BeginPaint, then handle all the logic to lay out the text, buttons, and other controls in the window, and then call EndPaint.
For the application, the logic between the beginning call and the ending call is to display the string "Hello, Windows desktop!" in the window.
In the following code, notice that the TextOut function is used to display the string.

An application typically handles many other messages, for example, WM_CREATE when a window is first created, and WM_DESTROY when the window is closed.

LRESULT is an integer value that your program returns to Windows. It contains your program's response to a particular message.
The meaning of this value depends on the message code. CALLBACK is the calling convention for the function.
hwnd is a handle to the window.
message is the message code; for example, the WM_SIZE message indicates the window was resized.
wParam and lParam contain additional data that pertains to the message. The exact meaning depends on the message code. */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("This is rezno[R]'s first Win32 application.");

    switch (message)                  /* switch to handle the messages */
    {
/* The WM_NCCREATE and WM_CREATE message are sent before the window becomes visible.
That makes them a good place to initialize your UI—for example, to determine the initial layout of the window. */
        case WM_NCCREATE:
            return DefWindowProc (hwnd, message, wParam, lParam);
        case WM_CREATE:
            return DefWindowProc (hwnd, message, wParam, lParam);

        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);

            // Here your application is laid out.
            // For this introduction, we just print out "Hello, Windows desktop!"
            // in the top left corner.
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW)); // FillRect = old GDI [not Direct2D]
            TextOut(hdc, 5, 5, greeting, _tcslen(greeting));
            // End application-specific layout section.

            EndPaint(hwnd, &ps);
            break;

        case WM_CLOSE:
            if (MessageBox(hwnd, "Really quit rezno[R]'s first Win32 program?", "rezno[R]'s first Win32 message box", MB_ICONINFORMATION | MB_OKCANCEL) == IDOK)
            {
                DestroyWindow(hwnd);
            }
            // Else: User canceled. Do nothing.
            return 0;

        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            return 0;
            break;
/* for messages that we don't deal with */
/* If you don't handle a particular message in your window procedure, pass the message parameters directly to the DefWindowProc function.
This function performs the default action for the message, which varies by message type. */
        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
/* Avoiding Bottlenecks in Your Window Procedure
While your window procedure executes, it blocks any other messages for windows created on the same thread.
Therefore, avoid lengthy processing inside your window procedure. For example, suppose your program opens a TCP connection
and waits indefinitely for the server to respond. If you do that inside the window procedure, your UI will not respond until the request completes.
During that time, the window cannot process mouse or keyboard input, repaint itself, or even close.

Instead, you should move the work to another thread, using one of the multitasking facilities that are built into Windows:
- Create a new thread.
- Use a thread pool.
- Use asynchronous I/O calls.
- Use asynchronous procedure calls. */

    return 0;
}
