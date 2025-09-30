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


#include <cstdlib> // for rand()
#include <cmath>   // for cos, sin

    void Renderer::Init() {
        shader = new Shader("D:\\Jadi\\Jadi\\JADI\\src\\JADI\\Renderer\\Shaders\\red.vert", "D:\\Jadi\\Jadi\\JADI\\src\\JADI\\Renderer\\Shaders\\red.frag");


        glEnable(GL_DEPTH_TEST);
        glGenVertexArrays(1, &vaoID);
        glGenBuffers(1, &vboID);

        int n = 50000000;
        float maxRadius = 0.5f;
        float size = 0.01f;

        for (int i = 0; i < n; i++) {
            float r = maxRadius * sqrt(static_cast<float>(rand()) / RAND_MAX);
            float angle = 2.0f * 3.1415926f * (static_cast<float>(rand()) / RAND_MAX);

            float cx = r * cos(angle);
            float cy = r * sin(angle);

            Vec3 v0 = { cx,        cy, 0.0f };
            Vec3 v1 = { cx + size, cy, 0.0f };
            Vec3 v2 = { cx,        cy + size, 0.0f };

            verticesWorld.push_back(v0);
            verticesWorld.push_back(v1);
            verticesWorld.push_back(v2);

            Mesh mesh;
            mesh.v0_id = verticesWorld.size() - 3;
            mesh.v1_id = verticesWorld.size() - 2;
            mesh.v2_id = verticesWorld.size() - 1;
            meshList.push_back(mesh);

            if ((i + 1) % 10000 == 0) {
                LOG_CORE_INFO("Generated {} meshes so far, total vertices: {}", i + 1, verticesWorld.size());
            }
        }

        LOG_CORE_INFO("Finished generating meshes: total meshes = {}, total vertices = {}",
            meshList.size(), verticesWorld.size());
        // Now generate GPU buffers
        glBindVertexArray(vaoID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, verticesWorld.size() * sizeof(Vec3), verticesWorld.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), (void*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);


        LOG_CORE_INFO("Mesh initialized: total vertices = {}", verticesWorld.size());
    }
    
    void Renderer::Draw() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update projection & view
        proj.SetupVar();
        proj.ProjCamera();
        proj.ProjMatrix();

        glBindVertexArray(vaoID);
        shader->Bind();
        GLuint mvpLoc = glGetUniformLocation(shader->GetProgramID(), "uMVP");
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, proj.GetViewProjMatrix());
        glDrawArrays(GL_TRIANGLES, 0, verticesWorld.size());
        shader->Unbind();
        glBindVertexArray(0);

    }

    void Renderer::Shutdown() {
    
    }
}
