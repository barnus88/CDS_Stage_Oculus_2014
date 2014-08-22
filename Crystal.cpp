#include "Crystal.h"


// Permet d'éviter la ré-écriture du namespace glm::

using namespace glm;


// Constructeur et Destructeur

Crystal::Crystal(float taille, std::string const vertexShader, std::string const fragmentShader) : m_shader(vertexShader, fragmentShader)
{
    m_vertices= new float[72];
    m_couleurs= new float[72];
    // Chargement du shader

    m_shader.charger();


    // Division de la taille

    taille /= 2;

// Vertices temporaires

    float verticesTmp[] = {-taille, 0, -taille,   taille, 0, -taille,   0, taille*2, 0,      // Triangle 1
                           taille, 0, -taille,   taille, 0, taille,  0, taille*2, 0,         // Triangle 2
                           taille, 0, taille,   -taille, 0, taille,   0, taille*2, 0,        // Triangle 3
                           -taille, 0, taille,   -taille, 0, -taille,   0, taille*2, 0,      // Triangle 4

                           -taille, 0, -taille,   taille, 0, -taille,   0, -taille*2, 0,     // Triangle 5
                           taille, 0, -taille,   taille, 0, taille,  0, -taille*2, 0,        // Triangle 6
                           taille, 0, taille,   -taille, 0, taille,   0, -taille*2, 0,       // Triangle 7
                           -taille, 0, taille,   -taille, 0, -taille,   0, -taille*2, 0};    // Triangle 8


    // Couleurs temporaires

    float couleursTmp[] = {1.0, 0.5, 0.0,   1.0, 0.5, 0.0,   1.0, 0.5, 0.0,           // Face 1

                           0.5, 1.0, 0.0,   0.5, 1.0, 0.0,   0.5, 1.0, 0.0,           // Face 2

                           0.0, 0.5, 1.0,   0.0, 0.5, 1.0,   0.0, 0.5, 1.0,           // Face 3

                           1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,           // Face 4

                           0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,           // Face 5

                           0.5, 0.5, 1.0,   0.5, 0.5, 1.0,   0.5, 0.5, 1.0,          // Face 6

                           1.0, 0.0, 0.5,   1.0, 0.0, 0.5,   1.0, 0.0, 0.5,          // Face 7

                           0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0};          // Face 8


    // Copie des valeurs dans les tableaux finaux

    for(int i(0); i < 72; i++)
    {
        m_vertices[i] = verticesTmp[i];
        m_couleurs[i] = couleursTmp[i];
    }
}

