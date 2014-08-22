#include "Scene.h"


#include "Input.h"
#include "Parser.h"
#include "Crate.h"
//#include "CrystalTexture.h"
#include "Texture.h"
#include "Camera.h"
#include "GraphicObject.h"
#include "Utils.h"

#include <numeric>
#include <random>
#include <chrono>

#define SIZE 64

Scene::Scene(std::string windowTitle, int windowWidth, int windowHeight, bool oculusRender, bool fullscreen):
  windowTitle_(windowTitle),
  windowWidth_(windowWidth),
  windowHeight_(windowHeight),
  input_ (nullptr),
  camera_ (nullptr),
//  oculus_ {Oculus<Scene>()},
  fullscreen_ (fullscreen),
  oculusRender_ (oculusRender)
{
    input_ = new Input(this);
    camera_ = new Camera(glm::vec3(-110.0, 0.0, 0.0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), 0.5, 0.5);
    camera_->setInput(input_);
}

Scene::~Scene()
{
  for(int i=0; i<gObjects_.size(); i++)
  {
      delete gObjects_[i];
  }
  gObjects_.clear();

  if(oculusRender_)
    delete oculus_;

  delete input_;
  delete camera_;


  SDL_GL_DeleteContext(context_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

bool Scene::initWindow()
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "Error opening the SDL : " << SDL_GetError() << std::endl;
    SDL_Quit();

    return false;
  }


  //Version
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // Double Buffer
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


  Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
  if(fullscreen_)
      flags |= SDL_WINDOW_MAXIMIZED;

  window_ = SDL_CreateWindow(windowTitle_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth_, windowHeight_, flags);

  if(window_ == nullptr)
  {
    std::cerr << "Error creating the window : " << SDL_GetError() << std::endl;
    SDL_Quit();

    return -1;
  }

 //Context
  context_ = SDL_GL_CreateContext(window_);

  if(context_ == 0)
  {
    std::cerr << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window_);
    SDL_Quit();

    return false;
  }

  return true;

}

bool Scene::initGL()
{
    glewExperimental = GL_TRUE;
    GLenum initGLEW( glewInit() );
    if(initGLEW != GLEW_OK)
    {
      std::cerr << "Error opening GLEW : " << glewGetErrorString(initGLEW) << std::endl;
      SDL_GL_DeleteContext(context_);
      SDL_DestroyWindow(window_);
      SDL_Quit();

      return false;
    }
  glEnable(GL_DEPTH_TEST);


  return true;
}

double Scene::maximum(){
    double ret(-1);
    vector<Star>::iterator it;
    for(it = lStar_.begin(); it!=lStar_.end(); ++it){
        if(it->m_x>ret){
            ret=it->m_x;
        }
        if(it->m_y>ret){
            ret=it->m_y;
        }
        if(it->m_z>ret){
            ret=it->m_z;
        }
    }
    return ret;
}

double Scene::minimum(){
    double ret(1);
    vector<Star>::iterator it;
    for(it = lStar_.begin(); it!=lStar_.end(); ++it){
        if(it->m_x<ret){
            ret=it->m_x;
        }
        if(it->m_y<ret){
            ret=it->m_y;
        }
        if(it->m_z<ret){
            ret=it->m_z;
        }

        if(it->m_z<0 || it->m_x<0 || it->m_y<0){
            ret=0;
        }
    }
    return ret;
}

void Scene::initEchelle()
{
    ///////////////////////////
    // Calcul de l'�chelle : //
    ///////////////////////////
    double valeurMax=maximum();
    double valeurMin=minimum();


    double ecart(valeurMax-valeurMin);
    int nbUnite=100;
    double cote=nbUnite;//nbUnite/(ecart+0.00);

    cout << "val min : "<< valeurMin <<endl;

    cout << "val max : "<< valeurMax <<endl;

    cout << "ecart : "<< ecart <<endl;

    cout << "cote : "<< cote <<endl;

    // On applique l'�chelle � toutes les �toiles :
    vector<Star>::iterator it;
    int i=0;
    for(it = lStar_.begin(); it!=lStar_.end(); ++it){
        it->m_posX=it->m_x*cote-nbUnite/2;
        it->m_posY=it->m_y*cote-nbUnite/2;
        //cout << "eca : "<< it->m_y << " -> " << cote << "-->"<< (it->m_y*cote) << endl;
        it->m_posZ=it->m_z*cote-nbUnite/2;
        i++;
        //cout<< it->m_id <<" "<< it->m_mass << " " << it->m_x << " " << it->m_y << " " << it->m_z << " " << it->m_age << " ------> "<< "Pos X : " << it->m_posX <<"Pos Y : " << it->m_posY << "Pos Z : " << it->m_posY << endl;
    }
    cout << "Nombre de lignes : "<< lStar_.size() <<endl;

}

