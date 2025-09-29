#include "Render.h"
#include "../Debug/Log.h"

#include <random>

namespace JADI {
    void JADI::Renderer::initScreenSize(GLFWwindow* window) {
        if (!window) return;

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        // Only update if size changed
        if (width != screenWidth || height != screenHeight) {
            screenWidth = width;
            screenHeight = height;

            if (screenHeight != 0)
                aspectRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
            else
                aspectRatio = 1.0f;        

            glViewport(0, 0, screenWidth, screenHeight);
        }
        proj.setAspectRatio(aspectRatio);
        proj.setScreenWidth(screenWidth);
        proj.setScreenHeight(screenHeight);
    }


    //GENERATE MESHES FOR TESTING PURPOSE
    void Renderer::Init() {
    }

    void Renderer::Draw() {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        proj.SetupVar();
        proj.ProjCamera();
        proj.ProjMatrix();

       
    }

    void Renderer::Shutdown() {
    }
}
