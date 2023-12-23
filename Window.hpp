#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <string>

struct platform_window_t
{
    HWND handle;
    std::string cls;
    HDC dc;
    HGLRC rc;
};

namespace Window
{
    bool Init() noexcept;

    void Cleanup() noexcept;

    platform_window_t* createWindow(unsigned int width, unsigned int height);
    
    void DestroyWindow(platform_window_t* window) noexcept;
    
    bool ShowWindow(platform_window_t* window) noexcept;
    
    void SetWindowResizable(platform_window_t* window, bool resizable) noexcept;

    bool HandleEvents(platform_window_t*);
    
    void* get_gl_function_pointer(const std::string& name);
    
    //
    void Swap(platform_window_t* window);
    
}

#endif