#pragma once
#include <glad/glad.h>

#include "../Math/Projection.h"
#include "../Math/Chunk.h"
#include "../Math/MathStruct.h"

#include "Shader.h"

#include "../Debug/Log.h"
#include <functional>



struct Vec3Hash {
    std::size_t operator()(const Vec3& v) const noexcept {
        auto fx = *reinterpret_cast<const std::uint32_t*>(&v.x);
        auto fy = *reinterpret_cast<const std::uint32_t*>(&v.y);
        auto fz = *reinterpret_cast<const std::uint32_t*>(&v.z);

        std::size_t h = fx;
        h = h * 0x9e3779b9 ^ fy;
        h = h * 0x9e3779b9 ^ fz;
        return h;
    }
};

namespace JADI {
    class Renderer {
    public:

        void Init();
        void Draw();
        static void Shutdown();
        void initScreenSize(GLFWwindow* window);


        int getScreenWidth() const { return screenWidth; }
        int getScreenHeight() const { return screenHeight; }
        int getAspectRatio() const { return aspectRatio; }

    private:
        Projection proj;
        int screenHeight;
        int screenWidth;

        float aspectRatio;

        GLuint vboID;
        GLuint vaoID;

        std::vector<Mesh> meshList;
        std::vector<Vec3> vertices;

        Shader* shader;

        std::vector<Vec3> verticesWorld;
        std::vector<Vec3> verticesScreen;
    };

}
