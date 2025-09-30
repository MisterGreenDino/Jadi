#include "Projection.h"
#include <cmath>


void JADI::Projection::SetupVar() {
    camFov = 50.0f;
    aspectRatio = screenWidth / screenHeight;
    nearPlane = 0.1f;   // small near plane
    farPlane = 100.0f;  // far enough
    camPosition = { 0, 0, 3 }; // camera 3 units away along +z
    camYaw = 0.0f;
    camPitch = 0.0f;

    float fovRad = camFov * (3.14159265f / 180.0f);
    focalLength = 1.0f / tanf(fovRad * 0.5f);
}


void JADI::Projection::ProjCamera() {
    // camera looks toward -z
    Vec3 forward = { 0, 0, -1 };
    Vec3 up = { 0, 1, 0 };
    Vec3 right = { 1, 0, 0 };

    // Translation part
    viewMatrix.data[0][0] = right.x; viewMatrix.data[0][1] = up.x; viewMatrix.data[0][2] = -forward.x; viewMatrix.data[0][3] = 0;
    viewMatrix.data[1][0] = right.y; viewMatrix.data[1][1] = up.y; viewMatrix.data[1][2] = -forward.y; viewMatrix.data[1][3] = 0;
    viewMatrix.data[2][0] = right.z; viewMatrix.data[2][1] = up.z; viewMatrix.data[2][2] = -forward.z; viewMatrix.data[2][3] = 0;

    viewMatrix.data[3][0] = -camPosition.x;
    viewMatrix.data[3][1] = -camPosition.y;
    viewMatrix.data[3][2] = -camPosition.z;
    viewMatrix.data[3][3] = 1.0f;
}

void JADI::Projection::ProjMatrix() {
    // zero matrix
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            projectionMatrix.data[i][j] = 0;

    float f = focalLength;
    float a = aspectRatio;
    float Zn = nearPlane;
    float Zf = farPlane;

    projectionMatrix.data[0][0] = f / a;
    projectionMatrix.data[1][1] = f;
    projectionMatrix.data[2][2] = (Zf + Zn) / (Zn - Zf);
    projectionMatrix.data[2][3] = (2 * Zf * Zn) / (Zn - Zf);
    projectionMatrix.data[3][2] = -1;
    projectionMatrix.data[3][3] = 0;

    // compute viewProj
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            viewProjMatrix.data[i][j] = 0.0f;
            for (int k = 0; k < 4; k++)
                viewProjMatrix.data[i][j] += viewMatrix.data[i][k] * projectionMatrix.data[k][j];
        }
}