void Scene::setupGObjects()
{
    string sTemp="cube" + std::to_string(64);
    Parser parser(sTemp);

    std::cout << "Lecture du fichier..."<<std::endl;
    //lStar_=parser.readFile2();

    //float cube[(size*size*size)];
    float cube[64*64*64]={0};

    int parserOk=parser.readBinaryFile(cube,SIZE);


    if(parserOk==0){
        std::cout << "Parsing OK "<<std::endl;
        float x=0;
        float y=0;
        float z=0;

        int sizeCarre=SIZE*SIZE;

        for(int j=0;j<((64*64*64)/3);j++){
            z = j / sizeCarre;
            int mod=j%sizeCarre;
            y = ( mod ) / SIZE;
            x = ( mod ) % SIZE;
            //gObjects_.push_back(new Crystal(x, y, z, 1.0, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag"));
            Star s(j,0,x,y,z,0);
            lStar_.push_back(s);
            if(j%100==0){
                std::cout << "Init "<< j<<std::endl;
            }
        }
        Crystal c(1.0,lStar_,"Shaders/couleur3D.vert", "Shaders/couleur3D.frag");

        initEchelle();

        auto start=std::chrono::high_resolution_clock::now();
        /*for(int i=0;i<10000;i++){
            gObjects_.push_back(new Crystal(lStar_[i].m_posX, lStar_[i].m_posY, lStar_[i].m_posZ, 1.0, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag"));
        }*/
        auto end =std::chrono::high_resolution_clock::now();

        auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(duration1).count();
        std::cout<< "Temps : "<< duration <<std::endl;


    }else{
        std::cout << "Parsing non OK !"<< std::endl;
    }


      /*Crystal* crystal = new Crystal(1.0, 2.0, 0.0, 1.0, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag");
      gObjects_.push_back(crystal);

      Crystal* crystal2 = new Crystal(-1.0, 10.0, 1.0, 1.0, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag");
      gObjects_.push_back(crystal2);
*/
}

void Scene::mainLoop()
{
  unsigned int frameRate = 1000 / 60;
  Uint32 start (0);
  Uint32 end  (0);
  Uint32 elapsedTime (0);




  input_->showCursor(false);
  input_->capturePointer(true);

  if(oculusRender_)
  {
    oculus_ = new Oculus<Scene>(this);
    input_->setOculus(oculus_);
  }
  while(! input_->isOver())
  {
    start = SDL_GetTicks();
    //Events
    input_->updateEvent();
    if(input_->isKeyboardKeyDown(SDL_SCANCODE_ESCAPE))
      break;
    if(oculusRender_)
    {
        oculus_->render();
    }
    else
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        render();
    }
    if(!oculusRender_){
      SDL_GL_SwapWindow(window_);
    }


    //Wait for FPS
    end = SDL_GetTicks();
    elapsedTime = end - start;
    LOG("Elapsed time: " + std::to_string(elapsedTime) + " ms", std::cout);
    updateFPS(elapsedTime);

    if(elapsedTime < frameRate)
    {
      SDL_Delay(frameRate - elapsedTime);
    }

  }
  double fpsMean = std::accumulate(fps_.begin(), fps_.end(), 0.0) / fps_.size();
  std::cout << "Mean fps: " + std::to_string(fpsMean) << std::endl;
}


void Scene::render()
{
  glm::mat4 projection;
  glm::mat4 modelview;

  double ratio = static_cast<double>(windowWidth_ / windowHeight_);

  projection = glm::perspective(90.0, ratio, 0.01, 10000.0);
  modelview = glm::mat4(2.0);

  Scene::render(modelview, projection);

}

/*void Scene::render(glm::mat4 & MV, glm::mat4 & proj)
{
    int sizeToRender = octantSize_ * octantsDrawnCount_;

    double e = std::numeric_limits<double>::epsilon();
    camera_->move(glm::vec3(sizeToRender + e, sizeToRender + e, sizeToRender + e) , glm::vec3(size_ - sizeToRender -e, size_ - sizeToRender -e, size_ - sizeToRender -e));
    camera_->lookAt(MV);

    for(int z=camera_->position().z - sizeToRender; z<camera_->position().z + sizeToRender; z++)
    {
        for(int y=camera_->position().y - sizeToRender; y<camera_->position().y + sizeToRender; y++)
        {
            for(int x=camera_->position().x - sizeToRender; x<camera_->position().x + sizeToRender; x++)
            {
                if(g0Objects_.at(x, y, z) != nullptr)
                    gObjects_.at(x, y, z)->draw(proj, MV);
            }
        }

    }

}*/
/*
void Scene::render()
{
  glm::mat4 projection;
  glm::mat4 modelview;

  double ratio = static_cast<double>(windowWidth_ / windowHeight_);

  projection = glm::perspective(90.0, ratio, 0.01, 10000.0);
  modelview = glm::mat4(2.0);

  camera_->move();
  camera_->lookAt(modelview);

  for(auto & gObject : gObjects_)
  {
      gObject->draw(projection, modelview);
  }

}
*/

void Scene::render(glm::mat4 & MV, glm::mat4 & proj)
{
    camera_->move();
    camera_->lookAt(MV);

   /* for(auto & gObject : gObjects_)
    {
        gObject->draw(proj, MV);
    }*/
    //l_Crystal_[0].afficher(proj, MV, 1000);

}

Oculus<Scene> *Scene::oculus() const
{
    return oculus_;
}

void Scene::setOculus(Oculus<Scene> *oculus)
{
    oculus_ = oculus;
}



SDL_Window* Scene::getWindow() const
{
    return window_;
}

Camera* Scene::getCamera()
{
    return camera_;
}
int Scene::windowWidth() const
{
    return windowWidth_;
}

void Scene::setWindowWidth(int windowWidth)
{
    windowWidth_ = windowWidth;
}
int Scene::windowHeight() const
{
    return windowHeight_;
}

void Scene::setWindowHeight(int windowHeight)
{
    windowHeight_ = windowHeight;

}



void Scene::updateFPS(int elapsedTime, int interval)
{
    if (elapsedTime==0){
      elapsedTime=1;
    }
    int fps = 1000 / elapsedTime;
    fps_.push_back(fps);

    if(elapsedTime > interval)
    {
        LOG("FPS: " + std::to_string(fps), std::cout);

        std::string newTitle = windowTitle_ + " (" + std::to_string(fps) + "FPS)";
        SDL_SetWindowTitle(window_, newTitle.c_str());
    }
}
