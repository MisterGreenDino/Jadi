#pragma once
#include <GLFW/glfw3.h>
#include "../../Renderer/Render.h"

struct Matrixe {
	float data[4][4];
};

struct Vec4 {
	float x, y, z, w;
};

struct Vec3 {
	float x, y, z;
};


namespace JADI {
	class Projection
	{
	public:
		// Setup variable (near plan, far plan, focal lenght, fov)
		void CalcVar();

		// Setup the camera (position, yaw, pitch)
		void ProjCamera();

		// Setup the projection matrix (perspective)
		void ProjMatrix();

		// Project a 3D vertex into 2D screen space
		Vec3 ProjVertice();


	private:
		Vec3 camPosition;
		float camYaw;
		float camPitch;
		float camFov;

		float focalLength;
		float nearPlane;
		float farPlane;
		float fovFactor;

		Matrixe projectionMatrix;
		Matrixe viewMatrix;

	};

}