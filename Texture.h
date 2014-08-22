#ifndef DEF_TEXTURE
#define DEF_TEXTURE


// Include

#ifdef WIN32
#include <GL/glew.h>

#else
#define GL3_PROTOTYPES 1
#include "Include/GL3/gl3.h"

#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>


// Classe Texture

class Texture
{
    public:

    Texture();
    Texture(std::string file);
    Texture(Texture const & texture);
    Texture& operator=(Texture const &texture);
    ~Texture();
    bool load();
    GLuint getID() const;
    void setFile(const std::string &file);
    const std::string & file() const;
    SDL_Surface * invertPixels(SDL_Surface * source) const;


    private:

    std::string file_;
    GLuint id_;

};

#endif
