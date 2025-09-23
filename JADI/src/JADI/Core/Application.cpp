#include "Application.h"
#include "../Debug/Log.h"
#include "../Renderer/Render.h"
#include "../Math/Rendering/Projection.h"


#include <chrono>
#include <GLFW/glfw3.h>

namespace JADI {

    Application::Application() {
        dt = 0;
        JADI::Log::Init();
    }

    Application::~Application() {}
    
    
    void Application::Run() {
        LOG_CORE_INFO("Initialized Log!");
        auto last = std::chrono::high_resolution_clock::now();
        long long delta = 0;

        if (!glfwInit()) {
            LOG_CORE_FATAL("Failed to initialize GLFW");
            return;
        }

        GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
        if (!window) {
            LOG_CORE_ERROR("Failed to create GLFW window");
            glfwTerminate();
            return;
        }
        else { LOG_CORE_INFO("GLFW window was created"); }

        //From now on, all OpenGL calls (glClear, glDraw*, etc.) will affect this window.
        glfwMakeContextCurrent(window);

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

        JADI::Renderer render;
        render.initScreenSize(window);
        LOG_CORE_INFO(render.getScreenWidth());
        LOG_CORE_INFO(render.getScreenHeight());


        while (!glfwWindowShouldClose(window)) {
            //Main loop
            glClear(GL_COLOR_BUFFER_BIT);

            //Input::Process();
            //Update(delta);
            Renderer::Draw();

            glfwSwapBuffers(window);            //Prevent flickering frame to frame
            glfwPollEvents();                   //Handle inputs (freeze if not here)


            
            //Delta time calculation
            auto now = std::chrono::high_resolution_clock::now();
            delta = std::chrono::duration_cast<std::chrono::microseconds>(now - last).count();;
            last = now;
        }

        glfwDestroyWindow(window);
        glfwTerminate();
    }

}