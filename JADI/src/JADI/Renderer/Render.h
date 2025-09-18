#pragma once
#include <GLFW/glfw3.h>

namespace JADI {
    class Renderer {
    public:
        static void Init();
        static void Draw();
        static void Shutdown();
    };
}
