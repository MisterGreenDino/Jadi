#pragma once
#include <GLFW/glfw3.h>

namespace JADI {
    class Renderer {
    public:
        static void Init();
        static void Draw();
        static void Shutdown();
        void initScreenSize(GLFWwindow* window);


        int getScreenWidth() const { return screenWidth; }
        int getScreenHeight() const { return screenHeight; }
    private:
        int screenHeight;
        int screenWidth;
        
        float aspectRatio;
    };

}
