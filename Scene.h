#ifndef DEF_SCENEOPENGL
#define DEF_SCENEOPENGL

// Includes OpenGL

#include <GL/glew.h>


#define GL3_PROTOTYPES 1
#include "Include/GL3/gl3.h"



// Includes GLM

#include "Include/glm/glm.hpp"
#include "Include/glm/gtx/transform.hpp"
#include "Include/glm/gtc/type_ptr.hpp"


// Includes

#include "Shader.h"
#include "SDL2/SDL.h"

#include <iostream>
#include <string>
#include <vector>
#include "Star.h"
#include "Crystal.h"




#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#include "Oculus.h"

class Input;
class Camera;
class GraphicObject;

class Scene
{

public:

    Scene(std::string windowTitle, int windowWidth, int windowHeight, bool oculusRender, bool fullscreen);
    ~Scene();

    bool initWindow();
    bool initGL();
    void mainLoop();
    void render();
    SDL_Window* getWindow() const;
    Camera* getCamera();



    int windowWidth() const;
    void setWindowWidth(int windowWidth);

    int windowHeight() const;
    void setWindowHeight(int windowHeight);



    void render(glm::mat4 & MV, glm::mat4 & proj);


    Oculus<Scene> *oculus() const;
    void setOculus(Oculus<Scene> *oculus);

    double maximum();
    double minimum();
    void initEchelle();
    void setupGObjects();

private:
    Oculus<Scene>* oculus_;
    std::string windowTitle_;
    int windowWidth_;
    int windowHeight_;
    SDL_Window* window_;
    SDL_GLContext context_;
    Input* input_;
    std::vector<GraphicObject*> gObjects_;
    std::vector<Crystal> l_Crystal_;
    Camera* camera_;
    bool fullscreen_;
    bool oculusRender_;
    std::vector<int> fps_;
    std::vector<Star> lStar_;

    void updateFPS(int elapsedTime, int interval = 1);

};


#endif
