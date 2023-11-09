#include "Window.hpp"
#include "Log.hpp"

static bool isInitilized = false;

platform_window_t* Window::create_window(const std::string& title, unsigned int width, unsigned int height)
{
    WNDPROC window_proc = [](HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) -> LRESULT {
        if (message == WM_CLOSE || (message == WM_KEYDOWN && wparam == VK_ESCAPE)) {
            PostQuitMessage(0);
            return 0;
        }

        // Allows clicking anywhere in the window to drag it around
        if (message == WM_NCHITTEST) {
            return HTCAPTION;
        }

        return DefWindowProc(hwnd, message, wparam, lparam);
    };

    std::string window_class = title + " class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = window_proc;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = window_class.c_str();
    RegisterClass(&wc);

    DWORD dwStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

    RECT wr = { 0, 0, (LONG)width, (LONG)height };
    AdjustWindowRect(&wr, dwStyle, FALSE);

    HWND hwnd = CreateWindow(window_class.c_str(), title.c_str(), dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top, NULL, NULL, NULL, NULL);
    if (!hwnd) {
        UnregisterClass(window_class.c_str(), NULL);
        return nullptr;
    }

    HDC dc = GetDC(hwnd);

    // OpenGL context


    /// 
    /// Pixel Format
    /// 
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

    /*

    PIXELFORMATDESCRIPTOR pfd2 = {};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_GENERIC_ACCELERATED | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;

    */

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

    platform_window_t* window = new platform_window_t;
    window->handle = hwnd;
    window->cls = window_class;
    window->dc = dc;
    window->rc = rc;

    return window;
}

void Window::destroy_window(platform_window_t* window)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(window->rc);

    ReleaseDC(window->handle, window->dc);
    DestroyWindow(window->handle);
    UnregisterClass(window->cls.c_str(), NULL);

    delete window;
}

bool Window::handle_events(platform_window_t*)
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

void* Window::get_gl_function_pointer(const std::string& name)
{
    return wglGetProcAddress(name.c_str());
}

void Window::swap(platform_window_t* window)
{
    SwapBuffers(window->dc);
}

///
/// 
/// Important Window Functions
/// 
/// 

static bool RegisterWindowClass() noexcept;

bool Window::Init() noexcept
{
    SM_ERROR("Init comecou");

    if (isInitilized)
        return false;

    isInitilized = RegisterWindowClass();
    SM_ASSERT(isInitilized, "Failed to register window class");

    return isInitilized;
}

void Window::Cleanup() noexcept
{
    return;
}

static bool RegisterWindowClass() noexcept
{

    return true;
}