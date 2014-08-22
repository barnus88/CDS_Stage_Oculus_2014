#ifndef PLANE_H
#define PLANE_H




// Includes GLM

#include "Include/glm/glm.hpp"
#include "Include/glm/gtx/transform.hpp"
#include "Include/glm/gtc/type_ptr.hpp"

//
// Includes


#include "GraphicObject.h"
#include "Texture.h"





class Plane: public GraphicObject
{
public:
    Plane(float x, float y, float z, float width, float height, float repeatWidth, float repeatHeight, std::string const vertexShader, std::string const fragShader, std::string const texture);
    ~Plane();
    void draw(glm::mat4 &projection, glm::mat4 &modelview);
    virtual void load();

    int nbTextureBytes();

protected:
    std::vector<float> textureCoord_;


    Texture* texture_;
};

#endif // PLANE_H
