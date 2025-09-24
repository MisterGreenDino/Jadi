#include "Render.h"
#include "../Debug/Log.h"

#include <GLFW/glfw3.h>
#include <random>

static int runCount = 0;

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
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(-0.1f, 0.1f);

        const int numMeshes = 100000;
        const int estimatedVertices = numMeshes * 2;

        vertices.clear();
        projected.clear();
        projectedFlag.clear();
        meshList.clear();

        vertices.reserve(estimatedVertices);
        projected.resize(estimatedVertices);
        projectedFlag.resize(estimatedVertices, false);
        meshList.reserve(numMeshes);

        int prevIndices[3] = { -1, -1, -1 };

        // pre-fill first 3 vertices
        for (int i = 0; i < 3; i++) {
            vertices.push_back({ dist(gen), dist(gen), dist(gen) });
            prevIndices[i] = i;
        }

        meshList.push_back({ prevIndices[0], prevIndices[1], prevIndices[2] });

        for (int i = 1; i < numMeshes; i++) {
            Mesh m;
            int shareCount = (gen() % 2) + 1; // share 1 or 2 vertices

            if (shareCount == 2) {
                m.v0_id = prevIndices[0];
                m.v1_id = prevIndices[1];
                vertices.push_back({ dist(gen), dist(gen), dist(gen) });
                m.v2_id = vertices.size() - 1;
            }
            else {
                m.v0_id = prevIndices[0];
                vertices.push_back({ dist(gen), dist(gen), dist(gen) });
                m.v1_id = vertices.size() - 1;
                vertices.push_back({ dist(gen), dist(gen), dist(gen) });
                m.v2_id = vertices.size() - 1;
            }

            prevIndices[0] = m.v0_id;
            prevIndices[1] = m.v1_id;
            prevIndices[2] = m.v2_id;

            meshList.push_back(m);
        }
        LOG_CORE_ERROR("Render init finished");
    }




    void Renderer::Draw() {
        runCount++;
        LOG_CORE_INFO(runCount);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // set screen coordinates
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, screenWidth, screenHeight, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        proj.SetupVar();
        proj.ProjCamera();
        proj.ProjMatrix();

        // reset flags
        std::fill(projectedFlag.begin(), projectedFlag.end(), false);

        for (const Mesh& m : meshList) {
            if (!Chunk::IsMeshInView()) continue;

            // project vertices only if not already
            if (!projectedFlag[m.v0_id]) {
                projected[m.v0_id] = proj.ProjVertice(vertices[m.v0_id].x, vertices[m.v0_id].y, vertices[m.v0_id].z);
                projectedFlag[m.v0_id] = true;
            }
            if (!projectedFlag[m.v1_id]) {
                projected[m.v1_id] = proj.ProjVertice(vertices[m.v1_id].x, vertices[m.v1_id].y, vertices[m.v1_id].z);
                projectedFlag[m.v1_id] = true;
            }
            if (!projectedFlag[m.v2_id]) {
                projected[m.v2_id] = proj.ProjVertice(vertices[m.v2_id].x, vertices[m.v2_id].y, vertices[m.v2_id].z);
                projectedFlag[m.v2_id] = true;
            }

            const Vec3& v0 = projected[m.v0_id];
            const Vec3& v1 = projected[m.v1_id];
            const Vec3& v2 = projected[m.v2_id];

            if (!std::isfinite(v0.x) || !std::isfinite(v1.x) || !std::isfinite(v2.x))
                continue;

            glColor3f(0.0f, 0.0f, 0.0f);
            glBegin(GL_TRIANGLES);
            glVertex2f(v0.x, v0.y);
            glVertex2f(v1.x, v1.y);
            glVertex2f(v2.x, v2.y);
            glEnd();
        }
    }

    void Renderer::Shutdown() {
    }
}