Crystal::Crystal(float taille, std::vector<Star> lStar, std::string const vertexShader, std::string const fragmentShader) : m_shader(vertexShader, fragmentShader)
{

    int nbTriangle(8);

    m_vertices= new float[lStar.size()*nbTriangle*9];
    m_couleurs= new float[lStar.size()*nbTriangle*9];
    // Chargement du shader

    m_shader.charger();


    // Division de la taille

    taille /= 2;

// Vertices temporaires

    //float tmp[lStar.size()*nbTriangle*9];
    for(int i(0); i < (int)lStar.size(); i++)
    {
        m_vertices[i*nbTriangle*9]=lStar.at(i).m_posX-taille;
        m_vertices[i*nbTriangle*9+1]=lStar.at(i).m_posY;
        m_vertices[i*nbTriangle*9+2]=lStar.at(i).m_posZ-taille;
        m_vertices[i*nbTriangle*9+3]=lStar.at(i).m_posX+taille;
        m_vertices[i*nbTriangle*9+4]=lStar.at(i).m_posY;
        m_vertices[i*nbTriangle*9+5]=lStar.at(i).m_posZ-taille;
        m_vertices[i*nbTriangle*9+6]=lStar.at(i).m_posX;
        m_vertices[i*nbTriangle*9+7]=lStar.at(i).m_posY+taille*2;
        m_vertices[i*nbTriangle*9+8]=lStar.at(i).m_posZ;

        m_vertices[i*nbTriangle*9+9]=lStar.at(i).m_posX+taille;
        m_vertices[i*nbTriangle*9+10]=lStar.at(i).m_posY;
        m_vertices[i*nbTriangle*9+11]=lStar.at(i).m_posZ-taille;
        m_vertices[i*nbTriangle*9+12]=lStar.at(i).m_posX+taille;
        m_vertices[i*nbTriangle*9+13]=lStar.at(i).m_posY;
        m_vertices[i*nbTriangle*9+14]=lStar.at(i).m_posZ+taille;
        m_vertices[i*nbTriangle*9+15]=lStar.at(i).m_posX;
        m_vertices[i*nbTriangle*9+16]=lStar.at(i).m_posY+taille*2;
        m_vertices[i*nbTriangle*9+17]=lStar.at(i).m_posZ;

        m_vertices[i*nbTriangle*9+18]=lStar.at(i).m_posX+taille;
        m_vertices[i*nbTriangle*9+19]=lStar.at(i).m_posY;
        m_vertices[i*nbTriangle*9+20]=lStar.at(i).m_posZ+taille;
        m_vertices[i*nbTriangle*9+21]=lStar.at(i).m_posX-taille;
        m_vertices[i*nbTriangle*9+22]=lStar.at(i).m_posY;
        m_vertices[i*nbTriangle*9+23]=lStar.at(i).m_posZ+taille;
        m_vertices[i*nbTriangle*9+24]=lStar.at(i).m_posX;
        m_vertices[i*nbTriangle*9+25]=lStar.at(i).m_posY+taille*2;
        m_vertices[i*nbTriangle*9+26]=lStar.at(i).m_posZ;

        m_vertices[i*nbTriangle*9+27]=lStar.at(i).m_posX-taille;
        m_vertices[i*nbTriangle*9+28]=lStar.at(i).m_posY;
        m_vertices[i*nbTriangle*9+29]=lStar.at(i).m_posZ+taille;
        m_vertices[i*nbTriangle*9+30]=lStar.at(i).m_posX-taille;
        m_vertices[i*nbTriangle*9+31]=lStar.at(i).m_posY;
        m_vertices[i*nbTriangle*9+32]=lStar.at(i).m_posZ-taille;
        m_vertices[i*nbTriangle*9+33]=lStar.at(i).m_posX;
        m_vertices[i*nbTriangle*9+34]=lStar.at(i).m_posY+taille*2;
        m_vertices[i*nbTriangle*9+35]=lStar.at(i).m_posZ;


        m_vertices[i*nbTriangle*9+36]=lStar.at(i).m_posX-taille;
        m_vertices[i*nbTriangle*9+37]=lStar.at(i).m_posY;
        m_vertices[i*nbTriangle*9+38]=lStar.at(i).m_posZ-taille;
        m_vertices[i*nbTriangle*9+39]=lStar.at(i).m_posX+taille;
        m_vertices[i*nbTriangle*9+40]=lStar.at(i).m_posY;
        m_vertices[i*nbTriangle*9+41]=lStar.at(i).m_posZ-taille;
        m_vertices[i*nbTriangle*9+42]=lStar.at(i).m_posX;
        m_vertices[i*nbTriangle*9+43]=lStar.at(i).m_posY-taille*2;
        m_vertices[i*nbTriangle*9+44]=lStar.at(i).m_posZ;

        m_vertices[i*nbTriangle*9+45]=lStar.at(i).m_posX+taille;
        m_vertices[i*nbTriangle*9+46]=lStar.at(i).m_posY;
        m_vertices[i*nbTriangle*9+47]=lStar.at(i).m_posZ-taille;
        m_vertices[i*nbTriangle*9+48]=lStar.at(i).m_posX+taille;
        m_vertices[i*nbTriangle*9+49]=lStar.at(i).m_posY;
        m_vertices[i*nbTriangle*9+50]=lStar.at(i).m_posZ+taille;
        m_vertices[i*nbTriangle*9+51]=lStar.at(i).m_posX;
        m_vertices[i*nbTriangle*9+52]=lStar.at(i).m_posY-taille*2;
        m_vertices[i*nbTriangle*9+53]=lStar.at(i).m_posZ;

        m_vertices[i*nbTriangle*9+54]=lStar.at(i).m_posX+taille;
        m_vertices[i*nbTriangle*9+55]=lStar.at(i).m_posY;
        m_vertices[i*nbTriangle*9+56]=lStar.at(i).m_posZ+taille;
        m_vertices[i*nbTriangle*9+57]=lStar.at(i).m_posX-taille;
        m_vertices[i*nbTriangle*9+58]=lStar.at(i).m_posY;
        m_vertices[i*nbTriangle*9+59]=lStar.at(i).m_posZ+taille;
        m_vertices[i*nbTriangle*9+60]=lStar.at(i).m_posX;
        m_vertices[i*nbTriangle*9+61]=lStar.at(i).m_posY-taille*2;
        m_vertices[i*nbTriangle*9+62]=lStar.at(i).m_posZ;

        m_vertices[i*nbTriangle*9+63]=lStar.at(i).m_posX-taille;
        m_vertices[i*nbTriangle*9+64]=lStar.at(i).m_posY;
        m_vertices[i*nbTriangle*9+65]=lStar.at(i).m_posZ+taille;
        m_vertices[i*nbTriangle*9+66]=lStar.at(i).m_posX-taille;
        m_vertices[i*nbTriangle*9+67]=lStar.at(i).m_posY;
        m_vertices[i*nbTriangle*9+68]=lStar.at(i).m_posZ-taille;
        m_vertices[i*nbTriangle*9+69]=lStar.at(i).m_posX;
        m_vertices[i*nbTriangle*9+70]=lStar.at(i).m_posY-taille*2;
        m_vertices[i*nbTriangle*9+71]=lStar.at(i).m_posZ;
    }


    double color[3];
    double min=1000000000000;
    double max=-1;

    for(int i(0); i < (int)lStar.size(); i++)
    {
        if(lStar.at(i).m_mass<min){
            min=lStar.at(i).m_mass;
        }
    }
    for(int i(0); i < (int)lStar.size(); i++)
    {
        if(lStar.at(i).m_mass>max){
            max=lStar.at(i).m_mass;
        }
    }
    double cote=360/(max-min);

    std::cout<< min << " et " << max << std::endl;
    std::cout<< "cote : " << cote << std::endl;

    for(int i(0); i < (int)lStar.size(); i++)
    {
        double value((lStar.at(i).m_mass-min)*cote);
        //std::cout<< "value : " << color[0] << "   " << color[1]  << "   " <<  color[2] << std::endl;
        GroundColorMix(color,(value),0,1);


        m_couleurs[i*nbTriangle*9]=color[0];
        m_couleurs[i*nbTriangle*9+1]=color[1];
        m_couleurs[i*nbTriangle*9+2]=color[2];
        m_couleurs[i*nbTriangle*9+3]=color[0];
        m_couleurs[i*nbTriangle*9+4]=color[1];
        m_couleurs[i*nbTriangle*9+5]=color[2];
        m_couleurs[i*nbTriangle*9+6]=color[0];
        m_couleurs[i*nbTriangle*9+7]=color[1];
        m_couleurs[i*nbTriangle*9+8]=color[2];

        m_couleurs[i*nbTriangle*9+9]=color[0];
        m_couleurs[i*nbTriangle*9+10]=color[1];
        m_couleurs[i*nbTriangle*9+11]=color[2];
        m_couleurs[i*nbTriangle*9+12]=color[0];
        m_couleurs[i*nbTriangle*9+13]=color[1];
        m_couleurs[i*nbTriangle*9+14]=color[2];
        m_couleurs[i*nbTriangle*9+15]=color[0];
        m_couleurs[i*nbTriangle*9+16]=color[1];
        m_couleurs[i*nbTriangle*9+17]=color[2];

        m_couleurs[i*nbTriangle*9+18]=color[0];
        m_couleurs[i*nbTriangle*9+19]=color[1];
        m_couleurs[i*nbTriangle*9+20]=color[2];
        m_couleurs[i*nbTriangle*9+21]=color[0];
        m_couleurs[i*nbTriangle*9+22]=color[1];
        m_couleurs[i*nbTriangle*9+23]=color[2];
        m_couleurs[i*nbTriangle*9+24]=color[0];
        m_couleurs[i*nbTriangle*9+25]=color[1];
        m_couleurs[i*nbTriangle*9+26]=color[2];

        m_couleurs[i*nbTriangle*9+27]=color[0];
        m_couleurs[i*nbTriangle*9+28]=color[1];
        m_couleurs[i*nbTriangle*9+29]=color[2];
        m_couleurs[i*nbTriangle*9+30]=color[0];
        m_couleurs[i*nbTriangle*9+31]=color[1];
        m_couleurs[i*nbTriangle*9+31]=color[2];
        m_couleurs[i*nbTriangle*9+33]=color[0];
        m_couleurs[i*nbTriangle*9+34]=color[1];
        m_couleurs[i*nbTriangle*9+35]=color[2];

        m_couleurs[i*nbTriangle*9+36]=color[0];
        m_couleurs[i*nbTriangle*9+37]=color[1];
        m_couleurs[i*nbTriangle*9+38]=color[2];
        m_couleurs[i*nbTriangle*9+39]=color[0];
        m_couleurs[i*nbTriangle*9+40]=color[1];
        m_couleurs[i*nbTriangle*9+41]=color[2];
        m_couleurs[i*nbTriangle*9+42]=color[0];
        m_couleurs[i*nbTriangle*9+43]=color[1];
        m_couleurs[i*nbTriangle*9+44]=color[2];

        m_couleurs[i*nbTriangle*9+45]=color[0];
        m_couleurs[i*nbTriangle*9+46]=color[1];
        m_couleurs[i*nbTriangle*9+47]=color[2];
        m_couleurs[i*nbTriangle*9+48]=color[0];
        m_couleurs[i*nbTriangle*9+49]=color[1];
        m_couleurs[i*nbTriangle*9+50]=color[2];
        m_couleurs[i*nbTriangle*9+51]=color[0];
        m_couleurs[i*nbTriangle*9+52]=color[1];
        m_couleurs[i*nbTriangle*9+53]=color[2];

        m_couleurs[i*nbTriangle*9+54]=color[0];
        m_couleurs[i*nbTriangle*9+55]=color[1];
        m_couleurs[i*nbTriangle*9+56]=color[2];
        m_couleurs[i*nbTriangle*9+57]=color[0];
        m_couleurs[i*nbTriangle*9+58]=color[1];
        m_couleurs[i*nbTriangle*9+59]=color[2];
        m_couleurs[i*nbTriangle*9+60]=color[0];
        m_couleurs[i*nbTriangle*9+61]=color[1];
        m_couleurs[i*nbTriangle*9+62]=color[2];

        m_couleurs[i*nbTriangle*9+63]=color[0];
        m_couleurs[i*nbTriangle*9+64]=color[1];
        m_couleurs[i*nbTriangle*9+65]=color[2];
        m_couleurs[i*nbTriangle*9+66]=color[0];
        m_couleurs[i*nbTriangle*9+67]=color[1];
        m_couleurs[i*nbTriangle*9+68]=color[2];
        m_couleurs[i*nbTriangle*9+69]=color[0];
        m_couleurs[i*nbTriangle*9+70]=color[1];
        m_couleurs[i*nbTriangle*9+71]=color[2];

    }
    /*for(int i(0); i < (int)(lStar.size()*nbTriangle*9); i++)
    {
        m_couleurs[i] = tmp[i];
    }*/

}


