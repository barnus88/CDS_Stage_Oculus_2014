#include "Oculus.h"

NullOculus::NullOculus()
{
    std::cout << "Null oculus constructor"<<std::endl;;
}

NullOculus::~NullOculus()
{
    std::cout << "Null oculus destructor"<<std::endl;;
}

bool GenericOculus::isMoving() const
{
    std::cout<< "Generic Oculus is not moving"<<std::endl;;
    return false;
}

bool GenericOculus::isUsingDebugHmd()
{
    return true;
}

glm::vec3 GenericOculus::dAngles() const
{
    return glm::vec3(0, 0, 0);
}

