#include "SceneOpenGL.h"
#include "Parser.h"
#include <vector>
#include <cstdlib>

#define SIZE 64

using namespace std;


/////////////////////////////////
//////////////  USE /////////////
///   ./main <namefile> [-star]
/// -star si le fichier en entrée est un fichier d'étoiles, sinon le programme charge un cube.
/// /////////////////////////////



int main(int argc, char **argv)
{




    vector<Star> l;
    if(argc>1){
        Parser parser(argv[1]);
        float cube[SIZE*SIZE*SIZE*3]={0};
         if(argc>2){
            if(strcmp(argv[2],"-star")==0){
                cout << "MODE STAR"<<endl;
                l=parser.readFile2();
            }else{
                cout << "MODE CUBE"<<endl;
                l=parser.readBinaryFile(cube,SIZE);
            }
        }else{
             cout << "MODE CUBE"<<endl;
             l=parser.readBinaryFile(cube,SIZE);
        }
         cout << "Lecture du fichier..."<<endl;
         //vector<Star> l=parser.readFile();
         //cout << "Lecture du fichier..."<<endl;
         //vector<Star> l2=parser.readFile2();

         //vector<Star> l3=parser.readBinaryFile(cube,SIZE);


         cout << "Nombre de lignes : "<< l.size() <<endl;

         // Création de la sène
         cout << "Création de la scene..."<<endl;
         SceneOpenGL scene("Prototype", 1200, 900, l);


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
    }else{
        cout << "USE : ./main <namefile> [-star]"<<endl;
    }

    return 0;
}
