#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "Star.h"
#include <vector>

using namespace std;

class Parser
{
    public:

        Parser(string pathFile);
        virtual ~Parser();
        vector<Star> readFile();
	vector<Star> readFile2();
	vector<Star> readBinaryFile(float* cube, int size);
    protected:
    private:

    string m_pathFile;
};

#endif // PARSER_H
