#include "Projection.h"
#include <cmath>

void JADI::Projection::CalcVar() {
    // Convert FOV to radians if it’s in degrees
    float fovRad = camFov * (3.14159265f / 180.0f);

    // Focal length factor
    fovFactor = 1.0f / tanf(fovRad * 0.5f);




	//need f,a,zn,zf,fov
}