#pragma once

#if defined(_WIN32)
#include "Window.hpp"
#else
#error Unsupported platform
#endif

#include <Windows.h>
#include "Log.hpp"

namespace GL
{
	//aaaa
	bool Init() noexcept;

	void Cleanup() noexcept;

	void* get_function_pointer(const std::string& name);

	void SwapBuffers(platform_window_t* window);

	
}