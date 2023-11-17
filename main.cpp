#include "Pong.hpp"
#include "Window.hpp"
#include <iostream>

int main()
{
    //Arrumar
    // Arrumar

    if (!pong::Init())
    {
        return -1;
    }

    pong::Run();
    pong::Cleanup();
    
    return 0;
}
