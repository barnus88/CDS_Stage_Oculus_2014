#ifndef UTILS_H
#define UTILS_H

#include <GL/glew.h>
#include "Include/glm/glm.hpp"
#include "Include/OVR/LibOVR/Src/Kernel/OVR_Math.h"
#include <cmath>
#include <ostream>
#include <string>


#define LOG_ENABLED 0

namespace Utils
{
    void resizeWindow(int w, int h);
    void GLGetError();
    void print(glm::vec3 vec);
    float radToDegree(float value);
    float degreeToRad(float value);
    float clamp(float phi, float limit = 89.0f);
    float isEqual(float a, float b);
    glm::mat4 ovr2glmMat(OVR::Matrix4f mat);
    void print(glm::mat4 mat);
    void print(OVR::Matrix4f mat);

    void log(std::string const & message, std::string const & file, int line, std::ostream & out);



}

#define LOG( message, out ) Utils::log( message, __FILE__, __LINE__, out )

#endif // UTILS_H
