#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "../Debug/Log.h"
#include "../Math/MathStruct.h"

namespace JADI {
	class Projection
	{
	public:
		// Setup variable (near plan, far plan, focal lenght, fov)
		void SetupVar();

		// Setup the camera (position, yaw, pitch)
		void ProjCamera();

		// Setup the projection matrix (perspective)
		void ProjMatrix();

		// Project a 3D vertex into 2D screen space
		Vec3 ProjVertice(float x, float y,float z);

		void setScreenHeight(float height) { screenHeight = height; }
		void setScreenWidth(float width) { screenWidth = width; }
		void setAspectRatio(float ratio) { aspectRatio = ratio; }

		const Vec3& getCamPosition() const { return camPosition; }
		float getCamYaw() const { return camYaw; }
		float getCamPitch() const { return camPitch; }
		float getCamFov() const { return camFov; }
		float getFov() const { return camFov; }
		float getAspectRatio() const { return aspectRatio; }
		float getNearPlane() const { return nearPlane; }
		float getFarPlane() const { return farPlane; }
		float getFocalLength() const { return focalLength; }

	private:
		float aspectRatio;
		float screenWidth;
		float screenHeight;

		Vec3 camPosition;
		float camYaw;
		float camPitch;
		float camFov;

		float nearPlane;
		float farPlane;
		float focalLength;

		Matrix projectionMatrix;
		Matrix viewMatrix;
		Matrix viewProjMatrix;

	};

}