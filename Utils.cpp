#include "Utils.h"

#include <iostream>


namespace Utils
{


    void resizeWindow(int w, int h)
    {
        glViewport(0, 0, w, h);
    }

    void GLGetError()
    {
      if(! LOG_ENABLED) return;

      for(GLenum currError = glGetError(); currError != GL_NO_ERROR; currError = glGetError())
      {
        std::cerr << "Error: ";

        switch(currError)
        {
          case GL_INVALID_ENUM:
            std::cerr << "GL_INVALID_ENUM";
            break;
          case GL_INVALID_VALUE:
            std::cerr << "GL_INVALID_VALUE";
            break;
          case GL_INVALID_OPERATION:
            std::cerr << "GL_INVALID_OPERATION";
            break;
          case GL_STACK_OVERFLOW:
            std::cerr << "GL_STACK_OVERFLOW";
            break;
          case GL_STACK_UNDERFLOW:
            std::cerr << "GL_STACK_UNDERFLOW";
            break;
          case GL_OUT_OF_MEMORY:
            std::cerr << "GL_OUT_OF_MEMORY";
            break;
          case GL_INVALID_FRAMEBUFFER_OPERATION:
            std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
          case GL_TABLE_TOO_LARGE:
            std::cerr << "GL_TABLE_TOO_LARGE";
            break;
          default:
            std::cerr << "Unknow error";
            break;
        }
        std::cerr << std::endl;
      }
    }




    float degreeToRad(float value)
    {
        return value * M_PI / 180;
    }

    float radToDegree(float value)
    {
        return 180 * value / M_PI;
    }


    float clamp(float phi, float limit)
    {
        float res = phi;
        if(res > limit)
        {
          res = limit;
        }
        else if(res < -limit)
        {
          res = -limit;
        }

        if(phi != res)
            std::cout << "Clamping phi: " << phi << " -> " << res << std::endl;

        return res;
    }

    float isEqual(float a, float b)
    {
        return (fabs(a - b) < std::numeric_limits<double>::epsilon());
    }

    glm::mat4 ovr2glmMat(OVR::Matrix4f mat)
    {
        glm::mat4 res;

        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
                res[i][j] = mat.M[i][j];

        return res;
    }

    void print(glm::mat4 mat)
    {
        for(int i=0; i<4; i++)
        {
          for(int j=0; j<4; j++)
          {
            std::cout << mat[i][j] << " ";
          }
          std::cout << std::endl;
        }
    }

    void print(OVR::Matrix4f mat)
    {
        for(int i=0; i<4; i++)
        {
          for(int j=0; j<4; j++)
          {
            std::cout << mat.M[i][j] << " ";
          }
          std::cout << std::endl;
        }
    }

    void log(const std::string &message, const std::string &file, int line, std::ostream &out)
    {
        if(LOG_ENABLED)
            out << "[" << file << ":" << line << "]  "<< message << std::endl;
    }





}

