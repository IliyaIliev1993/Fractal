#include "Renderer.h"

Renderer::Renderer()
{

}

bool Renderer::Init(const unsigned int& unScreenWidth,
					const unsigned int& unScreenHeight,
					const std::string& strWindowTitle)
{
	m_unScreenWidth = unScreenWidth;
	m_unScreenHeight = unScreenHeight;
	m_strWindowTitle = strWindowTitle;

	std::cout << "Renderer::Init() - Creating new Window with title : "<< strWindowTitle  << std::endl;
	std::cout << "Renderer::Init() - Setting resolution to: " << m_unScreenWidth << "x" << m_unScreenHeight << std::endl;
	if (m_unScreenWidth == 0 ||
		m_unScreenHeight == 0)
	{
		std::cout << "Renderer::Init() - Invalid options of Screen Resolution !" << std::endl;
		return false;
	}


	/*Initialize and configure GLFW*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/*Create a window with the screen resolution*/
	m_WindowPtr =  glfwCreateWindow(m_unScreenWidth, m_unScreenHeight, m_strWindowTitle.c_str(), NULL, NULL);
	if (m_WindowPtr == nullptr)
	{
		std::cout << "Renderer::Init() - Failed to create GLFWwindow !" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(m_WindowPtr);

	/*Loads all OPENGL functions pointers*/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Renderer::Init() - Failed to Initialize GLAD !" << std::endl;
		return false;
	}

	/*Configure global OPENGL state for depht testing*/
	glEnable(GL_DEPTH_TEST);
	
	std::cout << "Renderer::Init() - Initialization successful !" << std::endl;
	return true;
}

void Renderer::Process()
{
	float fCurrentTime = static_cast<float>(glfwGetTime());
	m_fDeltaTime = fCurrentTime - m_fLastFrameTime;
	m_fLastFrameTime = fCurrentTime;
}

void Renderer::ClearGlobalColor()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawPolygonLineMode()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::SwapBuffers()
{
	glfwSwapBuffers(m_WindowPtr);
}

void Renderer::DeInit()
{
	glfwDestroyWindow(m_WindowPtr);
	glfwTerminate();
	std::cout << "Renderer::DeInit() - Destroyed !" << std::endl;
}

GLFWwindow* Renderer::GetWindowPtr()
{
	return m_WindowPtr;
}

void Renderer::SetScreenWidth(const unsigned int& unScreenWidth)
{
	m_unScreenWidth = unScreenWidth;
}

void Renderer::SetScreenHeight(const unsigned int& unScreenHeight)
{
	m_unScreenHeight = unScreenHeight;
}

void Renderer::SetWindowTitle(const std::string& strWindowTitle)
{
	m_strWindowTitle = strWindowTitle;
}

const unsigned int& Renderer::GetScreenWidth()
{
	return m_unScreenWidth;
}

const unsigned int& Renderer::GetScreenHeight()
{
	return m_unScreenHeight;
}

const float& Renderer::GetDeltaTime()
{
	return m_fDeltaTime;
}

const std::string& Renderer::GetWindowTitle()
{
	return m_strWindowTitle;
}