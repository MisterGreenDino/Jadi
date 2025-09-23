#pragma once
#include <GLFW/glfw3.h>
#include "../Math/Projection.h"
#include "../Debug/Log.h"

namespace JADI {
    class Renderer {
    public:

        static void Init();
        void Draw();
        static void Shutdown();
        void initScreenSize(GLFWwindow* window);


        int getScreenWidth() const { return screenWidth; }
        int getScreenHeight() const { return screenHeight; }
        int getAspectRatio() const { return aspectRatio; }

    private:
        Projection proj;
        int screenHeight;
        int screenWidth;
        
        float aspectRatio;
    };

}
