#pragma once
#include <iostream>
#include <glad.h>
#include <GLFW/includes/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Camera
{
private:

	/*Window Resolution*/
	unsigned int m_unScreenWidth = 0;
	unsigned int m_unScreenHeight = 0;

	/*Camera vectors needed to calculate all the needed data*/
	glm::vec3 m_cameraPosition;
	glm::vec3 m_cameraTarget;
	glm::vec3 m_cameraDirection;
	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;

	/*Camera Data*/
	float m_fCameraSpeed = 0.0f;
	float m_fFieldOfView = 0.0f;
	float m_fYaw = 0.0f;	
	float m_fPitch = 0.0f;
	float m_fCurrentX = 0.0f;
	float m_fCurrentY = 0.0f;
	float m_fSensitivity = 0.0f;
	bool m_fMouseMemoryData = false;

	/*Global view Matrix*/
	glm::mat4 m_view;
	/*Global view Projection*/
	glm::mat4 m_projection;

public:

	/*Initialize the camera members*/
	bool Init(const unsigned int& unScreenWidth,
		      const unsigned int& unScreenHeight);

	/*Update function, called every frame*/
	void Process(Shader& shader);

	/*Setters for the needed data*/
	void SetCameraPosition(glm::vec3& cameraPosition);
	void SetCameraTarget(glm::vec3& cameraTarget);
	void SetCameraDirection(glm::vec3& cameraDirection);
	void SetCameraFront(glm::vec3& cameraFront);
	void SetCameraUp(glm::vec3& cameraUp);

	void SetCameraSpeed(float& fCameraSpeed);

	/*Getters for the needed data*/
	const glm::vec3& GetCameraPosition();
	const glm::vec3& GetCameraTarget();
	const glm::vec3& GetCameraDirection();
	const glm::vec3& GetCameraFront();
	const glm::vec3& GetCameraUp();
	const glm::mat4& GetGlobalView();

	const float& GetCameraSpeed();

	/*Handle Event*/
	void HandleEvent(GLFWwindow* windowPtr, const float& fDeltaTime);
	void MouseScrollEvent(GLFWwindow* windowPtr, double dXoffset, double dYoffset);
	void MouseEvent(GLFWwindow* windowPtr, double dXoffset, double dYoffset);
};