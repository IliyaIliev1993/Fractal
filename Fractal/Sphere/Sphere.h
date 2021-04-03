#pragma once
#include <iostream>
#include <vector>
#include <glad.h>
#include <GLFW/includes/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Sphere
{

private:

	/*OpenGL Data*/
	unsigned int VBO_Sphere = 0;
	unsigned int VAO_Sphere = 0;
	unsigned int EBO_Sphere = 0;

	/*Radius of Sphere*/
	float m_fRadius = 0.0f;
	/*Longitude Slices*/
	unsigned int m_unLongitudeSlices = 0;
	/*Latitude Slices*/
	unsigned int m_unLatitudeSlices = 0;

	//TODO
	std::vector<float> vecVertexPoints;
	std::vector<unsigned int> vecIndexPoints;

	/*Model Matrix*/
	glm::mat4 m_model;
public:
	
	Sphere();
	/*Initialization to all the needed data*/
	bool Init(float fRadius = 0.5f,
		unsigned int unLongitudeSlices = 20,
		unsigned int unLatitudeSlices = 20);

	/*Deinitialize all members*/
	void DeInit();

	/*Function that calculates Vertecies and Indecies
	for a given LongSlices, LatSlices and Radius*/
	void CalculateSphere();

	/*Passing and binding all the given calculated data to the GL Buffers*/
	void CreateBuffers();

	/*Draw the Sphere*/
	void Draw(Shader& shaderSphere);

	/*Setting matrix to the current model*/
	void SetModelMatrix(glm::mat4& model);

};