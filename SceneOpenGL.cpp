#include "SceneOpenGL.h"
#include <limits>

// Permet d'éviter la ré-écriture du namespace glm::

using namespace glm;


// Constructeur de Destucteur

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre, vector<Star> l) : m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre),
                                                                                             m_hauteurFenetre(hauteurFenetre), m_lStar(l), m_fenetre(0), m_contexteOpenGL(0),
                                                                                             m_input()
{

}


SceneOpenGL::~SceneOpenGL()
{
    SDL_GL_DeleteContext(m_contexteOpenGL);
    SDL_DestroyWindow(m_fenetre);
    SDL_Quit();
}


// Méthodes

bool SceneOpenGL::initialiserFenetre()
{
    // Initialisation de la SDL

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }


    // Version d'OpenGL

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


    // Double Buffer

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


    // Création de la fenêtre

    m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_largeurFenetre, m_hauteurFenetre, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(m_fenetre == 0)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }


    // Création du contexte OpenGL

    m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);

    if(m_contexteOpenGL == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_fenetre);
        SDL_Quit();

        return false;
    }

    return true;
}


bool SceneOpenGL::initGL()
{
    #ifdef WIN32

        // On initialise GLEW

        GLenum initialisationGLEW( glewInit() );


        // Si l'initialisation a échoué :

        if(initialisationGLEW != GLEW_OK)
        {
            // On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)

            std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;


            // On quitte la SDL

            SDL_GL_DeleteContext(m_contexteOpenGL);
            SDL_DestroyWindow(m_fenetre);
            SDL_Quit();

            return false;
        }

    #endif


    // Activation du Depth Buffer

    glEnable(GL_DEPTH_TEST);


    // Tout s'est bien passé, on retourne true

    return true;
}

double SceneOpenGL::maximum(){
    double ret(-1);
    vector<Star>::iterator it;
    for(it = m_lStar.begin(); it!=m_lStar.end(); ++it){
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

double SceneOpenGL::minimum(){
    double ret(1);
    vector<Star>::iterator it;
    for(it = m_lStar.begin(); it!=m_lStar.end(); ++it){
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

void SceneOpenGL::initEchelle()
{
    ///////////////////////////
    // Calcul de l'échelle : //
    ///////////////////////////
    double valeurMax=maximum();
    double valeurMin=minimum();


    double ecart(valeurMax-valeurMin);
    int nbUnite=50;
    double cote=nbUnite/(ecart+0.00);

	cout << "ecart : "<< valeurMin <<endl;

	cout << "ecart : "<< valeurMax <<endl;

	cout << "ecart : "<< ecart <<endl;

    // On applique l'échelle à toutes les étoiles :
    vector<Star>::iterator it;
	int i=0;
    for(it = m_lStar.begin(); it!=m_lStar.end(); ++it){
        it->m_posX=it->m_x*cote;//-nbUnite/2;
        it->m_posY=it->m_y*cote-nbUnite/2;
		//cout << "eca : "<< it->m_y << " -> " << cote << "-->"<< (it->m_y*cote) << endl;
        it->m_posZ=it->m_z*cote;//-nbUnite/2;
		i++;
        //cout<< it->m_id <<" "<< it->m_mass << " " << it->m_x << " " << it->m_y << " " << it->m_z << " " << it->m_age << " ------> "<< "Pos X : " << it->m_posX <<"Pos Y : " << it->m_posY << "Pos Z : " << it->m_posY << endl;
    }
    cout << "Nombre de lignes : "<< m_lStar.size() <<endl;

}

void SceneOpenGL::bouclePrincipale()
{
    // Variables relatives à la boucle

    Uint32 frameRate (1000 / 50);
    Uint32 debutBoucle(0), finBoucle(0), tempsEcoule(0);
    Uint32 testTime1(0), testTime2(0), testTime3(0), testTime4(0);

    bool afficheFPS(false);
    bool unSeulObjet(true);


    // Matrices

    mat4 projection;
    mat4 modelview;

    projection = perspective(70.0, (double) m_largeurFenetre / m_hauteurFenetre, 1.0, 1000.0);
    modelview = mat4(1.0);

	 // Caméra mobile

    Camera camera(vec3(3, 3, 3), vec3(0, 0, 0), vec3(0, 1, 0), 0.5, 0.5);
    m_input.afficherPointeur(false);
    m_input.capturerPointeur(true);


	Crystal *crystal;
    if(!unSeulObjet){
        crystal=new Crystal(1.0, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag");
    }else{
        crystal=new Crystal(0.1, m_lStar, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag");
    }
    // Variable angle

    float angle(0.0);


    // Boucle principale

    while(!m_input.terminer())
    {
        // On définit le temps de début de boucle

        debutBoucle = SDL_GetTicks();


        // Gestion des évènements

		m_input.updateEvenements();

        if(m_input.getTouche(SDL_SCANCODE_ESCAPE))
           break;

        camera.deplacer(m_input);


        // Nettoyage de l'écran

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Gestion de la caméra

        camera.lookAt(modelview);
        testTime1=SDL_GetTicks();


        // Incrémentation de l'angle

        angle += 4.0;

        if(angle >= 360.0)
            angle -= 360.0;


        // Rotation du repère

        //modelview = rotate(modelview, angle, vec3(0, 1, 0));



        if(!unSeulObjet){
            vector<Star>::iterator it;
            for(it = m_lStar.begin(); it!=m_lStar.end(); ++it){
                // Sauvegarde de la matrice modelview
                mat4 sauvegardeModelview = modelview;

                // Translation pour positionner l'etoile
                modelview = translate(modelview, vec3(it->m_posX, it->m_posY, it->m_posZ));

                // Affichage de l'etoile
                testTime3=SDL_GetTicks();
                crystal->afficher(projection, modelview);
                testTime4=SDL_GetTicks();
                // Restauration de la matrice
                modelview = sauvegardeModelview;
            }
        }else{
            testTime3=SDL_GetTicks();
            crystal->afficher(projection, modelview, m_lStar.size()*3*8);
            testTime4=SDL_GetTicks();
        }



        // Actualisation de la fenêtre

        SDL_GL_SwapWindow(m_fenetre);


        // Calcul du temps écoulé

        finBoucle = SDL_GetTicks();
        tempsEcoule = finBoucle - debutBoucle;


        // Si nécessaire, on met en pause le programme

        if(tempsEcoule < frameRate){
            SDL_Delay(frameRate - tempsEcoule);
            if (afficheFPS){
				std::cout<< "fps : "<< 1000/frameRate <<std::endl;
			}
        }else{
            if (tempsEcoule!=0 && afficheFPS){
				std::cout<< "fps : " << 1000/tempsEcoule <<std::endl;
			}
        }
    }
}
