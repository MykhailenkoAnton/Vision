#include "Engine.h"
#include <iostream>

namespace Vision
{
    Engine::Engine()
    {
        std::cout << "Hello from Vision Engine! Version: " << version() << std::endl;
    }
}  // namespace Vision
