#include "Window.hpp"
#include "Log.hpp"

namespace Window
{

///
/// Important variables.
///

static bool isInitilized = false;
static const std::string& sTitle = "Pong";
static const std::string& sWindowClassName = "Pong class";

static bool RegisterWindowClass()
{
    ///
    /// Procedure called to every message sent to the window.
    /// 
    WNDPROC window_proc = [](HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) -> LRESULT {
        if (message == WM_CLOSE || (message == WM_KEYDOWN && wparam == VK_ESCAPE)) {
            PostQuitMessage(0);
            return 0;
        }

        // Allows clicking anywhere in the window to drag it around.
        if (message == WM_NCHITTEST) {
            return HTCAPTION;
        }

        return DefWindowProc(hwnd, message, wparam, lparam);
    };

    ///
    /// Register the Window Class.
    /// 
    
    WNDCLASS wc = {};
    wc.lpfnWndProc = window_proc;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = sWindowClassName.c_str();
    return RegisterClass(&wc);
}

platform_window_t* createWindow(unsigned int width, unsigned int height)
{
    // Window need to be registered before being created.
    RegisterWindowClass();

    DWORD dwStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

    RECT wr = { 0, 0, (LONG)width, (LONG)height };
    AdjustWindowRect(&wr, dwStyle, FALSE);

    HWND hwnd = CreateWindow(
        sWindowClassName.c_str(), 
        sTitle.c_str(), 
        dwStyle, 
        CW_USEDEFAULT, CW_USEDEFAULT, 
        wr.right - wr.left, 
        wr.bottom - wr.top, 
        NULL, NULL, NULL, 
        NULL);
    
    if (!hwnd) {
        UnregisterClass(sWindowClassName.c_str(), NULL);
        return nullptr;
    }

    HDC dc = GetDC(hwnd);

    // Pixel Format.
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_SUPPORT_OPENGL | PFD_GENERIC_ACCELERATED | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER,    // Flags
            PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
            32,                   // Colordepth of the framebuffer.
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            24,                   // Number of bits for the depthbuffer
            8,                    // Number of bits for the stencilbuffer
            0,                    // Number of Aux buffers in the framebuffer.
            PFD_MAIN_PLANE,
            0,
            0, 0, 0
    };

    int pixelFormat = ChoosePixelFormat(dc, &pfd);
    if (pixelFormat == 0) {
        return nullptr;
    }

    if (SetPixelFormat(dc, pixelFormat, &pfd) == FALSE) {
        return nullptr;
    }

    HGLRC rc = wglCreateContext(dc);
    if (!rc) {
        return nullptr;
    }

    if (wglMakeCurrent(dc, rc) == FALSE) {
        return nullptr;
    }
    
    // Assigning the window's properties.
    platform_window_t* window = new platform_window_t;
    window->handle = hwnd;
    window->cls = sWindowClassName;
    window->dc = dc;
    window->rc = rc;

    return window;
}

void DestroyWindow(platform_window_t* window)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(window->rc);

    ReleaseDC(window->handle, window->dc);
    DestroyWindow(window->handle);
    UnregisterClass(window->cls.c_str(), NULL);

    delete window;
}

bool HandleEvents(platform_window_t*)
{
    MSG msg = {};
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (msg.message == WM_QUIT) {
        return true;
    }

    return false;
}

void* get_gl_function_pointer(const std::string& name)
{
    return wglGetProcAddress(name.c_str());
}

void Swap(platform_window_t* window)
{
    SwapBuffers(window->dc);
}

bool Init() noexcept
{
    if (isInitilized)
        return false;

    isInitilized = RegisterWindowClass();
    SM_ASSERT(isInitilized, "Failed to register window class");

    return isInitilized;
}

void Cleanup() noexcept
{
    if (isInitilized)
        return;

    //UnregisterClassW();
    isInitilized = false;
}

}

