#include "Render.h"
#include <GLFW/glfw3.h>
#include "../Debug/Log.h"

namespace JADI {
    void JADI::Renderer::initScreenSize(GLFWwindow* window) {
        if (!window) return; // safety check

        // Get the actual framebuffer size
        glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

        // Compute aspect ratio
        if (screenHeight != 0)
            aspectRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
        else
            aspectRatio = 1.0f; // fallback
    }

    void Renderer::Init() {
    }

    void Renderer::Draw() {
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);

        glVertex3f(0.0f, 0.5f, 0.8f);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(0.5f, -0.5f, 0.0f);

        glEnd();
    }

    void Renderer::Shutdown() {
    }
}
