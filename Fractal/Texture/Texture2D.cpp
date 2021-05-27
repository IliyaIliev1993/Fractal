#include "Texture2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool Texture2D::LoadFromFile(std::string sPathToFile)
{
    /* TOP LEFT->  *---------------------------------* <-TOP RIGHT
                   |                                 |
                   |                                 |
                   |                                 |
                   |                                 |
    BOTTOM LEFT -> *---------------------------------* <-BOTTOM RIGHT */

    m_vecVertexPoints =
    {
        /* Vertex X, Y, Z --- Texture U, V */
        -0.5f, 0.5f, 0.0f,      0.0f, 1.0f, 
         0.5f, 0.5f, 0.0f,      1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,     1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f
    };

    m_vecIndexPoints =
    {
        0, 1, 3, /* Drawing First Triangle */
        1, 2, 3  /* Drawing Second Triangle */
    };

    glGenVertexArrays(1, &VAO_Texture2D);
    glGenBuffers(1, &VBO_Texture2D);
    glGenBuffers(1, &EBO_Texture2D);

    glBindVertexArray(VAO_Texture2D);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Texture2D);
    glBufferData(GL_ARRAY_BUFFER, (unsigned int)m_vecVertexPoints.size() * sizeof(float), m_vecVertexPoints.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_Texture2D);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (unsigned int)m_vecIndexPoints.size() * sizeof(unsigned int), m_vecIndexPoints.data(), GL_STATIC_DRAW);

    /*Stride of Vertex Attributes*/
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /*Stride of Texture Attributes*/
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    /*Texture Generating and Loading from file*/
    glGenTextures(1, &m_Texture2D);
    glBindTexture(GL_TEXTURE_2D, m_Texture2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(sPathToFile.c_str(), &m_nWidth, &m_nHeight, &m_nNumberOfChannels, 4);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_nWidth, m_nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        std::cout << "Loading Texture: " << sPathToFile.c_str() << " ..." << std::endl;
    }
    else
    {
        std::cout << "Failed to load texture: " << sPathToFile << std::endl;
        return false;
    }

    m_sPath = sPathToFile;
    stbi_image_free(data);
	return true;
}

void Texture2D::BindTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Texture2D);
}

void Texture2D::Draw(glm::mat4& model, Shader& shaderTexture)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Texture2D);

    shaderTexture.use();
    shaderTexture.setMat4("model", model);

    glBindVertexArray(VAO_Texture2D);
    glDrawElements(GL_TRIANGLES, m_vecIndexPoints.size(), GL_UNSIGNED_INT, 0);
}

void Texture2D::UnbindTexture()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Destroy()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteVertexArrays(1, &VAO_Texture2D);
    glDeleteBuffers(1, &VBO_Texture2D);
    glDeleteBuffers(1, &EBO_Texture2D);
    std::cout << "Texture: " << m_sPath << " Destroyed ..." << std::endl;
}