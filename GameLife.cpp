#include "GameLife.h"
#include <iostream>
#include <fstream> //Using this for reading and writing files.

using namespace std;

GameLife::readFile()
{
  string fileName = argv[1]; //Takes in a user command line argument and
                              // uses it for the name of the file for reading.

  ifstream myFile (fileName); //Makes the file "fileName" available for reading.

  while(myFile.get(ch)) //A while function that continues on the end of file.
  {
    //getline(myFile, line); //Reads the file line by line.
    countChar++;
  }
  myArray = new char[countChar];

}
