#include "Render.h"
#include <GLFW/glfw3.h>
#include "../Debug/Log.h"

namespace JADI {
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
