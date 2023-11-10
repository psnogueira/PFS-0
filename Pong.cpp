/***************************************
 * Pong game
 * Made with OpenGL
 *--------------------------------------
 * Created by psnogueira on 17/10/2023
 ***************************************/

#if defined(_WIN32)
#include "Window.hpp"
#else
#error Unsupported platform
#endif

#include <set>
#include <utility>
#include <string>
#include <vector>
#include <Windows.h>
#include <iostream>
#include "Pong.hpp"
#include "Log.hpp"

#include <GL/gl.h>
#include <GL/glext.h>

#include "GL.hpp"

 ///
 /// OpenGL functions declarations
 ///




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

	return true;
}

/// 
/// Render
///

void Render()
{
	GL::Clear(GL_COLOR_BUFFER_BIT);
	GL::DrawArrays(GL_TRIANGLES, 0, 3);
}

#define LOG_GL_STRING(name, stringName) \
    SM_CUSTOM(TEXT_COLOR_BRIGHT_GREEN, name, reinterpret_cast<const char*>(GL::GetString(stringName)))

bool pong::PlayGame()
{
	const unsigned int client_width = 512;
	const unsigned int client_height = 512;

	Window::Init();

	platform_window_t* window = Window::create_window("Ola, Mundo!", client_width, client_height);
	
	if (!window) {
		printf("Failed to create window.\n");
		return false;
	}
	/*
	* Init() and Cleanup() of Graphics.cpp
	static HMODULE isOpenGLLibary = nullptr;

	isOpenGLLibary = LoadLibraryA("OpenGL32.dll");
	SM_ASSERT(isOpenGLLibary,"Failed to load OpenGL");

	FreeLibrary(isOpenGLLibary);
	isOpenGLLibary = nullptr;
	*/

	//auto versao = reinterpret_cast<const char*>(glGetString(GL_VENDOR));

	//SM_CUSTOM(TEXT_COLOR_BRIGHT_GREEN, "GL_VENDOR: ", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
	LOG_GL_STRING("GL_VENDOR: ", GL_VENDOR);
	LOG_GL_STRING("GL_VERSION: ", GL_VERSION);
	LOG_GL_STRING("GL_RENDERER: ", GL_RENDERER);

	//printf("GL_VENDOR: %s\n", glGetString(GL_VENDOR));
	//printf("GL_VERSION: %s\n", glGetString(GL_VERSION));
	//printf("GL_RENDERER: %s\n", glGetString(GL_RENDERER));

	// initialize OpenGL function pointers
	GL::LoadOpenGLFunction();

	

	if (!InitializeShaders()) {
		printf("Scene initialization failed.\n");
		return false;
	}
	SM_TRACE("Inicializacao deu certo!");

	while (true) {
		bool quit = Window::handle_events(window);
		if (quit) {
			break;
		}

		Render();

		//Window::swap(window);
		GL::SwapBuffers(window);
	}

	Window::destroy_window(window);
	
	return true;
}

 // Important variables
static bool isInitialized = false;
static bool isRunning = false;

/// ! @brief A Class with the Init() and Cleanup() functions of any item.
///
class Lifetime
{
public:

	///! @brief Generic initialization function that returns false on failure.
	///
	/// @return Whether the Initialization was successful.
	using PFNInit = bool (*)();

	///! @brief Generic cleanup function.
	///
	using PFNCleanup = void (*)();

private:

	PFNInit mInit;
	PFNCleanup mCleanup;

public:

	/// <summary> Lifetime constructor.
	/// Both Init() and Cleanup() functions are necessary.
	/// </summary>
	/// <param name="initFunction"></param>
	/// <param name="cleanupFunction"></param>
	constexpr Lifetime(PFNInit init, PFNCleanup cleanup) noexcept
		: mInit(init), mCleanup(cleanup)
	{

	}

public:

	///! @brief Lifetime item's initialization function that returns false on failure.
	///
	/// @return Whether the Initialization was successful.
	constexpr bool Init() const noexcept
	{
		return mInit();
	}

	///! @brief Lifetime item's cleanup function.
	///
	constexpr void Cleanup() const noexcept
	{
		mCleanup();
	}

};

///
/// Initialize the game's systems.
/// 
static bool InitGameSystems() noexcept;

///
/// Cleans up the game's systems.
/// 
static void CleanupGameSystems() noexcept;

