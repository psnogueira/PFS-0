#pragma once

#if defined(_WIN32)
#include "Window.hpp"
#else
#error Unsupported platform
#endif

#include <Windows.h>
#include "Log.hpp"

static PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
static PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr; //
//static PFNGLDRAWARRAYSEXTPROC glDrawArrays = nullptr; // já tem
static PFNGLCREATESHADERPROC glCreateShader = nullptr;
static PFNGLDELETESHADERPROC glDeleteShader = nullptr; //
static PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
static PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
static PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
static PFNGLATTACHSHADERPROC glAttachShader = nullptr;
static PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
static PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
static PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
static PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
static PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
static PFNGLBUFFERDATAPROC glBufferData = nullptr;
static PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = nullptr;
static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;

namespace GL
{
	//aaaa
	bool Init() noexcept;

	void Cleanup() noexcept;

	void* get_function_pointer(const std::string& name);

	void LoadOpenGLFunction();

	void SwapBuffers(platform_window_t* window);

	//glCreateProgram //
	//glDeleteProgram //
	//  
	//glCreateShader //
	//glDeleteShader //
	//glShaderSource //
	//glCompileShader //
	//glGetShaderiv //
	//glGetShaderInfoLog //
	//glAttachShader //
	// 
	//glLinkProgram //
	//glGetProgramiv //
	//glGetProgramInfoLog //
	//glUseProgram //
	// 
	//glGenBuffers //
	//glBindBuffer //
	//glBufferData //
	// 
	//glGetAttribLocation //
	// 
	//glEnableVertexAttribArray //
	//glVertexAttribPointer //
	//
	//glClear ? já tem, mas vou colocar mesmo assim (:
	//glDrawArrays ? já tem


	//
	// OpengGL functions
	//

	/**/
	GLuint CreateProgram() noexcept;
	void DeleteProgram(GLuint program) noexcept;

	const GLubyte* GetString(GLenum name) noexcept;

	GLuint CreateShader(GLenum shaderType) noexcept;
	void DeleteShader(GLuint shader) noexcept;
	void ShaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length) noexcept;
	void CompileShader(GLuint shader) noexcept;
	void GetShaderiv(GLuint shader, GLenum pname, GLint* params) noexcept;
	void GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) noexcept;
	void AttachShader(GLuint program, GLuint shader) noexcept;

	void LinkProgram(GLuint program) noexcept;
	void GetProgramiv(GLuint program, GLenum pname, GLint* params) noexcept;
	void GetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog) noexcept;
	void UseProgram(GLuint program) noexcept;

	void GenBuffers(GLsizei n, GLuint* buffers) noexcept;
	void BindBuffer(GLenum target, GLuint buffer) noexcept;
	void BufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) noexcept;
	
	GLint GetAttribLocation(GLuint program, const GLchar* name) noexcept;

	void EnableVertexAttribArray(GLuint index) noexcept;
	void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) noexcept;

	void Clear(GLbitfield mask) noexcept;

	void DrawArrays(GLenum mode, GLint first, GLsizei count) noexcept;

	/**/
	
}