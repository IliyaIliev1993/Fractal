#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "glad.h"
#include "GLFW/includes/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Texture2D
{

private:

    /*OpenGL Data*/
    unsigned int VBO_Texture2D = 0;
    unsigned int VAO_Texture2D = 0;
    unsigned int EBO_Texture2D = 0;

    std::vector<float> m_vecVertexPoints;
    std::vector<unsigned int> m_vecIndexPoints;

    unsigned int m_Texture2D;
    int m_nWidth;
    int m_nHeight;
    int m_nNumberOfChannels;
    std::string m_sPath;

public:

    bool LoadFromFile(std::string sPathToFile);
    void BindTexture();
    void UnbindTexture();
    void Destroy();
    void Draw(glm::mat4& model, Shader& shaderTexture);
    inline unsigned int GetTexture() { return m_Texture2D; }
    inline int GetWidth() { return m_nWidth; }
    inline int GetHeight() { return m_nHeight; }
    inline int GetNumberOfChannels() { return m_nNumberOfChannels; }

};