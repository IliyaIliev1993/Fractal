#include "Camera.h"

bool Camera::Init(const unsigned int& unScreenWidth,
				  const unsigned int& unScreenHeight)
{
	m_unScreenWidth = unScreenWidth;
	m_unScreenHeight = unScreenHeight;

	/*Initial position of Camera*/
	m_cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	/*Target of the camera that is pointing of*/
	m_cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	/*The camera direction is the vector that is poiting in backwards of the target*/
	m_cameraDirection = glm::normalize(m_cameraPosition - m_cameraTarget);
	/*The camera front is the vector that is pointing in front of the camera*/
	m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	/*The camera Up is the max value defined of the camera Y*/
	m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	/*Setting the camera Speed*/
	m_fCameraSpeed = 0.75f;
	/*Setting field of view*/
	m_fFieldOfView = 45.0f;

	m_fYaw = -90.0f;
	m_fPitch = 0.0f;
	m_fCurrentX = static_cast<float>(m_unScreenWidth / 2.0f);
	m_fCurrentY = static_cast<float>(m_unScreenHeight / 2.0f);
	m_fSensitivity = 0.1f;

	std::cout << "Camera::Init() - Initialization of Camera successful !" << std::endl;
	return true;
}

void Camera::Process(Shader& shader)
{
	shader.use();

	m_view = glm::mat4(1.0f);
	m_projection = glm::mat4(1.0f);
	m_view = glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraFront, m_cameraUp);
	m_projection = glm::perspective(glm::radians(m_fFieldOfView), (float)m_unScreenWidth / (float)m_unScreenHeight, 0.1f, 100.0f);

	shader.setMat4("view", m_view);
	shader.setMat4("projection", m_projection);
}

void Camera::HandleEvent(GLFWwindow* windowPtr, const float& fDeltaTime)
{
	float fCurrentCameraSpeed = m_fCameraSpeed * fDeltaTime;
	if (glfwGetKey(windowPtr, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_cameraPosition += fCurrentCameraSpeed * m_cameraFront;
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_cameraPosition -= fCurrentCameraSpeed * m_cameraFront;
	}
		
	if (glfwGetKey(windowPtr, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_cameraPosition -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * fCurrentCameraSpeed;
	}
	if (glfwGetKey(windowPtr, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_cameraPosition += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * fCurrentCameraSpeed;
	}
}

void Camera::MouseScrollEvent(GLFWwindow* windowPtr, double dXoffset, double dYoffset)
{
	const float fMinFOV = 1.0f;
	const float fMaxFOV = 45.0f;
	m_fFieldOfView -= static_cast<float>(dYoffset);
	if (m_fFieldOfView < fMinFOV)
	{
		m_fFieldOfView = fMinFOV;
	}
	if (m_fFieldOfView > fMaxFOV)
	{
		m_fFieldOfView = fMaxFOV;
	}
}

void Camera::MouseEvent(GLFWwindow* windowPtr, double dXoffset, double dYoffset)
{
	if (!m_fMouseMemoryData)
	{
		m_fCurrentX = dXoffset;
		m_fCurrentY= dYoffset;
		m_fMouseMemoryData = true;
	}

	float fXOffsetCamera = dXoffset - m_fCurrentX;
	float fYOffsetCamera = m_fCurrentY - dYoffset; // reversed since y-coordinates go from bottom to top
	m_fCurrentX = dXoffset;
	m_fCurrentY = dYoffset;

	fXOffsetCamera *= m_fSensitivity;
	fYOffsetCamera *= m_fSensitivity;

	m_fYaw += fXOffsetCamera;
	m_fPitch += fYOffsetCamera;

	const float fMaxPitch = 89.0f;
	const float fMinPitch = -89.0f;
	if (m_fPitch > fMaxPitch)
	{
		m_fPitch = fMaxPitch;
	}
	if (m_fPitch < fMinPitch)
	{
		m_fPitch = fMinPitch;
	}

	glm::vec3 cameraFront;
	cameraFront.x = cos(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));
	cameraFront.y = sin(glm::radians(m_fPitch));
	cameraFront.z = sin(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));
	m_cameraFront = glm::normalize(cameraFront);
}

void Camera::SetCameraPosition(glm::vec3& cameraPosition)
{
	m_cameraPosition = cameraPosition;
}

void Camera::SetCameraTarget(glm::vec3& cameraTarget)
{
	m_cameraTarget = cameraTarget;
}

void Camera::SetCameraDirection(glm::vec3& cameraDirection)
{
	m_cameraDirection = cameraDirection;
}

void Camera::SetCameraFront(glm::vec3& cameraFront)
{
	m_cameraFront = cameraFront;
}

void Camera::SetCameraUp(glm::vec3& cameraUp)
{
	m_cameraUp = cameraUp;
}

void Camera::SetCameraSpeed(float& fCameraSpeed)
{
	m_fCameraSpeed = fCameraSpeed;
}

const glm::vec3& Camera::GetCameraPosition()
{
	return m_cameraPosition;
}

const glm::vec3& Camera::GetCameraTarget()
{
	return m_cameraTarget;
}

const glm::vec3& Camera::GetCameraDirection()
{
	return m_cameraDirection;
}

const glm::vec3& Camera::GetCameraFront()
{
	return m_cameraFront;
}

const glm::vec3& Camera::GetCameraUp()
{
	return m_cameraUp;
}

const glm::mat4& Camera::GetGlobalView()
{
	return m_view;
}

const float& Camera::GetCameraSpeed()
{
	return m_fCameraSpeed;
}