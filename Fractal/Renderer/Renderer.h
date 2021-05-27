#pragma once
#include <iostream>
#include <string>
#include <glad.h>
#include <GLFW/includes/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Texture2D.h"
class Renderer
{

private:

	/*Screen Resolution Data and Window properties*/
	unsigned int m_unScreenWidth = 0;
	unsigned int m_unScreenHeight = 0;
	std::string m_strWindowTitle = "N/A";

	/*Calculations Data*/
	float m_fDeltaTime = 0.0f;
	float m_fLastFrameTime = 0.0f;

	/*Window Ptr*/
	GLFWwindow* m_WindowPtr = nullptr;

public:

	Renderer();
	/*Initialize Renderer System*/
	bool Init(const unsigned int& unScreenWidth,
			  const unsigned int& unScreenHeight,
			  const std::string& strWindowTitle);
	/*Deinitialize Renderer System*/
	void DeInit();

	/*Function that clears the global background Color*/
	void ClearGlobalColor();
	/*Enable / Disable drawing Polygon Line Mode (used to debug)*/
	void EnableDrawPolygonLineMode();
	void DisableDrawPolygonLineMode();
	/*Swapping buffers*/
	void SwapBuffers();

	/*Function called in every cycle only to do some calculations*/
	void Process();
	
	/*Setters for all Renderer data*/
	void SetScreenWidth(const unsigned int& unScreenWidth);
	void SetScreenHeight(const unsigned int& unScreenHeight);
	void SetWindowTitle(const std::string& strWindowTitle);

	/*Getters for all Renderer data*/
	GLFWwindow* GetWindowPtr();
	const unsigned int& GetScreenWidth();
	const unsigned int& GetScreenHeight();
	const float& GetDeltaTime();
	const std::string& GetWindowTitle();

};
