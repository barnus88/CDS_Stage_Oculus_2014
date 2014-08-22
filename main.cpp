#include "SceneOpenGL.h"
#include "Parser.h"
#include <vector>
#include <cstdlib>

#define SIZE 64

using namespace std;



int main(int argc, char **argv)
{


    //Parseur
    Parser parser("cube64");

    cout << "Lecture du fichier..."<<endl;
    //vector<Star> l=parser.readFile();
	cout << "Lecture du fichier..."<<endl;
    //vector<Star> l2=parser.readFile2();

    float cube[SIZE*SIZE*SIZE*3]={0};
    vector<Star> l3=parser.readBinaryFile(cube,SIZE);


    cout << "Nombre de lignes : "<< l3.size() <<endl;
        
    // Création de la sène
    cout << "Création de la scene..."<<endl;
    SceneOpenGL scene("Prototype", 1200, 900, l3);


    cout << "Initialisation de la fenetre..."<<endl;
    // Initialisation de la scène

    if(scene.initialiserFenetre() == false)
    return -1;

    cout << "Initialisation de GL..."<<endl;
    if(scene.initGL() == false)
    return -1;

    cout << "Initialisation de l'échelle..."<<endl;
    scene.initEchelle();
    // Boucle Principale

    cout << "Lancement..."<<endl;
    scene.bouclePrincipale();
		
	//system("PAUSE");


    return 0;
}
