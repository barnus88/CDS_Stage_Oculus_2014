#include "GraphicObject.h"

#include <cstring>


GraphicObject::GraphicObject(float x, float y, float z, float size, std::string vertexShader, std::string fragmentShader):
    position_ {x, y, z},
    rotation_ {0, 0, 0},
    scale_ {1},
    shader_ {nullptr},
    VBOId_ {0},
    VAOId_ {0}
{
    shader_ = new Shader(vertexShader, fragmentShader);
}

GraphicObject::~GraphicObject()
{
    delete shader_;

    if(glIsBuffer(VBOId_)  == GL_TRUE)
    {
        glDeleteBuffers(1, &VBOId_);
    }

    if(glIsVertexArray(VAOId_) == GL_TRUE)
    {
      glDeleteVertexArrays(1, &VAOId_);
    }
}

int GraphicObject::nbVerticesBytes()
{
    return vertices_.size() * sizeof(float);
}

int GraphicObject::nbColorsBytes()
{
     return colors_.size() * sizeof(float);
}




void GraphicObject::move(glm::vec3 const & value)
{
    position_ += value;
}


void GraphicObject::updateVBO(void* data, int bytesSize, int offset)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBOId_);

        void* VBOAdress = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

        if(VBOAdress == nullptr)
        {
            std::cerr << "Cannot get the VBO address" << std::endl;
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            return;
        }
        memcpy((char*) VBOAdress + offset, data, bytesSize);
        glUnmapBuffer(GL_ARRAY_BUFFER);
        VBOAdress = 0;

        glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GraphicObject::print()
{

}

void GraphicObject::draw(glm::mat4 &projection, glm::mat4 &modelview)
{

}
