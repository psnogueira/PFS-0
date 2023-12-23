///
/// Log Messages:
/// 
/// 1- SM_TRACE(message, ...)
/// 2- SM_WARNING(message, ...)
/// 3- SM_ERROR(message, ...)
/// 4- SM_CUSTOM(color, title, message, ...)
/// 5- SM_ASSERT(X, message, ...)
/// 

#pragma once

#ifdef _WIN32
#define DEBUG_BREAK() __debugbreak();
#endif

#include <stdio.h>

///
/// Enum of all available text colors
/// 
enum TextColor
{
	TEXT_COLOR_BLACK,
	TEXT_COLOR_RED,
	TEXT_COLOR_GREEN,
	TEXT_COLOR_YELLOW,
	TEXT_COLOR_BLUE,
	TEXT_COLOR_MAGENTA,
	TEXT_COLOR_CYAN,
	TEXT_COLOR_WHITE,
	TEXT_COLOR_BRIGHT_BLACK,
	TEXT_COLOR_BRIGHT_RED,
	TEXT_COLOR_BRIGHT_GREEN,
	TEXT_COLOR_BRIGHT_YELLOW,
	TEXT_COLOR_BRIGHT_BLUE,
	TEXT_COLOR_BRIGHT_MAGENTA,
	TEXT_COLOR_BRIGHT_CYAN,
	TEXT_COLOR_BRIGHT_WHITE,
	TEXT_COLOR_COUNT
};

template <typename ...Args>
void _log(const char* prefix, const char* message, TextColor textColor, Args... args) // Not supposed to be used directly.
{
	static const char* TextColorTable[TEXT_COLOR_COUNT] =
	{
		"\x1b[30m", // TEXT_COLOR_BLACK
		"\x1b[31m", // TEXT_COLOR_RED
		"\x1b[32m", // TEXT_COLOR_GREEN
		"\x1b[33m", // TEXT_COLOR_YELLOW
		"\x1b[34m", // TEXT_COLOR_BLUE
		"\x1b[35m", // TEXT_COLOR_MAGENTA
		"\x1b[36m", // TEXT_COLOR_CYAN
		"\x1b[37m", // TEXT_COLOR_WHITE
		"\x1b[90m", // TEXT_COLOR_BRIGHT_BLACK
		"\x1b[91m", // TEXT_COLOR_BRIGHT_RED
		"\x1b[92m", // TEXT_COLOR_BRIGHT_GREEN
		"\x1b[93m", // TEXT_COLOR_BRIGHT_YELLOW
		"\x1b[94m", // TEXT_COLOR_BRIGHT_BLUE
		"\x1b[95m", // TEXT_COLOR_BRIGHT_MAGENTA
		"\x1b[96m", // TEXT_COLOR_BRIGHT_CYAN
		"\x1b[97m", // TEXT_COLOR_BRIGHT_WHITE
	};

	char formatBuffer[2048] = {};		//8912 | 8192
	sprintf_s(formatBuffer, "%s%s%s \033[0m", TextColorTable[textColor], prefix, message);
	// "\x1b[31m" + message + "\033[0m"; // Black Text

	char textBuffer[2048] = {};
	sprintf_s(textBuffer, formatBuffer, args...);

	// Print text.
	puts(textBuffer);
}

#define SM_TRACE(message, ...) _log("TRACE: ", message, TEXT_COLOR_GREEN, ##__VA_ARGS__);
#define SM_WARN(message, ...) _log("WARNING: ", message, TEXT_COLOR_YELLOW, ##__VA_ARGS__);
#define SM_ERROR(message, ...) _log("ERROR: ", message, TEXT_COLOR_RED, ##__VA_ARGS__);
#define SM_CUSTOM(color, title, message, ...) _log(title, message, color, ##__VA_ARGS__);
#define SM_ASSERT(x, message, ...)                      \
{                                                       \
	if(!(x))                                            \
	{                                                   \
		SM_ERROR(message, ##__VA_ARGS__);               \
		DEBUG_BREAK();                                  \
		SM_ERROR("ASERTION HIT!");						\
	}                                                   \
}


