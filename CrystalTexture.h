/*#ifndef DEF_CRYSTALTEXTURE
#define DEF_CRYSTALTEXTURE


#include "Crystal.h"
#include "Texture.h"
#include <string>

class CrystalTexture: public Crystal
{
  public:
      CrystalTexture(float x, float y, float z, float size, std::string const vertexShader, std::string const fragmentShader, std::string texture);
      virtual ~CrystalTexture();
      void draw(glm::mat4 &projection, glm::mat4 &modelview);
      void load();

      int nbTextureBytes();



      static int getNbInstances();
      static void setNbInstances(int value);

      Texture* texture() const;
      void setTexture(Texture* texture);

      static std::vector<Texture*> textures();
      static void setTextures(const std::vector<Texture*>& textures);



      void print();
protected:
      static std::vector<Texture*> textures_;
      static int nbInstances;
      Texture* texture_;
    std::vector<float> textureCoord_;
};

#endif
*/
