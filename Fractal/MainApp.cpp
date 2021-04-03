#include "MainApp.h"

void MouseScrollEvent(GLFWwindow* windowPtr, double dXoffset, double dYoffset);
void MouseEvent(GLFWwindow* windowPtr, double dXoffset, double dYoffset);

MainApp::MainApp():m_rend(new Renderer),
				   m_camera(new Camera)
{

}

MainApp& MainApp::GetInstance()
{
	static MainApp mainAppInstance;
	return mainAppInstance;
}

bool MainApp::Init()
{
	const std::string strWindowTitle = "Fractal";

	if (!m_rend->Init(m_unScreenWidth, m_unScreenHeight, strWindowTitle))
	{
		std::cout << "MainApp::Init() - Failed to initialize Renderer !" << std::endl;
	}

	if (!m_camera->Init(m_unScreenWidth, m_unScreenHeight))
	{
		std::cout << "MainApp::Init() - Failed to initialize Camera !" << std::endl;
	}

	glfwSetScrollCallback(m_rend->GetWindowPtr(), MouseScrollEvent);
	glfwSetCursorPosCallback(m_rend->GetWindowPtr(), MouseEvent);
	glfwSetInputMode(m_rend->GetWindowPtr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	m_ShaderSphere.Create("Data/Shaders/vertex_shader_sphere.txt", "Data/Shaders/fragment_shader_sphere.txt");
	m_sphere.Init(m_fMainMotherSpereRadius, 
			      m_unLongitudeSlices, 
			      m_unLongitudeSlices);

	return true;
}

void MainApp::DrawMotherSphere(float& fXMother,
								float& fYMother,
								float& fZMother,
								float& fMotherRadius,
								float& fMotherScaleFactor,
								unsigned int& unLevel,
								Shader& shader)
{
	/*Mother Main Shpere*/
	glm::mat4 modelMainMotherSphere = glm::mat4(1.0f);
	/*Rotate the main mother sphere by 90 degrees on X axis to make the childs "stick" to the equator*/
	modelMainMotherSphere = glm::translate(modelMainMotherSphere, glm::vec3(fXMother, fYMother, fZMother));
	modelMainMotherSphere = glm::scale(modelMainMotherSphere, glm::vec3(fMotherScaleFactor, fMotherScaleFactor, fMotherScaleFactor));
	modelMainMotherSphere = glm::rotate(modelMainMotherSphere, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	m_sphere.SetModelMatrix(modelMainMotherSphere);
	m_sphere.Draw(shader);

	const int nSpheresAroundMother = 6;
	const int nSpheresInTopOfMother = 3;

	if (unLevel <= 1)
	{
		return;
	}

	/*Side Childs*/
	for (int i = 1; i <= nSpheresAroundMother; i++)
	{
		float fXMotherChild = fXMother;
		float fYMotherChild = fYMother;
		float fZMotherChild = fZMother;
		float fMainMotherSphereRadius = fMotherRadius / 3.0f;
		float fCurrentScaleFactor = fMotherScaleFactor / 3.0f;
		const float fAngleAroudMother = 60.0f;
		const float fDistanceToTranslate = (fMotherRadius + fMainMotherSphereRadius);
		const float fCurrentAngle = fAngleAroudMother * static_cast<float>(i);
		const float fRotateByOwnAxisY = 90.0f + (180.0f - fCurrentAngle);
		const float fRotateBYOwnAxisX = 0.0f;
		const float fTHETA = glm::radians(fCurrentAngle); /*Theta is the angle that is from 0 to 360 LONGITUDE*/
		const float fPHI = glm::radians(fRotateBYOwnAxisX); /*Theta is the angle that is from 90 to -90 LATITUDE*/
		float fXChild = fDistanceToTranslate * cos(fPHI) * cos(fTHETA);
		float fYChild = fDistanceToTranslate * sinf(fPHI);
		float fZChild = fDistanceToTranslate * cos(fPHI) * sin(fTHETA);

		glm::mat4 modelChilds = glm::mat4(1.0f);
		modelChilds = glm::translate(modelChilds, glm::vec3(fXChild, fYChild, fZChild));
		modelChilds = glm::translate(modelChilds, glm::vec3(fXMotherChild, fYMotherChild, fZMotherChild));
		modelChilds = glm::scale(modelChilds, glm::vec3(fCurrentScaleFactor, fCurrentScaleFactor, fCurrentScaleFactor));
		modelChilds = glm::rotate(modelChilds, glm::radians(fRotateByOwnAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
		modelChilds = glm::rotate(modelChilds, glm::radians(fRotateBYOwnAxisX), glm::vec3(1.0f, 0.0f, 0.0f));
		m_sphere.SetModelMatrix(modelChilds);
		m_sphere.Draw(shader);
		if (unLevel >= 3)
		{
			DrawSideSpheresLevel1(fXChild, fYChild, fZChild, fMainMotherSphereRadius, fCurrentScaleFactor, unLevel, shader);
			DrawTopSpheresLevel1(fXChild, fYChild, fZChild, fMainMotherSphereRadius, fCurrentScaleFactor, unLevel, shader);
		}

	}

	/*Top Childs*/
	for (int i = 1; i <= nSpheresInTopOfMother; i++)
	{
		float fXMotherChild = fXMother;
		float fYMotherChild = fYMother;
		float fZMotherChild = fZMother;
		float fMainMotherSphereRadius = fMotherRadius / 3.0f;
		float fCurrentScaleFactor = fMotherScaleFactor / 3.0f;
		const float fAngleAroudMother = 120.0f;
		const float fDistanceToTranslate = (fMotherRadius + fMainMotherSphereRadius);
		const float fCurrentAngle = fAngleAroudMother * static_cast<float>(i);
		const float fRotateByOwnAxisY = 90.0f + (180.0f - fCurrentAngle);
		const float fRotateBYOwnAxisX = 60.0f;
		const float fTHETA = glm::radians(fCurrentAngle); /*Theta is the angle that is from 0 to 360 LONGITUDE*/
		const float fPHI = glm::radians(fRotateBYOwnAxisX); /*Theta is the angle that is from 90 to -90 LATITUDE*/
		float fXChild = fDistanceToTranslate * cos(fPHI) * cos(fTHETA);
		float fYChild = fDistanceToTranslate * sinf(fPHI);
		float fZChild = fDistanceToTranslate * cos(fPHI) * sin(fTHETA);

		glm::mat4 modelChilds = glm::mat4(1.0f);
		modelChilds = glm::translate(modelChilds, glm::vec3(fXChild, fYChild, fZChild));
		modelChilds = glm::translate(modelChilds, glm::vec3(fXMotherChild, fYMotherChild, fZMotherChild));
		modelChilds = glm::scale(modelChilds, glm::vec3(fCurrentScaleFactor, fCurrentScaleFactor, fCurrentScaleFactor));
		modelChilds = glm::rotate(modelChilds, glm::radians(fRotateByOwnAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
		modelChilds = glm::rotate(modelChilds, glm::radians(fRotateBYOwnAxisX), glm::vec3(1.0f, 0.0f, 0.0f));
		m_sphere.SetModelMatrix(modelChilds);
		m_sphere.Draw(shader);
		if (unLevel >= 3)
		{
			DrawSideSpheresLevel1(fXChild, fYChild, fZChild, fMainMotherSphereRadius, fCurrentScaleFactor, unLevel, shader);
			DrawTopSpheresLevel1(fXChild, fYChild, fZChild, fMainMotherSphereRadius, fCurrentScaleFactor, unLevel, shader);
		}
	}


}

void MainApp::DrawSideSpheresLevel1(float& fXMother,
							  float& fYMother,
						      float& fZMother,
							  float& fMotherRadius,
							  float& fMotherScaleFactor,
							  unsigned int& unLevel,
							  Shader& shader)
{
	const int nSpheresAroundMother = 6;
	const int nSpheresInTopOfMother = 3;

	/*Side Childs*/
	for (int i = 1; i <= nSpheresAroundMother; i++)
	{
		float fXMotherChild = fXMother;
		float fYMotherChild = fYMother;
		float fZMotherChild = fZMother;
		float fMainMotherSphereRadius = fMotherRadius / 3.0f;
		float fCurrentScaleFactor = fMotherScaleFactor / 3.0f;
		const float fAngleAroudMother = 60.0f;
		const float fDistanceToTranslate = (fMotherRadius + fMainMotherSphereRadius);
		const float fCurrentAngle = fAngleAroudMother * static_cast<float>(i);
		const float fRotateByOwnAxisY = 90.0f + (180.0f - fCurrentAngle);
		const float fRotateBYOwnAxisX = 0.0f;
		const float fTHETA = glm::radians(fCurrentAngle); /*Theta is the angle that is from 0 to 360 LONGITUDE*/
		const float fPHI = glm::radians(fRotateBYOwnAxisX); /*Theta is the angle that is from 90 to -90 LATITUDE*/
		float fXChild = fDistanceToTranslate * cos(fPHI) * cos(fTHETA);
		float fYChild = fDistanceToTranslate * sinf(fPHI);
		float fZChild = fDistanceToTranslate * cos(fPHI) * sin(fTHETA);

		glm::mat4 modelChilds = glm::mat4(1.0f);
		modelChilds = glm::translate(modelChilds, glm::vec3(fXChild, fYChild, fZChild));
		modelChilds = glm::translate(modelChilds, glm::vec3(fXMotherChild, fYMotherChild, fZMotherChild));
		modelChilds = glm::scale(modelChilds, glm::vec3(fCurrentScaleFactor, fCurrentScaleFactor, fCurrentScaleFactor));
		modelChilds = glm::rotate(modelChilds, glm::radians(fRotateByOwnAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
		modelChilds = glm::rotate(modelChilds, glm::radians(fRotateBYOwnAxisX), glm::vec3(1.0f, 0.0f, 0.0f));
		m_sphere.SetModelMatrix(modelChilds);
		m_sphere.Draw(shader);
		if (unLevel == 4)
		{
			DrawSideSpheresLevel2(fXChild, fYChild, fZChild, fMainMotherSphereRadius, fCurrentScaleFactor, unLevel, shader);
			DrawTopSpheresLevel2(fXChild, fYChild, fZChild, fMainMotherSphereRadius, fCurrentScaleFactor, unLevel, shader);
		}
	}

}

void MainApp::DrawTopSpheresLevel1(float& fXMother,
	float& fYMother,
	float& fZMother,
	float& fMotherRadius,
	float& fMotherScaleFactor,
	unsigned int& unLevel,
	Shader& shader)
{
	const int nSpheresAroundMother = 6;
	const int nSpheresInTopOfMother = 3;
	unsigned int unLevelChild = unLevel;
	/*Top Childs*/
	for (int i = 1; i <= nSpheresInTopOfMother; i++)
	{
		float fXMotherChild = fXMother;
		float fYMotherChild = fYMother;
		float fZMotherChild = fZMother;
		float fMainMotherSphereRadius = fMotherRadius / 3.0f;
		float fCurrentScaleFactor = fMotherScaleFactor / 3.0f;
		const float fAngleAroudMother = 120.0f;
		const float fDistanceToTranslate = (fMotherRadius + fMainMotherSphereRadius);
		const float fCurrentAngle = fAngleAroudMother * static_cast<float>(i);
		const float fRotateByOwnAxisY = 90.0f + (180.0f - fCurrentAngle);
		const float fRotateBYOwnAxisX = 60.0f;
		const float fTHETA = glm::radians(fCurrentAngle); /*Theta is the angle that is from 0 to 360 LONGITUDE*/
		const float fPHI = glm::radians(fRotateBYOwnAxisX); /*Theta is the angle that is from 90 to -90 LATITUDE*/
	    float fXChild = fDistanceToTranslate * cos(fPHI) * cos(fTHETA);
		float fYChild = fDistanceToTranslate * sinf(fPHI);
		float fZChild = fDistanceToTranslate * cos(fPHI) * sin(fTHETA);

		glm::mat4 modelChilds = glm::mat4(1.0f);
		modelChilds = glm::translate(modelChilds, glm::vec3(fXChild, fYChild, fZChild));
		modelChilds = glm::translate(modelChilds, glm::vec3(fXMotherChild, fYMotherChild, fZMotherChild));
		modelChilds = glm::scale(modelChilds, glm::vec3(fCurrentScaleFactor, fCurrentScaleFactor, fCurrentScaleFactor));
		modelChilds = glm::rotate(modelChilds, glm::radians(fRotateByOwnAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
		modelChilds = glm::rotate(modelChilds, glm::radians(fRotateBYOwnAxisX), glm::vec3(1.0f, 0.0f, 0.0f));
		m_sphere.SetModelMatrix(modelChilds);
		m_sphere.Draw(shader);
	}
}

void MainApp::DrawSideSpheresLevel2(float& fXMother,
	float& fYMother,
	float& fZMother,
	float& fMotherRadius,
	float& fMotherScaleFactor,
	unsigned int& unLevel,
	Shader& shader)
{
	const int nSpheresAroundMother = 6;
	const int nSpheresInTopOfMother = 3;

	/*Side Childs*/
	for (int i = 1; i <= nSpheresAroundMother; i++)
	{
		float fXMotherChild = fXMother;
		float fYMotherChild = fYMother;
		float fZMotherChild = fZMother;
		float fMainMotherSphereRadius = fMotherRadius / 3.0f;
		float fCurrentScaleFactor = fMotherScaleFactor / 3.0f;
		const float fAngleAroudMother = 60.0f;
		const float fDistanceToTranslate = (fMotherRadius + fMainMotherSphereRadius);
		const float fCurrentAngle = fAngleAroudMother * static_cast<float>(i);
		const float fRotateByOwnAxisY = 90.0f + (180.0f - fCurrentAngle);
		const float fRotateBYOwnAxisX = 0.0f;
		const float fTHETA = glm::radians(fCurrentAngle); /*Theta is the angle that is from 0 to 360 LONGITUDE*/
		const float fPHI = glm::radians(fRotateBYOwnAxisX); /*Theta is the angle that is from 90 to -90 LATITUDE*/
		float fXChild = fXMotherChild + fDistanceToTranslate * cos(fPHI) * cos(fTHETA);
		float fYChild = fYMotherChild + fDistanceToTranslate * sinf(fPHI);
		float fZChild = fZMotherChild + fDistanceToTranslate * cos(fPHI) * sin(fTHETA);

		glm::mat4 modelChilds = glm::mat4(1.0f);
		modelChilds = glm::translate(modelChilds, glm::vec3(fXChild, fYChild, fZChild));
		modelChilds = glm::translate(modelChilds, glm::vec3(fXMotherChild, fYMotherChild, fZMotherChild));
		modelChilds = glm::scale(modelChilds, glm::vec3(fCurrentScaleFactor, fCurrentScaleFactor, fCurrentScaleFactor));
		modelChilds = glm::rotate(modelChilds, glm::radians(fRotateByOwnAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
		modelChilds = glm::rotate(modelChilds, glm::radians(fRotateBYOwnAxisX), glm::vec3(1.0f, 0.0f, 0.0f));
		m_sphere.SetModelMatrix(modelChilds);
		m_sphere.Draw(shader);
	}

}

void MainApp::DrawTopSpheresLevel2(float& fXMother,
	float& fYMother,
	float& fZMother,
	float& fMotherRadius,
	float& fMotherScaleFactor,
	unsigned int& unLevel,
	Shader& shader)
{
	const int nSpheresAroundMother = 6;
	const int nSpheresInTopOfMother = 3;
	unsigned int unLevelChild = unLevel;
	/*Top Childs*/
	for (int i = 1; i <= nSpheresInTopOfMother; i++)
	{
		float fXMotherChild = fXMother;
		float fYMotherChild = fYMother;
		float fZMotherChild = fZMother;
		float fMainMotherSphereRadius = fMotherRadius / 3.0f;
		float fCurrentScaleFactor = fMotherScaleFactor / 3.0f;
		const float fAngleAroudMother = 120.0f;
		const float fDistanceToTranslate = (fMotherRadius + fMainMotherSphereRadius);
		const float fCurrentAngle = fAngleAroudMother * static_cast<float>(i);
		const float fRotateByOwnAxisY = 90.0f + (180.0f - fCurrentAngle);
		const float fRotateBYOwnAxisX = 60.0f;
		const float fTHETA = glm::radians(fCurrentAngle); /*Theta is the angle that is from 0 to 360 LONGITUDE*/
		const float fPHI = glm::radians(fRotateBYOwnAxisX); /*Theta is the angle that is from 90 to -90 LATITUDE*/
		float fXChild = fXMotherChild + fDistanceToTranslate * cos(fPHI) * cos(fTHETA);
		float fYChild = fYMotherChild + fDistanceToTranslate * sinf(fPHI);
		float fZChild = fZMotherChild + fDistanceToTranslate * cos(fPHI) * sin(fTHETA);

		glm::mat4 modelChilds = glm::mat4(1.0f);
		modelChilds = glm::translate(modelChilds, glm::vec3(fXChild, fYChild, fZChild));
		modelChilds = glm::translate(modelChilds, glm::vec3(fXMotherChild, fYMotherChild, fZMotherChild));
		modelChilds = glm::scale(modelChilds, glm::vec3(fCurrentScaleFactor, fCurrentScaleFactor, fCurrentScaleFactor));
		modelChilds = glm::rotate(modelChilds, glm::radians(fRotateByOwnAxisY), glm::vec3(0.0f, 1.0f, 0.0f));
		modelChilds = glm::rotate(modelChilds, glm::radians(fRotateBYOwnAxisX), glm::vec3(1.0f, 0.0f, 0.0f));
		m_sphere.SetModelMatrix(modelChilds);
		m_sphere.Draw(shader);
	}
}

void MainApp::Run()
{
	while (!glfwWindowShouldClose(m_rend->GetWindowPtr()))
	{
		m_ShaderSphere.use();
		HandleEvent(m_rend->GetWindowPtr());
		m_camera->Process(m_ShaderSphere);
		m_rend->Process(m_ShaderSphere);
		m_rend->ClearGlobalColor();
		m_rend->DrawPolygonLineMode();

		float fXMother = 0.0f;
		float fYMother = 0.0f;
		float fZMother = 0.0f;
		float fMainMotherSphereRadius = m_fMainMotherSpereRadius;
	    float fCurrentScaleFactor = 2 * fMainMotherSphereRadius;
	
		DrawMotherSphere(fXMother,
			fYMother,
			fZMother,
			fMainMotherSphereRadius,
			fCurrentScaleFactor,
			m_unMaxLevels,
			m_ShaderSphere);

		m_rend->SwapBuffers();
		glfwPollEvents();
	}
}

void MainApp::HandleEvent(GLFWwindow* windowPtr)
{
	if (glfwGetKey(m_rend->GetWindowPtr(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_rend->GetWindowPtr(), true);
	}

	if (glfwGetKey(m_rend->GetWindowPtr(), GLFW_KEY_LEFT) == GLFW_PRESS && !m_bPressedLeft)
	{
		m_bPressedLeft = true;
		m_unMaxLevels--;
		if (m_unMaxLevels <= 1)
		{
			m_unMaxLevels = 1;
		}

		std::cout << m_unMaxLevels << std::endl;
	}
	if (glfwGetKey(m_rend->GetWindowPtr(), GLFW_KEY_LEFT) == GLFW_RELEASE && m_bPressedLeft)
	{
		m_bPressedLeft = false;
	}

	if (glfwGetKey(m_rend->GetWindowPtr(), GLFW_KEY_RIGHT) == GLFW_PRESS && !m_bPressedRight)
	{
		m_bPressedRight = true;
		m_unMaxLevels++;
		if (m_unMaxLevels >= 4)
		{
			m_unMaxLevels = 4;
		}

		std::cout << m_unMaxLevels << std::endl;
	}

	if (glfwGetKey(m_rend->GetWindowPtr(), GLFW_KEY_RIGHT) == GLFW_RELEASE && m_bPressedRight)
	{
		m_bPressedRight = false;
	}

	m_camera->HandleEvent(windowPtr, m_rend->GetDeltaTime());
}

void MouseScrollEvent(GLFWwindow* windowPtr, double dXoffset, double dYoffset)
{
	MainApp::GetInstance().m_camera->MouseScrollEvent(windowPtr, dXoffset, dYoffset);
}

void MouseEvent(GLFWwindow* windowPtr, double dXoffset, double dYoffset)
{
	MainApp::GetInstance().m_camera->MouseEvent(windowPtr, dXoffset, dYoffset);
}

void MainApp::DeInit()
{
	m_rend->DeInit();
	m_sphere.DeInit();
}