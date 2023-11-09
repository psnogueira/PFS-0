#include "GL.hpp"

namespace GL
{
	bool Init() noexcept
	{
		return true;
	}

	void Cleanup() noexcept
	{

	}

	void* get_function_pointer(const std::string& name)
	{
		return wglGetProcAddress(name.c_str());
	}

	void SwapBuffers(platform_window_t* window)
	{
		SwapBuffers(window->dc);
	}

}