Crystal::~Crystal()
{

}

void Crystal::GroundColorMix(double* color, double x, double min, double max)
{
   /*
    * Red = 0
    * Green = 1
    * Blue = 2
    */
    double posSlope = (max-min)/60;
    double negSlope = (min-max)/60;

    if( x < 60 )
    {
        color[0] = max;
        color[1] = posSlope*x+min;
        color[2] = min;
        return;
    }
    else if ( x < 120 )
    {
        color[0] = negSlope*x+2*max+min;
        color[1] = max;
        color[2] = min;
        return;
    }
    else if ( x < 180  )
    {
        color[0] = min;
        color[1] = max;
        color[2] = posSlope*x-2*max+min;
        return;
    }
    else if ( x < 240  )
    {
        color[0] = min;
        color[1] = negSlope*x+4*max+min;
        color[2] = max;
        return;
    }
    else if ( x < 300  )
    {
        color[0] = posSlope*x-4*max+min;
        color[1] = min;
        color[2] = max;
        return;
    }
    else
    {
        color[0] = max;
        color[1] = min;
        color[2] = negSlope*x+6*max;
        return;
    }
}


// Méthodes

void Crystal::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{
    // Activation du shader

    glUseProgram(m_shader.getProgramID());


        // Envoi des vertices

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
        glEnableVertexAttribArray(0);


        // Envoi de la couleur

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, m_couleurs);
        glEnableVertexAttribArray(1);


        // Envoi des matrices

        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));


        // Rendu

        glDrawArrays(GL_TRIANGLES, 0, 24);


        // Désactivation des tableaux

        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);


    // Désactivation du shader

    glUseProgram(0);
}

void Crystal::afficher(glm::mat4 &projection, glm::mat4 &modelview, int nb)
{
    // Activation du shader

    glUseProgram(m_shader.getProgramID());


        // Envoi des vertices

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
        glEnableVertexAttribArray(0);


        // Envoi de la couleur

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, m_couleurs);
        glEnableVertexAttribArray(1);


        // Envoi des matrices

        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));


        // Rendu

        glDrawArrays(GL_TRIANGLES, 0, nb);


        // Désactivation des tableaux

        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);


    // Désactivation du shader

    glUseProgram(0);
}

