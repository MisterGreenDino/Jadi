#include "Application.h"
#include "../Debug/Log.h"

namespace JADI {
    Application::Application() {
        JADI::Log::Init();
    }
    Application::~Application() {}
    void Application::Run() {
        while (true);
    }
}
