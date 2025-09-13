#include "Application.h"
#include "../Debug/Log.h"
#include <chrono>

namespace JADI {
    Application::Application() {
        JADI::Log::Init();
    }
    Application::~Application() {}
    void Application::Run() {
        JADI_CORE_FATAL("Initialized Log!");
        auto last = std::chrono::high_resolution_clock::now();
        long long delta = 0;
        while (true) {
            //Main loop


            
            //Delta time calculation
            auto now = std::chrono::high_resolution_clock::now();
            delta = std::chrono::duration_cast<std::chrono::microseconds>(now - last).count();;
            last = now;
        }
    }
}
