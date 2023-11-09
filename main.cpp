#include "Pong.hpp"
#include "Window.hpp"
#include <iostream>

int main()
{
    ///
    /// Início da função main.cpp
    ///

    if (!pong::Init())
    {
        return -1;
    }

    pong::Run();
    pong::Cleanup();

    ///
    /// Fim da função main.cpp
    ///

    //
    if (!pong::PlayGame())
    {
        return 1;
    }
    
    return 0;
}
