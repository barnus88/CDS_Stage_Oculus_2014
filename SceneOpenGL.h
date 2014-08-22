#ifndef DEF_SCENEOPENGL
#define DEF_SCENEOPENGL


// Includes

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


// Autres includes

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include "Shader.h"
#include "Crystal.h"
#include "Input.h"
#include "Camera.h"
#include "Parser.h"

#include "Oculus.h"

// Classe

class SceneOpenGL
{
    public:

    SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre, vector<Star> l);
    ~SceneOpenGL();

    bool initialiserFenetre();
    void initEchelle();
    bool initGL();
    void bouclePrincipale();
    double maximum();
    double minimum();


    private:

    std::string m_titreFenetre;
    int m_largeurFenetre;
    int m_hauteurFenetre;

    SDL_Window* m_fenetre;
    SDL_GLContext m_contexteOpenGL;
	Input m_input;
	vector<Star> m_lStar;
};

#endif

