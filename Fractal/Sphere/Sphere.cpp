#include "Sphere.h"

Sphere::Sphere()
{

}

bool Sphere::Init(float fRadius,
	unsigned int unLongitudeSlices,
	unsigned int unLatitudeSlices)
{
	if ((fRadius <= 0.0f) || 
		(unLongitudeSlices == 0) ||
		(unLatitudeSlices == 0))
	{
		std::cout << "Sphere::Init() - Cannot set negative values to Sphere !" << std::endl;
		return false;
	}

	m_fRadius = fRadius;
	m_unLongitudeSlices = unLongitudeSlices;
	m_unLatitudeSlices = unLatitudeSlices;

	m_model = glm::mat4(1.0f);

	CalculateSphere();
	CreateBuffers();

	return true;
}

void Sphere::DeInit()
{
	glDeleteVertexArrays(1, &VAO_Sphere);
	glDeleteBuffers(1, &VBO_Sphere);
	glDeleteBuffers(1, &EBO_Sphere);
}

void Sphere::CalculateSphere()
{
	std::cout << "Sphere::CalculateSphere() - Calculating ..." << std::endl;

	//const unsigned int unSizeOfVertexArray = m_unLatitudeSlices * m_unLongitudeSlices;
	//float* fVertexArrayPtr = new float[unSizeOfVertexArray];

	/*Define all the needed data to create a Sphere*/
	const float fPI = acosf(-1);
	/*Vertex Pos in 3D space*/
	float fX = 0.0f;
	float fY = 0.0f;
	float fZ = 0.0f;
	/*Data needed to calculate the needed indeces to draw 2 triangles in 1 sector of the Sphere*/
	unsigned int unPoint1 = 0;
	unsigned int unPoint2 = 0;
	/*Angles THETA and PHI needed to calculate from degrees to 3D points*/
	float fLongitudeAngleTHETA = 0.0f;
	float fLatitudeAnglePHI = 0.0f;

	/*Calculating the steps needed to decide where and how many 
	  vertecies are needed to draw the Sphere*/
	float fLongitudeSteps = 2 * fPI / m_unLongitudeSlices;
	float fLatitudeSteps = fPI / m_unLatitudeSlices;

	/*Beginning with the Latitude*/
	for (unsigned int i = 0; i <= m_unLatitudeSlices; ++i)
	{
		/*Starting from 90 degrees and going to -90 degrees*/
		fLatitudeAnglePHI = fPI / 2 - i * fLatitudeSteps;
		/*Calculating Z*/
		/* (r * sin(PHI)) */
		fZ = m_fRadius * sinf(fLatitudeAnglePHI); 

		/*Going to the Longitude*/
		for (unsigned int j = 0; j <= m_unLongitudeSlices; ++j)
		{
			/*Starting from 0 degrees and going to 360 degrees*/
			fLongitudeAngleTHETA = j * fLongitudeSteps;

			/*Calculating X*/
			/* (r * cos(PHI) * cos(THETA)) */
			fX = m_fRadius * cos(fLatitudeAnglePHI) * cos(fLongitudeAngleTHETA);
			/* (r * cos(PHI) * sin(THETA)) */
			fY = m_fRadius * cos(fLatitudeAnglePHI) * sin(fLongitudeAngleTHETA);

			vecVertexPoints.push_back(fX);
			vecVertexPoints.push_back(fY);
			vecVertexPoints.push_back(fZ);
		}
	}

	/*Calculating Indecies*/
	for (unsigned int i = 0; i < m_unLatitudeSlices; ++i)
	{
		unPoint1 = i * (m_unLongitudeSlices + 1);
		unPoint2 = unPoint1 + (m_unLongitudeSlices + 1);

		for (unsigned int j = 0; j < m_unLongitudeSlices; ++j, ++unPoint1, ++unPoint2)
		{
			if (i != 0)
			{
				vecIndexPoints.push_back(unPoint1);
				vecIndexPoints.push_back(unPoint2);
				vecIndexPoints.push_back(unPoint1 + 1);
			}

			if (i != (m_unLatitudeSlices - 1))
			{
				vecIndexPoints.push_back(unPoint1 + 1);
				vecIndexPoints.push_back(unPoint2);
				vecIndexPoints.push_back(unPoint2 + 1);
			}
		}
	}

}

void Sphere::CreateBuffers()
{
	glGenVertexArrays(1, &VAO_Sphere);
	glGenBuffers(1, &VBO_Sphere);
	glGenBuffers(1, &EBO_Sphere);

	glBindVertexArray(VAO_Sphere);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Sphere);
	glBufferData(GL_ARRAY_BUFFER, (unsigned int)vecVertexPoints.size() * sizeof(float), vecVertexPoints.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Sphere);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (unsigned int)vecIndexPoints.size() * sizeof(unsigned int), vecIndexPoints.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Sphere::Draw(Shader& shaderSphere)
{
	// activate shader
	shaderSphere.use();

	shaderSphere.setMat4("model", m_model);

	glBindVertexArray(VAO_Sphere);
	glDrawElements(GL_TRIANGLES, vecIndexPoints.size(), GL_UNSIGNED_INT, 0);
}

void Sphere::SetModelMatrix(glm::mat4& model)
{
	m_model = glm::mat4(1.0f);
	m_model = model;
}