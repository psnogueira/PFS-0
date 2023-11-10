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

	void LoadOpenGLFunction()
	{
		glCreateProgram = (PFNGLCREATEPROGRAMPROC)get_function_pointer("glCreateProgram");
		glDeleteProgram = (PFNGLDELETEPROGRAMPROC)get_function_pointer("glDeleteProgram");
		glCreateShader = (PFNGLCREATESHADERPROC)get_function_pointer("glCreateShader");
		glDeleteShader = (PFNGLDELETESHADERPROC)get_function_pointer("glDeleteShader");
		glShaderSource = (PFNGLSHADERSOURCEPROC)get_function_pointer("glShaderSource");
		glCompileShader = (PFNGLCOMPILESHADERPROC)get_function_pointer("glCompileShader");
		glGetShaderiv = (PFNGLGETSHADERIVPROC)get_function_pointer("glGetShaderiv");
		glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)get_function_pointer("glGetShaderInfoLog");
		glAttachShader = (PFNGLATTACHSHADERPROC)get_function_pointer("glAttachShader");
		glLinkProgram = (PFNGLLINKPROGRAMPROC)get_function_pointer("glLinkProgram");
		glGetProgramiv = (PFNGLGETPROGRAMIVPROC)get_function_pointer("glGetProgramiv");
		glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)get_function_pointer("glGetProgramInfoLog");
		glUseProgram = (PFNGLUSEPROGRAMPROC)get_function_pointer("glUseProgram");
		glGenBuffers = (PFNGLGENBUFFERSPROC)get_function_pointer("glGenBuffers");
		glBindBuffer = (PFNGLBINDBUFFERPROC)get_function_pointer("glBindBuffer");
		glBufferData = (PFNGLBUFFERDATAPROC)get_function_pointer("glBufferData");
		glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)GL::get_function_pointer("glGetAttribLocation");
		glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)get_function_pointer("glEnableVertexAttribArray");
		glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)get_function_pointer("glVertexAttribPointer");
	}

	void SwapBuffers(platform_window_t* window)
	{
		SwapBuffers(window->dc);
	}

	///
	/// OpenGL function definitions
	/// 

	/**/
	GLuint CreateProgram() noexcept
	{
		return glCreateProgram();
	}

	void DeleteProgram(GLuint program) noexcept
	{
		glDeleteProgram(program);
	}

	const GLubyte* GetString(GLenum name) noexcept
	{
		return glGetString(name);
	}

	GLuint CreateShader(GLenum shaderType) noexcept
	{
		return glCreateShader(shaderType);
	}

	void DeleteShader(GLuint shader) noexcept
	{
		glDeleteShader(shader);
	}

	void ShaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length) noexcept
	{
		glShaderSource(shader, count, string, length);
	}

	void CompileShader(GLuint shader) noexcept
	{
		glCompileShader(shader);
	}

	void GetShaderiv(GLuint shader, GLenum pname, GLint* params) noexcept
	{
		glGetShaderiv(shader, pname, params);
	}

	void GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) noexcept
	{
		glGetShaderInfoLog(shader, maxLength, length, infoLog);
	}

	void AttachShader(GLuint program, GLuint shader) noexcept
	{
		glAttachShader(program, shader);
	}

	void LinkProgram(GLuint program) noexcept
	{
		glLinkProgram(program);
	}

	void GetProgramiv(GLuint program, GLenum pname, GLint* params) noexcept
	{
		glGetProgramiv(program, pname, params);
	}

	void GetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog) noexcept
	{
		glGetProgramInfoLog(program, maxLength, length, infoLog);
	}

	void UseProgram(GLuint program) noexcept
	{
		glUseProgram(program);
	}

	void GenBuffers(GLsizei n, GLuint* buffers) noexcept
	{
		glGenBuffers(n, buffers);
	}

	void BindBuffer(GLenum target, GLuint buffer) noexcept
	{
		glBindBuffer(target, buffer);
	}

	void BufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) noexcept
	{
		glBufferData(target, size, data, usage);
	}

	GLint GetAttribLocation(GLuint program, const GLchar* name) noexcept
	{
		return glGetAttribLocation(program, name);
	}

	void EnableVertexAttribArray(GLuint index) noexcept
	{
		glEnableVertexAttribArray(index);
	}

	void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) noexcept
	{
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	}

	void Clear(GLbitfield mask) noexcept
	{
		glClear(mask);
	}

	void DrawArrays(GLenum mode, GLint first, GLsizei count) noexcept
	{
		glDrawArrays(mode, first, count);
	}

	/**/
}