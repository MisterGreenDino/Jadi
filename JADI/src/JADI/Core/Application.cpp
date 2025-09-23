#include "Application.h"
#include "../Debug/Log.h"
#include <chrono>

namespace JADI {

    Application::Application() {
        dt = 0;
        JADI::Log::Init();
    }
    Application::~Application() {}
    
    
    void Application::Run() {
        LOG_CORE_INFO("Initialized Log!");
        auto last = std::chrono::high_resolution_clock::now();
        auto now = std::chrono::high_resolution_clock::now();
        while (true) {
            //Main loop
            Render();
            Update();
            //Delta time calculation
            auto now = std::chrono::high_resolution_clock::now();
            dt = std::chrono::duration_cast<std::chrono::microseconds>(now - last).count();;
            last = now;
        }
    }

    long long Application::getDelta() {
        return dt;
    }
}
