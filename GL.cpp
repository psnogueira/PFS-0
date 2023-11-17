#include "GL.hpp"

///
/// OpenGL functions declarations
///

static PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
static PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr; //
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

namespace GL
{
	static bool isInitialized = false;

	bool Init() noexcept
	{
		if (isInitialized)
			return false;
		
		//isInitialized = LoadOpenGLFunction();

		return true;
	}

	void Cleanup() noexcept
	{

	}

	void* get_function_pointer(const std::string& name)
	{
		return wglGetProcAddress(name.c_str());
	}

	bool LoadOpenGLFunction()
	{
		return 
			(glCreateProgram = (PFNGLCREATEPROGRAMPROC)get_function_pointer("glCreateProgram")) &&
			(glDeleteProgram = (PFNGLDELETEPROGRAMPROC)get_function_pointer("glDeleteProgram")) &&
			(glCreateShader = (PFNGLCREATESHADERPROC)get_function_pointer("glCreateShader")) &&
			(glDeleteShader = (PFNGLDELETESHADERPROC)get_function_pointer("glDeleteShader")) &&
			(glShaderSource = (PFNGLSHADERSOURCEPROC)get_function_pointer("glShaderSource")) &&
			(glCompileShader = (PFNGLCOMPILESHADERPROC)get_function_pointer("glCompileShader")) &&
			(glGetShaderiv = (PFNGLGETSHADERIVPROC)get_function_pointer("glGetShaderiv")) &&
			(glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)get_function_pointer("glGetShaderInfoLog")) &&
			(glAttachShader = (PFNGLATTACHSHADERPROC)get_function_pointer("glAttachShader")) &&
			(glLinkProgram = (PFNGLLINKPROGRAMPROC)get_function_pointer("glLinkProgram")) &&
			(glGetProgramiv = (PFNGLGETPROGRAMIVPROC)get_function_pointer("glGetProgramiv")) &&
			(glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)get_function_pointer("glGetProgramInfoLog")) &&
			(glUseProgram = (PFNGLUSEPROGRAMPROC)get_function_pointer("glUseProgram")) &&
			(glGenBuffers = (PFNGLGENBUFFERSPROC)get_function_pointer("glGenBuffers")) &&
			(glBindBuffer = (PFNGLBINDBUFFERPROC)get_function_pointer("glBindBuffer")) &&
			(glBufferData = (PFNGLBUFFERDATAPROC)get_function_pointer("glBufferData")) &&
			(glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)GL::get_function_pointer("glGetAttribLocation")) &&
			(glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)get_function_pointer("glEnableVertexAttribArray")) &&
			(glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)get_function_pointer("glVertexAttribPointer"));
	}

	bool InitializeShaders()
	{
		// shaders

		std::vector<std::pair<GLenum, std::string>> shaders = {
			{
				GL_VERTEX_SHADER,
				"#version 130\n"
				"in vec4 position;\n"
				"out vec2 uv;\n"
				"\n"
				"void main() {\n"
				"  gl_Position = position;\n"
				"  uv = (position.xy + 1.0) / 2.0;\n"
				"}\n"
			},
			{
				GL_FRAGMENT_SHADER,
				"#version 130\n"
				"in vec2 uv;\n"
				"out vec4 color;\n"
				"\n"
				"void main() {\n"
				"  color = vec4(uv, 0.0, 1.0);\n"
				"}\n"
			},
		};

		GLuint program = GL::CreateProgram();

		for (const auto& s : shaders) {
			GLenum type = s.first;
			const std::string& source = s.second;

			const GLchar* src = source.c_str();

			GLuint shader = GL::CreateShader(type);
			GL::ShaderSource(shader, 1, &src, nullptr);

			GL::CompileShader(shader);

			GLint compiled = 0;
			GL::GetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
			if (!compiled) {
				GLint length = 0;
				GL::GetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

				if (length > 1) {
					std::string log(length, '\0');
					GL::GetShaderInfoLog(shader, length, &length, &log[0]);
					printf("Shader compile failed:\n%s\n", log.c_str());
				}
				else {
					printf("Shader compile failed.\n");
				}

				return false;
			}

			GL::AttachShader(program, shader);
		}

		GL::LinkProgram(program);

		GLint linked = 0;
		GL::GetProgramiv(program, GL_LINK_STATUS, &linked);

		if (!linked) {
			GLint length = 0;
			GL::GetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

			if (length > 1) {
				std::string log(length, '\0');
				GL::GetProgramInfoLog(program, length, &length, &log[0]);
				printf("Program link failed:\n%s", log.c_str());
			}
			else {
				printf("Program link failed.\n");
			}

			return false;
		}

		// vertex buffer

		float vertices[] = {
			-1.0f, 1.0f,
			-1.0f, -1.0f,
			1.0f, -1.0f
		};

		GLuint vb;
		GL::GenBuffers(1, &vb);
		GL::BindBuffer(GL_ARRAY_BUFFER, vb);
		GL::BufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// initial state
		GL::UseProgram(program);

		GLint position = GL::GetAttribLocation(program, "position");
		GL::EnableVertexAttribArray(position);

		GL::BindBuffer(GL_ARRAY_BUFFER, vb);
		GL::VertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, 0, 0);


		//Arrumar
		return true;
	}

	void SwapBuffers(platform_window_t* window)
	{
		SwapBuffers(window->dc);
	}

	///
	/// OpenGL function definitions
	/// 

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

}