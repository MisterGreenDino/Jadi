#include "Render.h"

#include <GLFW/glfw3.h>

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


    void Renderer::Init() {


    }

    // In Renderer.cpp
    void JADI::Renderer::Draw() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set orthographic projection for pixel coordinates
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, screenWidth, screenHeight, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        proj.SetupVar();
        proj.ProjCamera();
        proj.ProjMatrix();

        Vec3 v0 = proj.ProjVertice(0.2, 0.5, -0.2);
        Vec3 v1 = proj.ProjVertice(-0.5, -0.5, -0.5);
        Vec3 v2 = proj.ProjVertice(0.5, -0.5, -0.5);

        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(v0.x, v0.y);
        glVertex2f(v1.x, v1.y);
        glVertex2f(v2.x, v2.y);
        glEnd();

        Vec3 v3 = proj.ProjVertice(0.2, 0.5, -1.0);
        Vec3 v4 = proj.ProjVertice(-0.5, -0.5, -0.5);
        Vec3 v5 = proj.ProjVertice(0.5, -0.5, -0.5);
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_TRIANGLES);
        glVertex2f(v3.x, v3.y);
        glVertex2f(v4.x, v4.y);
        glVertex2f(v5.x, v5.y);
        glEnd();
    }

    void Renderer::Shutdown() {
    }
}
