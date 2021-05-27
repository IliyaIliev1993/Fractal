#pragma once
#include <iostream>
#include <memory>
#include <functional>
#include "Renderer/Renderer.h"
#include "Camera/Camera.h"
#include "Sphere/Sphere.h"

class MainApp
{

private:
	MainApp();
	~MainApp() = default;

	/*Window Resolution*/
	const unsigned int m_unScreenWidth = 1920;
	const unsigned int m_unScreenHeight = 1080;

	/*Shaders*/
	Shader m_ShaderSphere;

	/*Sphere and details*/
	Sphere m_sphere;
	float m_fMainMotherSpereRadius = 0.5f;
	unsigned int m_unLongitudeSlices = 20;
	unsigned int m_unLatitudeSlices = 20;
	unsigned int m_unMaxLevels = 1;

	/*MainFunction, it will be called only if we have some process input*/
	bool m_bPressedLeft = false;
	bool m_bPressedRight = false;
	void HandleEvent(GLFWwindow* windowPtr);
	
	/*DrawMotherSphere*/
	void DrawMotherSphere(float& fXMother,
							float& fYMother,
							float& fZMother,
							float& fMotherRadius,
							float& fMotherScaleFactor,
							unsigned int& unLevel,
							Shader& shader);
	/*DrawSideSpheres Level1*/
	void DrawSideSpheresLevel1(float& fXMother,
						 float& fYMother,
						 float& fZMother,
						 float& fMotherRadius,
					     float& fMotherScaleFactor,
						 unsigned int& unLevel,
						 Shader& shader);
	/*DrawTopSpheres Level1*/
	void DrawTopSpheresLevel1(float& fXMother,
						float& fYMother,
						float& fZMother,
						float& fMotherRadius,
						float& fMotherScaleFactor,
						unsigned int& unLevel,
						Shader& shader);

public:

	/*Creating instance from Renderer*/
	std::unique_ptr<Renderer>m_rend;
	/*Creating instance from Camera*/
	std::unique_ptr<Camera>m_camera;

	/**Returns the MainApp Object */
	static MainApp& GetInstance();

	/** Delete copy-constructor, move-constructor and assignment operators */
	MainApp(MainApp const&) = delete;
	void operator = (MainApp const&) = delete;
	MainApp(MainApp&&) = delete;
	void operator = (MainApp&&) = delete;

	/*Initialize Main App and calls all the Init data*/
	bool Init();
	/*Run the current application*/
	void Run();
	/*Deinitialize Main App and calls all the Deinit data*/
	void DeInit();
	

};