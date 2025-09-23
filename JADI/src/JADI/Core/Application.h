#pragma once

#include "Core.h"

namespace JADI {
    class JADI_API Application {
    public:
        Application();
        virtual ~Application();
        void Run();
        virtual void Render() = 0;
        virtual void Update() = 0;
        long long getDelta();
    private:
        long long dt;
    };
    Application* CreateApplication();
}
