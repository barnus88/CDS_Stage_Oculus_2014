#include "Parser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

Parser::Parser(string pathFile):m_pathFile(pathFile)
{
}

Parser::~Parser()
{
}

vector<Star> Parser::readFile(){
    ifstream fichier(m_pathFile.c_str(), ios::in);  // on ouvre le fichier en lecture

    vector<Star> l;

    if(fichier)  // si l'ouverture a réussi
    {
        string ligne;
        int current(0);
        int idObject;
        double mass;
        float x;
        float y;
        float z;
        double age;

        int nbLine(0);
        while(getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu"
        {
                current=0;
                nbLine++;
                //cout << ligne << endl;  // on l'affiche
                istringstream iss( ligne );
                string mot;
                while ( getline( iss, mot, ' ' ) )
                {
                    if(mot.compare("")!=0){
                        current++;
                        istringstream iss2( mot );
                        switch(current){
                            case 1:
                                iss2 >> idObject;
                                break;
                            case 2:
                                iss2 >> mass;
                                break;
                            case 3 :
                                iss2 >> x;
                                break;
                            case 4 :
                                iss2 >> y;
                                break;
                            case 5:
                                iss2 >> z;
                                break;
                            case 6:
                                iss2 >> age;
                                break;

                        }
                    }

                }


                Star s(idObject,mass,x,y,z,age);
                if(!(x==0 && y==0 && z==0)){
                    l.push_back(s);
                }
				if(nbLine%10000==0){
					cout << nbLine<< endl;
				}
                /*cout<< idObject <<" "<< mass << " " << x << " " << y << " " << z << " " << age << endl;
                if(nbLine>10){
                break;
                }*/
        }

            fichier.close();  // on ferme le fichier
            return l;
    }
    else{  // sinon
           cerr << "Impossible d'ouvrir le fichier !" << endl;
		   exit(0);
		   return l;
    }
}


vector<Star> Parser::readFile2(){
	vector<Star> l;
    FILE* fichier = NULL;
	char chaine[1000] = "";
	fichier = fopen(m_pathFile.c_str(), "r");
	
	string ligne;
    int current(0);
    int idObject;
    float mass;
    float x;
    float y;
    float z;
    float age;

    int nbLine(0);

	if (fichier != NULL)
    {
        while (fgets(chaine, 1000, fichier) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            current=0;
            nbLine++;
			if(nbLine>1){
				fscanf(fichier, "%d %f %f %f %f %f", &idObject, &mass,&x,&y,&z,&age);
				//cout<< idObject <<" "<< mass <<" "<< x <<" "<< y <<" "<< z <<" "<< age << endl;
			}
            Star s(idObject,mass,x,y,z,age);
            if(!(x==0 && y==0 && z==0)){
                l.push_back(s);
            }
			if(nbLine%10000==0){
				cout << nbLine<< endl;
			}
		}
 
        fclose(fichier);
    }
	return l;
}

vector<Star> Parser::readBinaryFile(float* cube, int size ) {
  FILE* fichier = NULL;
  vector<Star> l;
  fichier = fopen( m_pathFile.c_str(), "rb+" );
  printf("Lecture de %s\n", m_pathFile.c_str());

  if (fichier != NULL) {
    int nx=size,ny=size,nz=size;
    fread( cube, sizeof(float), nx*ny*nz, fichier );
    fclose(fichier);
    printf("Lecture du fichier %s OK!!\n", m_pathFile.c_str());
    printf("Traitement des données...\n");
    float x=0;
    float y=0;
    float z=0;
    int sizeCaree(size*size);
    for(int j=0;j<((size*size*size));j++){
        z = j / sizeCaree;
        int mod=j%sizeCaree;
        y = ( mod ) / size;
        x = ( mod ) % size;
        Star s(j,cube[j],x,y,z,0);
        l.push_back(s);
        if(j%100==0){
            std::cout << "Init "<< j<<std::endl;
        }
    }
  }
  else {
    printf("Impossible d'ouvrir le fichier %s!\n", m_pathFile.c_str());
    fclose(fichier);
  }
  return l;
}
