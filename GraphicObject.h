#ifndef GRAPHICOBJECT_H
#define GRAPHICOBJECT_H

#include "Include/glm/glm.hpp"
#include <vector>
#include <string>
#include "Shader.h"

//GL Macro
#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

class GraphicObject
{
public:
    GraphicObject(float x, float y, float z, float size, std::string vertexShader, std::string fragmentShader);
    virtual ~GraphicObject();
    virtual void draw(glm::mat4 &projection, glm::mat4 &modelview);

    int nbVerticesBytes();
    int nbColorsBytes();


    void move(glm::vec3 const & value);

    void updateVBO(void* data, int bytesSize, int offset);
    virtual void print();

protected:
    glm::vec3 position_;
    glm::vec3 rotation_;
    int scale_;
    std::vector<float> vertices_;
    std::vector<float> colors_;
    Shader* shader_;
    GLuint VBOId_;
    GLuint VAOId_;


};

#endif // GRAPHICOBJECT_H

