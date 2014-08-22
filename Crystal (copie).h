#ifndef DEF_CRYSTAL
#define DEF_CRYSTAL

// Includes GLM

#include "Include/glm/glm.hpp"
#include "Include/glm/gtx/transform.hpp"
#include "Include/glm/gtc/type_ptr.hpp"


#include "GraphicObject.h"


#include <string>



class Crystal: public GraphicObject
{
    public:
      Crystal(float x, float y, float z, float size, std::string const vertexShader, std::string const fragmentShader);
      virtual ~Crystal();
      void draw(glm::mat4 &projection, glm::mat4 &modelview);
      virtual void load();

    protected:



};

#endif