///
/// Initialize the game's state and resources.
/// 
static bool InitState() noexcept;

///
/// Cleans up the game's state and resources.
/// 
static void CleanupState() noexcept;


///
/// All the game Lifetimes.
/// 
/// It is an array containing instances of the class Lifetime.
/// Every instance is generated by giving an Init and Cleanup function.
/// 
static constexpr Lifetime kGameLifetimes[] =
{
	{InitGameSystems, CleanupGameSystems},
	{InitState, CleanupState}
};

/// 
/// Simple wrapper for the array reference syntax.
/// 
template<typename T, std::size_t Size>
using ConstArrayReference = const T(&)[Size];

template<std::size_t NumItems>
bool TryInitItems(ConstArrayReference<Lifetime, NumItems> lifetimes) noexcept;

/// 
/// Initialization function
/// 
bool pong::Init() noexcept
{
	SM_TRACE("Init()");

	// If the game is already initialized, this function returns false.
	if (isInitialized)
	{
		SM_WARN("Game has already initilized!");
		return false;
	}
		
	isInitialized = TryInitItems(kGameLifetimes);
	//Window::Init();
	return isInitialized;
}

template<std::size_t NumItems>
static void CleanupItemsStartingAt(ConstArrayReference<Lifetime, NumItems> lifetimes, unsigned index) noexcept;

///
/// Trys to initialize all given items
/// 
template<std::size_t NumItems> 
bool TryInitItems(ConstArrayReference<Lifetime, NumItems> lifetimes) noexcept
{
	bool succeded = true;

	for (unsigned i = 0; succeded && i < NumItems; i++)
	{
		succeded = lifetimes[i].Init();

		if (!succeded)
		{
			CleanupItemsStartingAt(lifetimes, i);
		}
	}

	return succeded;
}

template<std::size_t NumItems>
void CleanupItemsStartingAt(ConstArrayReference<Lifetime, NumItems> lifetimes, unsigned index) noexcept
{
	for (int i = static_cast<int>(index) - 1; i >= 0; i--)
	{
		lifetimes[i].Cleanup();
	}
}

//
static bool WindowInit() noexcept;

//
static void WindowCleanup() noexcept;

//
static bool GraphicsInit() noexcept;

//
static void GraphicsCleanup() noexcept;

//
static bool glInit() noexcept;

//
static void glCleanup() noexcept;

//
static bool TimeInit() noexcept;

//
static void TimeCleanup() noexcept;

///
/// All the system Lifetimes.
/// 
/// It is an array containing instances of the class Lifetime.
/// Every instance is generated by giving an Init and Cleanup function.
/// 
static constexpr Lifetime kSystemLifetimes[] =
{
	{WindowInit, WindowCleanup},
	{GraphicsInit, GraphicsCleanup },
	{glInit, glCleanup},
	{TimeInit, TimeCleanup}

	// Need to add:
	//
	// Log::Init, Log::Cleanup
	// Window::Init, Window::Cleanup
	// Graphics::Init, Graphics::Cleanup
	// gl::Init, gl::Cleanup
	// Time::Init, Time::Cleanup

};

bool InitGameSystems() noexcept
{
	return TryInitItems(kSystemLifetimes);
}


///
/// Calls the cleanup function of all the provided item lifetimes.
///
template<std::size_t NumItems>
static void CleanupItems(ConstArrayReference<Lifetime, NumItems> itemLifetimes) noexcept;

void CleanupGameSystems() noexcept
{
	CleanupItems(kSystemLifetimes);
}

template<std::size_t NumItems>
void CleanupItems(ConstArrayReference<Lifetime, NumItems> itemLifetimes) noexcept
{
	CleanupItemsStartingAt(itemLifetimes, NumItems);
}

//
static bool InitGameWindow() noexcept;

//
static void CleanupGameWindow() noexcept;

//
static bool InitContext() noexcept;

//
static void CleanupContext() noexcept;

//
static bool InitGraphicsResources() noexcept;

//
static void CleanupGraphicsResources() noexcept;

///
/// All the game state Lifetimes.
/// 
/// It is an array containing instances of the class Lifetime.
/// Every instance is generated by giving an Init and Cleanup function.
/// 
static constexpr Lifetime kStateLifetimes[] =
{
	{InitGameWindow, CleanupGameWindow},
	{InitContext, CleanupContext},
	{InitGraphicsResources, CleanupGraphicsResources}
};

