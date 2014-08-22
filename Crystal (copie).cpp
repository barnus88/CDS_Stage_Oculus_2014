
#include "Utils.h"
#include "Crystal.h"

#include <algorithm>



Crystal::Crystal(float x, float y, float z, float taille, std::string const vertexShader, std::string const fragmentShader):
    GraphicObject(x, y, z, taille, vertexShader, fragmentShader)
{
  shader_->load();

    //A B C D anti clockwise with A facing x axis +, E top, F bottom
    vertices_ = {-taille, 0, -taille,   taille, 0, -taille,   0, taille*2, 0,      // Triangle 1
                           taille, 0, -taille,   taille, 0, taille,  0, taille*2, 0,         // Triangle 2
                           taille, 0, taille,   -taille, 0, taille,   0, taille*2, 0,        // Triangle 3
                           -taille, 0, taille,   -taille, 0, -taille,   0, taille*2, 0,      // Triangle 4

                           -taille, 0, -taille,   taille, 0, -taille,   0, -taille*2, 0,     // Triangle 5
                           taille, 0, -taille,   taille, 0, taille,  0, -taille*2, 0,        // Triangle 6
                           taille, 0, taille,   -taille, 0, taille,   0, -taille*2, 0,       // Triangle 7
                           -taille, 0, taille,   -taille, 0, -taille,   0, -taille*2, 0};

    colors_ = {1.0, 0.5, 0.0,   1.0, 0.5, 0.0,   1.0, 0.5, 0.0,           // Face 1

                           0.5, 1.0, 0.0,   0.5, 1.0, 0.0,   0.5, 1.0, 0.0,           // Face 2

                           0.0, 0.5, 1.0,   0.0, 0.5, 1.0,   0.0, 0.5, 1.0,           // Face 3

                           1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 4

                           0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 5

                           0.5, 0.5, 1.0,   0.5, 0.5, 1.0,   0.5, 0.5, 1.0,          // Face 6

               1.0, 0.0, 0.5,   1.0, 0.0, 0.5,   1.0, 0.0, 0.5,          // Face 7

               0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,           // Face 6

                1.0, 0.0, 0.5,   1.0, 0.0, 0.5,   1.0, 0.0, 0.5,          // Face 7

                0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0};            // Face 6



    std::transform(vertices_.begin(), vertices_.end(), vertices_.begin(),
                   std::bind1st(std::multiplies<float>(), taille/2));

    load();

}

Crystal::~Crystal()
{

}

void Crystal::load()
{
    //VBO
    if(glIsBuffer(VBOId_) == GL_TRUE)
    {
        glDeleteBuffers(1, &VBOId_);
    }


    glGenBuffers(1, &VBOId_);
    glBindBuffer(GL_ARRAY_BUFFER, VBOId_);

        glBufferData(GL_ARRAY_BUFFER, nbVerticesBytes() + nbColorsBytes(), 0, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, nbVerticesBytes(), vertices_.data());
        glBufferSubData(GL_ARRAY_BUFFER, nbVerticesBytes(), nbColorsBytes(), colors_.data());

    glBindBuffer(GL_ARRAY_BUFFER, 0);


    //VAO
    if(glIsVertexArray(VAOId_) == GL_TRUE)
      glDeleteVertexArrays(1, &VAOId_);

    glGenVertexArrays(1, &VAOId_);
    glBindVertexArray(VAOId_);

        glBindBuffer(GL_ARRAY_BUFFER, VBOId_);
            //Vertices
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
            glEnableVertexAttribArray(0);

            //Colors
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(nbVerticesBytes()));
            glEnableVertexAttribArray(1);


            //glDisableVertexAttribArray(1);
            //glDisableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


}

void Crystal::draw(glm::mat4 &projection, glm::mat4 &modelview)
{
    modelview = glm::translate(modelview, position_);
  glUseProgram(shader_->getProgramID());

    glBindVertexArray(VBOId_);


      glUniformMatrix4fv(glGetUniformLocation(shader_->getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));
      glUniformMatrix4fv(glGetUniformLocation(shader_->getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));


      glDrawArrays(GL_TRIANGLES, 0, vertices_.size()/3);



    glBindVertexArray(0);

  glUseProgram(0);

  modelview = glm::translate(modelview, - position_);

}


