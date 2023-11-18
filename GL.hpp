#pragma once

#if defined(_WIN32)
#include "Window.hpp"
#else
#error Unsupported platform
#endif

#include <Windows.h>
#include "Log.hpp"
#include <string>
#include <vector>

namespace GL
{
	bool Init() noexcept;

	void Cleanup() noexcept;

	void* get_function_pointer(const std::string& name);

	bool LoadOpenGLFunction();

	bool InitializeShaders();

	void SwapBuffers(platform_window_t* window);

	///
	/// OpengGL functions
	///

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
	
}