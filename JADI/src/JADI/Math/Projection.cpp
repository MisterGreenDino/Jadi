#include "Projection.h"
#include <cmath>


void JADI::Projection::SetupVar() {
    // Convert FOV to radians
    camFov = 50;
    float fovRad = camFov * (3.14159265f / 180.0f);

    // Focal length factor (fovFactor)
    focalLength = 1.0f / tanf(fovRad * 0.5f);    
    
    // Near and far planes
    nearPlane = 1.0f / (2.0f * tanf(fovRad * 0.5f)); // optional, can be 0.1 or similar
    farPlane = 100.0f; // render distance

    //Temporary camera specs
    camPosition.x = 0;
    camPosition.y = 0;
    camPosition.z = 0;
    camYaw = 0;
    camPitch = 0;
}


void JADI::Projection::ProjCamera() {
    float yawRad = camYaw * 3.14159265f / 180.0f;
    float pitchRad = camPitch * 3.14159265f / 180.0f;

    // Compute forward vector
    Vec3 forward{
        sinf(yawRad) * cosf(pitchRad),
        sinf(pitchRad),
        -cosf(yawRad) * cosf(pitchRad)
    };

    // Compute right vector
    Vec3 right{
        cosf(yawRad),
        0,
        sinf(yawRad)
    };

    // Compute up vector = cross(forward, right)
    Vec3 up{
        forward.y * right.z - forward.z * right.y,
        forward.z * right.x - forward.x * right.z,
        forward.x * right.y - forward.y * right.x
    };

    // Clear view matrix
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            viewMatrix.data[i][j] = 0.0f;

    //Set the view matrix by roation
    viewMatrix.data[0][0] = right.x;
    viewMatrix.data[0][1] = up.x;
    viewMatrix.data[0][2] = -forward.x;
    viewMatrix.data[0][3] = 0.0f;

    viewMatrix.data[1][0] = right.y;
    viewMatrix.data[1][1] = up.y;
    viewMatrix.data[1][2] = -forward.y;
    viewMatrix.data[1][3] = 0.0f;

    viewMatrix.data[2][0] = right.z;
    viewMatrix.data[2][1] = up.z;
    viewMatrix.data[2][2] = -forward.z;
    viewMatrix.data[2][3] = 0.0f;

    // Translation part
    viewMatrix.data[3][0] = -(right.x * camPosition.x + right.y * camPosition.y + right.z * camPosition.z);
    viewMatrix.data[3][1] = -(up.x * camPosition.x + up.y * camPosition.y + up.z * camPosition.z);
    viewMatrix.data[3][2] = (forward.x * camPosition.x + forward.y * camPosition.y + forward.z * camPosition.z);
    viewMatrix.data[3][3] = 1.0f;
}


void JADI::Projection::ProjMatrix() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            projectionMatrix.data[i][j] = 0.0f;

    float f = focalLength;
    float a = aspectRatio;
    float Zn = nearPlane;
    float Zf = farPlane;

    projectionMatrix.data[0][0] = f / a;
    projectionMatrix.data[1][1] = f;
    projectionMatrix.data[2][2] = (Zf + Zn) / (Zn - Zf);
    projectionMatrix.data[2][3] = 2 * (Zf * Zn) / (Zn - Zf);
    projectionMatrix.data[3][2] = -1;
    projectionMatrix.data[3][3] = 0;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            viewProjMatrix.data[i][j] = 0.0f;
            for (int k = 0; k < 4; k++)
                viewProjMatrix.data[i][j] += viewMatrix.data[i][k] * projectionMatrix.data[k][j];
        }
}

Vec3 JADI::Projection::ProjVertice(float x, float y, float z) {
    const float* m = &viewProjMatrix.data[0][0]; // pointer to matrix data for fast access
    float px = m[0] * x + m[1] * y + m[2] * z + m[3];
    float py = m[4] * x + m[5] * y + m[6] * z + m[7];
    float pz = m[8] * x + m[9] * y + m[10] * z + m[11];
    float pw = m[12] * x + m[13] * y + m[14] * z + m[15];

    // avoid divide by zero
    float invW = (pw != 0.0f) ? (1.0f / pw) : 10000.0f;

    Vec3 screen;
    screen.x = (px * invW + 1.0f) * 0.5f * screenWidth;
    screen.y = (1.0f - (py * invW + 1.0f) * 0.5f) * screenHeight;
    screen.z = pz * invW;

    return screen;
}