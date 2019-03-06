#include <iostream>

using namespace std;

class GameLife
{
  public:
    GameLife();
    GameLife(int maxSize);

    int readFile(string fileName);
    int ClassicMode(string printControl, string outputFileName);
    int DoughNutMode(string printControl, string outputFileName);
    int MirrorMode(string printControl, string outputFileName);
    int getLineLength(string fileName);
    int printGen0(string printControl);
    int RandomGrid(int dim1, int dim2, double density);

    char ch;
    int countChar;
    string fileName;
    string line;
    int lineLength;
    int numberRows;
    int numNeighbors;
    int charCounter;
    int generationCount;
    char classicArray[];
};
