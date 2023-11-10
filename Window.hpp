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

    platform_window_t* create_window(const std::string& title, unsigned int width, unsigned int height);
    

    void destroy_window(platform_window_t* window);
    

    bool handle_events(platform_window_t*);
    

    void* get_gl_function_pointer(const std::string& name);
    
    //
    void swap(platform_window_t* window);
    
}

#endif