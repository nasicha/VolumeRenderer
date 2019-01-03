#include "Camera.h"

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp> 


Camera::Camera()
{
	reset();
}

Camera::~Camera(void)
{
}

void Camera::reset()
{
	mRadius = 5.0f;
	mAzimuth = 0.0f;
	mPolar = M_PI / 2.0f;

	mPos = glm::vec3(0.0f, 0.0f, -5.0f);
	mUp = glm::vec3(0.0f, 1.0f, 0.0f);
	mTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	mNear = 0.1f;
	mFar = 1000.0f;
	mFieldOfView = 45.0f;
	mAspect = 4.0f / 3.0f;
	mOrthogonal = false;
	mLeft = -2.0f;
	mRight = 2.0f;
	mTop = 2.0f;
	mBottom = -2.0f;
	buildViewMatrix();
	buildProjectionMatrix();
}

void Camera::setOrthogonalBorders(float left, float right, float top, float bottom)
{
	mLeft = left;
	mRight = right;
	mTop = top;
	mBottom = bottom;
}

void Camera::buildViewMatrix(void)
{
	glm::vec3 pos;
	pos.z = mRadius * cosf(mAzimuth) * sinf(mPolar);
	pos.x = mRadius * sinf(mAzimuth) * sinf(mPolar);
	pos.y = mRadius * cosf(mPolar);
	mViewMatrix = glm::lookAt(pos, mTarget, mUp);
	//mViewMatrix = glm::lookAt(mPos,mTarget,mUp);
}

void Camera::buildProjectionMatrix(void)
{
	if (mOrthogonal) {
		mProjectionMatrix = glm::ortho(mLeft, mRight, mBottom, mTop, mNear, mFar);
	}
	else {
		mProjectionMatrix = glm::perspective(glm::radians(mFieldOfView), mAspect, mNear, mFar);
	}
}

void Camera::zoom(float t)
{
	mRadius -= t;
	if (mRadius < 2.0f)
		mRadius = 2.0f;

	glm::vec3 f = glm::normalize(mTarget - mPos);
	mPos += f*t;
	//mTarget += f*t;
	buildViewMatrix();
}

void Camera::rotateAzimuth(float t)
{
	mAzimuth -= t;
	buildViewMatrix();
}

void Camera::rotatePolar(float t)
{
	mPolar -= t;
	if (mPolar < 0.1f) {
		mPolar = 0.1f;
	}
	if (mPolar > M_PI - 0.1f) {
		mPolar = M_PI - 0.1f;
	}
	buildViewMatrix();
}

void Camera::moveForwards(float t)
{
	glm::vec3 f = glm::normalize(mTarget - mPos);
	mPos += f*t;
	mTarget += f*t;
	buildViewMatrix();
}

void Camera::moveBackwards(float t)
{
	glm::vec3 f = glm::normalize(mTarget - mPos);
	mPos -= f*t;
	mTarget -= f*t;
	buildViewMatrix();
}

void Camera::moveLeft(float t)
{
	glm::vec3 f = glm::normalize(mTarget - mPos);
	glm::vec3 u = glm::normalize(mUp);
	glm::vec3 s = glm::normalize(glm::cross(f, u));
	mPos -= s*t;
	mTarget -= s*t;
	buildViewMatrix();
}

void Camera::moveRight(float t)
{
	glm::vec3 f = glm::normalize(mTarget - mPos);
	glm::vec3 u = glm::normalize(mUp);
	glm::vec3 s = glm::normalize(glm::cross(f, u));
	mPos += s*-t;
	mTarget += t;
	buildViewMatrix();
}

void Camera::moveUp(float t)
{
	glm::vec3 f = glm::normalize(mTarget - mPos);
	glm::vec3 u = glm::normalize(mUp);
	glm::vec3 s = glm::normalize(glm::cross(f, u));
	u = glm::cross(s, f);
	mPos += u*t;
	mTarget += u*t;
	buildViewMatrix();
}

void Camera::moveDown(float t)
{
	glm::vec3 f = glm::normalize(mTarget - mPos);
	glm::vec3 u = glm::normalize(mUp);
	glm::vec3 s = glm::normalize(glm::cross(f, u));
	u = glm::cross(s, f);
	mPos -= u*t;
	mTarget -= u*t;
	buildViewMatrix();
}

void Camera::rotateUp(float t)
{
	glm::vec3 f = glm::normalize(mTarget - mPos);
	glm::vec3 u = glm::normalize(mUp);
	glm::vec3 s = glm::normalize(glm::cross(f, u));
	glm::mat4 rotation = glm::rotate(glm::mat4(), t, s);
	glm::vec3 newF = glm::vec3(rotation*glm::vec4(f, 0));
	mUp = glm::vec3(rotation*glm::vec4(mUp, 0.0f));
	mTarget = mPos + newF;
	buildViewMatrix();
}

void Camera::rotateDown(float t)
{
	glm::vec3 f = glm::normalize(mTarget - mPos);
	glm::vec3 u = glm::normalize(mUp);
	glm::vec3 s = glm::normalize(glm::cross(f, u));
	glm::mat4 rotation = glm::rotate(glm::mat4(), -t, s);
	glm::vec3 newF = glm::vec3(rotation*glm::vec4(f, 0.0f));
	mUp = glm::vec3(rotation*glm::vec4(mUp, 0.0f));
	mTarget = mPos + newF;
	buildViewMatrix();
}

void Camera::rotateLeft(float t)
{
	glm::vec3 f = glm::normalize(mTarget - mPos);
	glm::vec3 u = glm::normalize(mUp);
	glm::mat4 rotation = glm::rotate(glm::mat4(), t, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 newF = glm::vec3(rotation*glm::vec4(f, 0.0f));
	mTarget = mPos + newF;
	mUp = glm::vec3(rotation*glm::vec4(mUp, 0.0f));
	buildViewMatrix();
}

void Camera::rotateRight(float t)
{
	glm::vec3 f = glm::normalize(mTarget - mPos);
	glm::vec3 u = glm::normalize(mUp);
	glm::mat4 rotation = glm::rotate(glm::mat4(), -t, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 newF = glm::vec3(rotation*glm::vec4(f, 0.0f));
	mTarget = mPos + newF;
	mUp = glm::vec3(rotation*glm::vec4(mUp, 0.0f));
	buildViewMatrix();
}