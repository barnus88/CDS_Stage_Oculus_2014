/*#include "Utils.h"
#include "CrystalTexture.h"


std::vector<Texture*> CrystalTexture::textures_;
int CrystalTexture::nbInstances = 0;

CrystalTexture::CrystalTexture(float x, float y, float z, float size, std::string const vertexShader, std::string const fragmentShader, std::string texture):
  Crystal(x, y, z, size, vertexShader, fragmentShader),
  texture_ {nullptr}
{
    CrystalTexture::nbInstances++;

  for(auto & t : CrystalTexture::textures_)
  {
    if(t->file() == texture)
    {
        texture_ = t;
        LOG("Found texture " + t->file(), std::cout);
    }
  }

  if(texture_ == nullptr)
  {
      texture_ = new Texture(texture);
      CrystalTexture::textures_.push_back(texture_);

      LOG("Create texture " + texture, std::cout);
  }

  textureCoord_ = {0, 0,   1, 0,   1, 1,     // Face 1
                   0, 0,   0, 1,   1, 1,     // Face 1

                   0, 0,   1, 0,   1, 1,     // Face 2
                   0, 0,   0, 1,   1, 1,     // Face 2

                   0, 0,   1, 0,   1, 1,     // Face 3
                   0, 0,   0, 1,   1, 1,     // Face 3

                   0, 0,   1, 0,   1, 1,     // Face 4
                   0, 0,   0, 1,   1, 1,     // Face 4

                   0, 0,   1, 0,   1, 1,     // Face 5
                   0, 0,   0, 1,   1, 1,     // Face 5

                   0, 0,   1, 0,   1, 1,     // Face 6
                   0, 0,   0, 1,   1, 1,    // Face 6

                   0, 0,   1, 0,   1, 1,     // Face 7
                   0, 0,   0, 1,   1, 1,    // Face 7

                   0, 0,   1, 0,   1, 1,     // Face 8
                   0, 0,   0, 1,   1, 1};    // Face 8
  load();

}

CrystalTexture::~CrystalTexture()
{
    if(CrystalTexture::nbInstances == 1)
    {
        for(int i=0; i<CrystalTexture::textures_.size(); i++)
        {
            delete CrystalTexture::textures_[i];
        }
        CrystalTexture::textures_.clear();
    }

   CrystalTexture::nbInstances--;

}

void CrystalTexture::draw(glm::mat4 &projection, glm::mat4 &modelview)
{
    modelview = glm::translate(modelview, position_);

  glUseProgram(shader_->getProgramID());


  glBindVertexArray(VAOId_);



      // Envoi des matrices

      glUniformMatrix4fv(glGetUniformLocation(shader_->getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
      glUniformMatrix4fv(glGetUniformLocation(shader_->getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));


      // Verrouillage de la texture

      glBindTexture(GL_TEXTURE_2D, texture_->getID());


      // Rendu
        std::cout<< " size : "<< vertices_.size()/3 <<std::endl;
      glDrawArrays(GL_TRIANGLES, 0, vertices_.size()/3);


      // Déverrouillage de la texture

      glBindTexture(GL_TEXTURE_2D, 0);


      // Désactivation des tableaux

      //glDisableVertexAttribArray(2);
      //glDisableVertexAttribArray(0);
   glBindVertexArray(0);

  // Désactivation du shader

  glUseProgram(0);

  modelview = glm::translate(modelview, - position_);

}

void CrystalTexture::load()
{
    //VBO
    if(glIsBuffer(VBOId_) == GL_TRUE)
    {
        glDeleteBuffers(1, &VBOId_);
    }


    glGenBuffers(1, &VBOId_);
    glBindBuffer(GL_ARRAY_BUFFER, VBOId_);

        glBufferData(GL_ARRAY_BUFFER, nbVerticesBytes() + nbTextureBytes(), 0, GL_STATIC_DRAW);


        glBufferSubData(GL_ARRAY_BUFFER, 0, nbVerticesBytes(), vertices_.data());
        glBufferSubData(GL_ARRAY_BUFFER, nbVerticesBytes(), nbTextureBytes(), textureCoord_.data());

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //VAO
    if(glIsVertexArray(VAOId_) == GL_TRUE)
      glDeleteVertexArrays(1, &VAOId_);

    glGenVertexArrays(1, &VAOId_);
    glBindVertexArray(VAOId_);

        glBindBuffer(GL_ARRAY_BUFFER, VBOId_);
            // Envoi des vertices

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0,  BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);


            // Envoi des coordonnées de texture

            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0,  BUFFER_OFFSET(nbVerticesBytes()));
            glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

}

int CrystalTexture::nbTextureBytes()
{
    return textureCoord_.size() * sizeof(float);
}
int CrystalTexture::getNbInstances()
{
    return nbInstances;
}

void CrystalTexture::setNbInstances(int value)
{
    nbInstances = value;
}
Texture* CrystalTexture::texture() const
{
    return texture_;
}

void CrystalTexture::setTexture(Texture* texture)
{
    texture_ = texture;
}
std::vector<Texture*> CrystalTexture::textures()
{
    return textures_;
}

void CrystalTexture::setTextures(const std::vector<Texture*>& textures)
{
    textures_ = textures;
}

void CrystalTexture::print()
{
    LOG("CrystalTexture: texture name: " + texture_->file() + ", texture id: " + std::to_string(texture_->getID()), std::cout);
}
*/
