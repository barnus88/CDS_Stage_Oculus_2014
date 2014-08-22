#ifndef DEF_CRYSTAL
#define DEF_CRYSTAL


// Includes OpenGL

#ifdef WIN32
#include <GL/glew.h>

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif


// Includes GLM

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Includes

#include "Shader.h"
#include "Star.h"
#include <vector>


// Classe Cube

class Crystal
{
    public:
    Crystal(float taille, std::string const vertexShader, std::string const fragmentShader);
    Crystal(float taille, std::vector<Star> lStar, std::string const vertexShader, std::string const fragmentShader);
    ~Crystal();

    void afficher(glm::mat4 &projection, glm::mat4 &modelview);
    void afficher(glm::mat4 &projection, glm::mat4 &modelview, int nb);
    void GroundColorMix(double* color, double x, double min, double max);

    protected:

    Shader m_shader;
    float *m_vertices;
    float *m_couleurs;
};

#endif
