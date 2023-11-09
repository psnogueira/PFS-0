/***************************************
 * Pong game
 * Made with OpenGL
 *--------------------------------------
 * Created by psnogueira on 17/10/2023
 ***************************************/

#pragma once

namespace pong
{
	/// ! @brief Initializes the game and its systems. 
	/// 
	/// If the game is already initialized, this function returns false.
	/// If this function fails, it cleans up all the resources before returning.
	/// 
	/// @return Whether the game was successfully initialized.
	/// 
	bool Init() noexcept;

	/// ! @brief Game's main loop.
	/// 
	void Run() noexcept;

	///! @brief Cleans up the resources used by the game and its systems.
	///
	void Cleanup() noexcept;

	bool PlayGame();

} // namespace dpong