bool InitState() noexcept
{
	return TryInitItems(kStateLifetimes);
}

void CleanupState() noexcept
{
	CleanupItems(kStateLifetimes);
}

/// 
/// <param name="key -> The pressed key's virtual key code."></param>
/// <param name="pressed - > Whether the key was presssed."></param>
static void OnKeyEvent(int key, bool pressed) noexcept;

bool InitGameWindow() noexcept
{
	return true;
}




/// 
/// All the game state Lifetimes Definitions
/// 
/// {InitGameWindow, CleanupGameWindow},
/// {InitContext, CleanupContext},
/// {InitGraphicsResources, CleanupGraphicsResources }
///  

//InitGameWindow()

void CleanupGameWindow() noexcept
{

}

bool InitContext() noexcept
{
	return true;
}

void CleanupContext() noexcept
{

}

bool InitGraphicsResources() noexcept
{
	return true;
}

void CleanupGraphicsResources() noexcept
{

}


/// 
/// All the system Lifetimes Definitions
/// 
/// Log::Init, Log::Cleanup
/// Window::Init, Window::Cleanup
/// Graphics::Init, Graphics::Cleanup
/// gl::Init, gl::Cleanup
/// Time::Init, Time::Cleanup
/// 

bool WindowInit() noexcept
{
	return true;
}

void WindowCleanup() noexcept
{

}

bool GraphicsInit() noexcept
{
	return true;
}

void GraphicsCleanup() noexcept
{

}

bool glInit() noexcept
{
	return true;
}
void glCleanup() noexcept
{

}

bool TimeInit() noexcept
{
	return true;
}

void TimeCleanup() noexcept
{

}

static void OnBeginRun() noexcept;
static void OnFinishRun() noexcept;
static float GetDeltaTime() noexcept;
static void OnUpdate(float deltaTime) noexcept;
static void OnRender() noexcept;

void pong::Run() noexcept
{
	SM_TRACE("Run()");

	OnBeginRun();

	while (isRunning)
	{
		const float deltaTime = GetDeltaTime();

		OnUpdate(deltaTime);
		OnRender();
	}

	OnFinishRun();
}

void LogContextSpecifications() noexcept;

static void OnBeginRun() noexcept
{
	SM_TRACE("OnBeginRun()");
	// Show Window
	// Set Window Resizible (false)

	// Log Context Specifications
	LogContextSpecifications();
	
	// Reset game state
	// Position Paddles

	// srand(currentTime)?
}

void LogContextSpecifications() noexcept
{
	LOG_GL_STRING("GL_VENDOR2: ", GL_VENDOR);
	LOG_GL_STRING("GL_VERSION2: ", GL_VERSION);
	LOG_GL_STRING("GL_RENDERER2: ", GL_RENDERER);
}

void OnFinishRun() noexcept
{
	SM_TRACE("OnFinishRun()");

}

void pong::Cleanup() noexcept
{
	//std::cout << "Cleanup()" << std::endl;
	SM_TRACE("Cleanup()");

}

/*
static void CleanupTextureQuad() noexcept;

static constexpr Lifetime kGraphicsResourcesLifetimes[] =
{
	{InitPaddleProgram, CleanupPaddleProgram},
	{InitBallProgram, CleanupBallProgram},
	{InitQuad, CleanupQuad},
	{InitTextureQuad, CleanupTextureQuad}
};


bool InitGraphicsResources() noexcept
{
	return TryInitItems(kGraphicsResourcesLifetimes);
}

void CleanupGraphicsResources() noexcept
{

}
*/

float GetDeltaTime() noexcept
{	
	//static float sLastTime = 0.0f;

	//const float kNow = Time::Get();
	//const float kTimeDelta = kNow - sLastTime;
	//sLastTime = kNow;

	//return kTimeDelta;

	return 1.0f;
}

void OnUpdate(float deltaTime) noexcept
{
	// Delta time (float deltaTime)
	// isRunning = Window::PollEvents();

	// Update Ball

	// Update Paddles

	// Check collision
	
	// const bool collided = collision();

	// if(collided){CheckBallSideCollision()};
}

void OnRender() noexcept
{

}

// UpdateScores(Side lostSide)
